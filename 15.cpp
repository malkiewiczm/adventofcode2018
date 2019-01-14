#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

#define ONE

static inline void _assert(bool what, int line)
{
	if (what)
		return;
	fprintf(stderr, "assert failed on line %d\n", line);
	exit(1);
}
#define assert(what)(_assert(what, __LINE__))
#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

static char grid[50][50];
static bool occ[50][50];
struct ent_t;
static int num_goblin = 0;
static int num_elf = 0;
typedef std::vector<ent_t> vec_t;

#define FOR(i, to) for (unsigned i = 0; i < to; ++i)
#define inf 1e7
#define WALL '#'
#define OPEN '.'
#define ELF_WIN 1
#define GOBLIN_WIN 2

static const int dx[4] = { 0, -1, 1, 0 };
static const int dy[4] = { -1, 0, 0, 1 };
vec_t ent;

static int dist[50][50];

static inline void print_dist()
{
	FOR(y, 10) {
		FOR(x, 10) {
			printf("%3d", (dist[y][x] == inf) ? -1 : dist[y][x]);
		}
		putchar('n');
	}																
}

static int safe_dist(int y, int x);

struct tuple {
	int x, y, z;
	tuple() = default;
	tuple(int a, int b, int c)
		: x(a), y(b), z(c) {}
	bool operator< (const tuple &rhs) const {
		if (z != rhs.z)
			return z < rhs.z;
		if (y != rhs.y)
			return y < rhs.y;
		return x < rhs.x;
	}
};

static void calc_dist(int sx, int sy)
{
	FOR(i, 50) {
		FOR(j, 50) {
			dist[i][j] = inf;
		}
	}
	std::queue<tuple> Q;
	Q.push({ sx, sy, 0 });
	while (not Q.empty()) {
		int x = Q.front().x;
		int y = Q.front().y;
		int z = Q.front().z;
		Q.pop();
		if (dist[y][x] != inf)
			continue;
		dist[y][x] = z;
		++z;
		FOR(k, 4) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx < 0 || nx >= 50 || ny < 0 || ny >= 50)
				continue;
			if (grid[ny][nx] == WALL)
				continue;
			if (occ[ny][nx])
				continue;
			Q.push({ nx, ny, z});
		}
	}
}

struct ent_t {
	int x, y;
	int hp, attack;
	bool kind;
	bool is_elf() const {
		return kind;
	}
	bool is_goblin() const {
		return !kind;
	}
	ent_t() = default;
	ent_t(int _x, int _y, int _attack, bool _kind)
		: x(_x), y(_y), hp(200), attack(_attack), kind(_kind) {
		occ[y][x] = true;
		if (kind)
			++num_elf;
		else
			++num_goblin;

	}
	bool operator< (const ent_t &rhs) const {
		if (y != rhs.y)
			return y < rhs.y;
		return x < rhs.x;
	}
	bool dead() const {
		return hp <= 0;
	}
	bool not_dead() const {
		return hp > 0;
	};
	void damage(int amt) {
		hp -= amt;
		if (dead()) {
			occ[y][x] = false;
			if (kind) {
#ifndef ONE
				throw GOBLIN_WIN;
#endif
				--num_elf;
			} else {
				--num_goblin;
			}
		}
	}
	bool nearby() {
		std::vector<tuple> possible;
		FOR(i, ent.size()) {
			ent_t &other = ent[i];
			if (other.dead())
				continue;
			if (kind == other.kind)
				continue;
			FOR(k, 4) {
				int nx = x + dx[k];
				int ny = y + dy[k];
				if (other.x == nx && other.y == ny)
					possible.emplace_back(nx, ny, other.hp);
			}
		}
		if (possible.empty())
			return false;
		auto closest = std::min_element(possible.begin(), possible.end());
		FOR(i, ent.size()) {
			ent_t &other = ent[i];
			if (other.dead())
				continue;
			if (kind == other.kind)
				continue;
			if (other.x == closest->x && other.y == closest->y) {
				other.damage(attack);
				return true;
			}
		}
		throw "problem";
	}
	void move() {
		if (nearby())
			return;
		calc_dist(x, y);
		std::vector<tuple> possible;
		FOR(i, ent.size()) {
			ent_t &other = ent[i];
			if (other.dead())
				continue;
			if (kind == other.kind)
				continue;
			FOR(k, 4) {
				int nx = other.x + dx[k];
				int ny = other.y + dy[k];
				possible.emplace_back(nx, ny, safe_dist(nx, ny));
			}
		}
		auto closest = std::min_element(possible.begin(), possible.end());
		if (closest->z == inf)
			return;
		int cx = closest->x;
		int cy = closest->y;
		calc_dist(cx, cy);
		possible.clear();
		FOR(k, 4) {
			int nx = x + dx[k];
			int ny = y + dy[k];
			possible.emplace_back(nx, ny, safe_dist(nx, ny));
		}
		closest = std::min_element(possible.begin(), possible.end());
		assert(closest->z != inf);
		occ[y][x] = false;
		x = closest->x;
		y = closest->y;
		occ[y][x] = true;
		nearby();
	}
};

