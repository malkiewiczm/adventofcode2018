#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (unsigned i = 0; i < to; ++i)

static const int dx[6] = { 0, 1, 0, -1, 0, 0 };
static const int dy[6] = { 1, 0, -1, 0, 0, 0 };
static const int dz[6] = { 0, 0, 0, 0, 1, -1 };

#define between(x, x0, x1)(x >= x0 && x <= x1)

struct bot_t {
	int x, y, z, r;
	int dist(const bot_t &rhs) const {
		return std::abs(x - rhs.x) + std::abs(y - rhs.y) + std::abs(z - rhs.z);
	}
	bool operator< (const bot_t &rhs) const {
		return x < rhs.x;
	}
};

static inline std::ostream &operator<< (std::ostream &o, const bot_t &rhs)
{
	o << "{ " << rhs.x << ' ' << rhs.y << ' ' << rhs.z << ": " << rhs.r << " }";
	return o;
}

static inline int dist(int x0, int y0, int z0, int x1, int y1, int z1)
{
	return std::abs(x0 - x1) + std::abs(y0 - y1) + std::abs(z0 - z1);
}

static std::vector<bot_t> ins;

static inline void go(FILE *f)
{
	for ( ; ; ) {
		bot_t bot;
		int ret = fscanf(f, "pos=<%d,%d,%d>, r=%d\n", &bot.x, &bot.y, &bot.z, &bot.r);
		if (ret != 4)
			break;
		ins.push_back(bot);
	}
}

struct tuple {
	int x[5];
	int &operator[] (int i) { return x[i]; }
	const int &operator[] (int i) const { return x[i]; }
	bool operator< (const tuple &rhs) const {
		if (x[0] != rhs.x[0])
			return x[0] > rhs.x[0];
		if (x[1] != rhs.x[1])
			return x[1] < rhs.x[1];
		return false;
	}
};

static inline std::ostream &operator<< (std::ostream &o, const tuple &rhs)
{
	o << "{ ";
	FOR(i, 5) {
		o << rhs.x[i] << ' ';
	}
	o << '}';
	return o;
}

static int delta = 15;

static int range_find(int x0, int x1, int y0, int y1, int z0, int z1, int div)
{
	tuple best = { 0, 0, 222, 222, 222 };
	for (int x = x0; x <= x1; ++x) {
		for (int y = y0; y <= y1; ++y) {
			for (int z = z0; z <= z1; ++z) {
				int far = dist(x, y, z, 0, 0, 0);
				int count = 0;
				for (auto bot : ins) {
					int d = dist(x, y, z, bot.x / div, bot.y / div, bot.z / div);
					if (d <= bot.r / div)
						++count;
				}
				tuple mine = { count, far, x, y, z };
				if (mine < best)
					best = mine;
			}
		}
	}
	trace(best);
	int new_div = div / 10;
	if (new_div == 0)
		return best[1];
	x0 = best[2] * 10;
	y0 = best[3] * 10;
	z0 = best[4] * 10;
	return range_find(x0 - delta, x0 + delta, y0 - delta, y0 + delta, z0 - delta, z0 + delta, new_div);
}

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(false);
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	if (argc >= 3) {
		int ret = sscanf(argv[2], "%i", &delta);
		if (ret != 1)
			delta = 15;
	}
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
	go(f);
	fclose(f);
	int ans = range_find(-10, 10, -10, 10, -10, 10, 1e8);
	trace("ans = " << ans);
#ifdef one
	unsigned biggest = 0;
	for (unsigned i = 1; i < ins.size(); ++i) {
		if (ins[i].r > ins[biggest].r)
			biggest = i;
	}
	int count = 0;
	for (unsigned i = 0; i < ins.size(); ++i) {
		if (ins[biggest].dist(ins[i]) <= ins[biggest].r) {
			++count;
		}
	}
	trace(count);
#endif
}
