#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 0; i < to; ++i)

#define next()(fgetc(f))

//#define one

struct cell_t {
	bool up;
	bool down;
	bool left;
	bool right;
	cell_t()
		: up(false), down(false), left(false), right(false) {}
};

template<typename T>
struct grid_t {
	T mine[110][110];
	T &operator()(int x, int y) {
		return mine[x + 55][y + 55];
	}
};

grid_t<cell_t> grid;

struct vec2 {
	int x, y;
	vec2() : x(0), y(0) {}
	vec2(int a, int b) : x(a), y(b) {}
	void go(char where) {
		switch (where) {
		case 'N':
			grid(x, y).up = true;
			++y;
			grid(x, y).down = true;
			break;
		case 'S':
			grid(x, y).down = true;
			--y;
			grid(x, y).up = true;
			break;
		case 'W':
			grid(x, y).left = true;
			--x;
			grid(x, y).right = true;
			break;
		case 'E':
			grid(x, y).right = true;
			++x;
			grid(x, y).left = true;
			break;
		default:
			trace("direction " << where << " is not valid");
			exit(1);
		}
	}
	vec2 up() const {
		return vec2(x, y + 1);
	}
	vec2 down() const {
		return vec2(x, y - 1);
	}
	vec2 left() const {
		return vec2(x - 1, y);
	}
	vec2 right() const {
		return vec2(x + 1, y);
	}
	int path_dist() const {
		return std::abs(x) + std::abs(y);
	}
	bool operator< (const vec2 &rhs) const {
		return path_dist() < rhs.path_dist();
	}
};

static inline std::ostream &operator<<(std::ostream &o, const vec2 &vec)
{
	o << '(' << vec.x << ", " << vec.y << ')';
	return o;
}

static bool fill_grid(FILE *f, vec2 loc)
{
	for ( ; ; ) {
		char c = next();
		switch (c) {
		case '(': {
			bool again = false;
			do {
				again = fill_grid(f, loc);
			} while (again);
			break;
		}
		case ')':
			return false;
		case '|':
			return true;
		case '$':
			return false;
		default:
			loc.go(c);
		}
	}
}

#ifdef one

static int calc_depth(vec2 loc, int curr)
{
	static grid_t<bool> visited;
	if (visited(loc.x, loc.y)) {
		return curr;
	}
	visited(loc.x, loc.y) = true;
	int depth[5] = { 0 };
	depth[0] = curr;
	if (grid(loc.x, loc.y).up) {
		depth[1] = calc_depth(loc.up(), curr + 1);
	}
	if (grid(loc.x, loc.y).down) {
		depth[2] = calc_depth(loc.down(), curr + 1);
	}
	if (grid(loc.x, loc.y).left) {
		depth[3] = calc_depth(loc.left(), curr + 1);
	}
	if (grid(loc.x, loc.y).right) {
		depth[4] = calc_depth(loc.right(), curr + 1);
	}
	int *res = std::max_element(depth, depth + 5);
	return res[0];
}

#else

static int total_over = 0;

static void calc_depth(vec2 loc, int curr)
{
	static grid_t<bool> visited;
	if (visited(loc.x, loc.y)) {
		return;
	}
	if (curr >= 1000)
		++total_over;
	visited(loc.x, loc.y) = true;
	if (grid(loc.x, loc.y).up) {
		calc_depth(loc.up(), curr + 1);
	}
	if (grid(loc.x, loc.y).down) {
		calc_depth(loc.down(), curr + 1);
	}
	if (grid(loc.x, loc.y).left) {
		calc_depth(loc.left(), curr + 1);
	}
	if (grid(loc.x, loc.y).right) {
		calc_depth(loc.right(), curr + 1);
	}
}

#endif

static inline void go(FILE *f)
{
	assert(next() == '^');
	fill_grid(f, vec2());
#ifdef one
	int ans = calc_depth(vec2(), -1);
	trace(ans);
#else
	calc_depth(vec2(), 0);
	trace(total_over);
#endif
}

int main(int argc, char **argv)
{
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
	go(f);
	fclose(f);
}