static int safe_dist(int x, int y)
{
	if (x < 0 || y < 0)
		return inf;
	if (x >= 50 || y >= 50)
		return inf;
	if (grid[y][x] == WALL)
		return inf;
	if (occ[y][x])
		return inf;
	return dist[y][x];
}

static void read_all(const char *fname, const int elf_attack)
{
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
	int y = 0;
	while (fgets(grid[y], 50, f)) {
		FOR(x, 50) {
			switch (grid[y][x]) {
			case 'G':
				grid[y][x] = OPEN;
				ent.emplace_back(x, y, 3, false);
				break;
			case 'E':
				grid[y][x] = OPEN;
				ent.emplace_back(x, y, elf_attack, true);
				break;
			}
		}
		++y;
	}
	fclose(f);
}

static inline void do_move()
{
	std::sort(ent.begin(), ent.end());

	FOR(i, ent.size()) {
		if (ent[i].dead())
			continue;
		if (num_elf == 0 && ent[i].is_goblin())
			throw GOBLIN_WIN;
		if (num_goblin == 0 && ent[i].is_elf())
			throw ELF_WIN;
		ent[i].move();
	}
}

static inline void print_loc()
{
	static char tmp[33][33];
	FOR(y, 32) {
		FOR(x, 32) {
			tmp[y][x] = grid[y][x] > ' ' ? grid[y][x] : ' ';
		}
	}
	FOR(i, ent.size()) {
		if (ent[i].dead())
			continue;
		tmp[ent[i].y][ent[i].x] = ent[i].kind ? 'E' : 'G';
	}
	FOR(y, 32) {
		puts(tmp[y]);
	}
}

static int get_health_alive()
{
	int ret = 0;
	FOR(i, ent.size()) {
		if (ent[i].dead())
			continue;
		putchar((ent[i].is_elf() ? 'E' : 'G'));
		printf("(%d) ", ent[i].hp);
		ret += ent[i].hp;
	}
	putchar('\n');
	return ret;
}

int main(int argc, char **argv)
{
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	int elf_attack = 3;
	int round_num = 0;
#ifndef ONE
	for ( ; ; ) {
		++elf_attack;
#endif
		ent.clear();
		num_goblin = 0;
		num_elf = 0;
		FOR(i, 50) {
			FOR(j, 50) {
				occ[i][j] = false;
			}
		}
		read_all(fname, elf_attack);
		round_num = 0;
		try {
			for ( ; ; ) {
				//printf("round %d\n", round_num);
				//print_loc();
				//get_health_alive();
				do_move();
				++round_num;
				//getchar();
			}
		} catch (int who) {
#ifndef ONE
			if (who == ELF_WIN)
				break;
		}
#endif
	}
	int a = get_health_alive();
	int res = a * round_num;
	trace(round_num << " * " << a << " = " << res);
}
