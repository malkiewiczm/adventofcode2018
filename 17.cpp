#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define inf 1e6
#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define min3(a, b, c)(std::min(a, std::min(b, c)))
#define max3(a, b, c)(std::max(a, std::max(b, c)))

#define FOR(i, to) for (int i = 0; i < to; ++i)

#define SAND 0
#define CLAY 1
#define WATER 2
#define FALL 3
#define MARKER 4

static char grid[2000][1000];
static int min_y = inf;
static int max_y = 0;
static int min_x = inf;
static int max_x = 0;

static inline void fill_with(char what, int x0, int x1, int y0, int y1)
{
	if (what == CLAY) {
		min_y = min3(y0, y1, min_y);
		max_y = max3(y0, y1, max_y);
		min_x = min3(x0, x1, min_x);
		max_x = max3(x0, x1, max_x);
	}
	for (int y = y0; y <= y1; ++y) {
		for (int x = x0; x <= x1; ++x) {
			grid[y][x] = what;
		}
	}
}

static void read_all(const char *fname)
{
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
	int a, b, c;
	char first, second;
	while (fscanf(f, "%c=%d, %c=%d..%d\n", &first, &a, &second, &b, &c) == 5) {
		if (first == 'x') {
			fill_with(CLAY, a, a, b, c);
		} else {
			fill_with(CLAY, b, c, a, a);
		}
	}
	fclose(f);
}

static int get_clay_right(int sx, int sy)
{
	for (int x = sx; x < 1000; ++x) {
		if (grid[sy][x] == CLAY) {
			return x;
		}
	}
	return 1000;
}

static int get_clay_left(int sx, int sy)
{
	for (int x = sx; x >= 0; --x) {
		if (grid[sy][x] == CLAY) {
			return x;
		}
	}
	return -1;
}

static void water_at(int sx, int sy);

static int spill_check(int sx, int sy, int clay_depth, int clay_right, int clay_left)
{
	bool spill_left = false;
	bool spill_right = false;
	int spill_y = -1;
	for (int y = clay_depth - 1; y >= sy; --y) {
		int new_clay_left = get_clay_left(sx, y);
		int new_clay_right = get_clay_right(sx, y);
		spill_right = new_clay_right > clay_right;
		spill_left = new_clay_left < clay_left;
		if (spill_right || spill_left) {
			spill_y = y;
			break;
		}
		clay_left = new_clay_left;
		clay_right = new_clay_right;
		fill_with(WATER, clay_left + 1, clay_right - 1, y, y);
	}
	if (spill_right) {
		clay_right = get_clay_right(sx, spill_y + 1);
		clay_left = get_clay_left(sx, spill_y + 1);
		fill_with(FALL, clay_left + 1, clay_right, spill_y, spill_y);
		water_at(clay_right + 1, spill_y);
	}
	if (spill_left) {
		clay_right = get_clay_right(sx, spill_y + 1);
		clay_left = get_clay_left(sx, spill_y + 1);
		fill_with(FALL, clay_left, clay_right - 1, spill_y, spill_y);
		water_at(get_clay_left(sx, spill_y + 1) - 1, spill_y);
	}
	return spill_y;
}

static void outer_spill_check(int sx, int sy, int spout_y, int clay_right, int clay_left)
{
	bool spill_left = false;
	bool spill_right = false;
	int spill_y = -1;
	for (int y = spout_y - 1; y >= sy; --y) {
		int new_clay_left = get_clay_left(sx, y);
		int new_clay_right = get_clay_right(sx, y);
		spill_right = new_clay_right > clay_right;
		spill_left = new_clay_left < clay_left;
		if (spill_right || spill_left) {
			spill_y = y;
			break;
		}
		clay_left = new_clay_left;
		clay_right = new_clay_right;
	}
	clay_right = get_clay_right(sx, spill_y + 1);
	clay_left = get_clay_left(sx, spill_y + 1);
	if (spill_right) {
		fill_with(FALL, clay_left + 1, clay_right, spill_y, spill_y);
		water_at(clay_right + 1, spill_y);
		water_at(clay_right - 1, spill_y + 1);
	}
	if (spill_left) {
		fill_with(FALL, clay_left, clay_right - 1, spill_y, spill_y);
		water_at(clay_left - 1, spill_y);
		water_at(clay_left + 1, spill_y + 1);
	}
	if (spill_left || spill_right) {
		fill_with(WATER, clay_left + 1, clay_right - 1, spill_y + 1, spout_y);
	}
}

static bool confirm_box(int sy, const int right, const int left)
{
	while (grid[sy][right] == CLAY && grid[sy][left] == CLAY) {
		bool rclay = grid[sy][right - 1] == CLAY;
		bool lclay = grid[sy][left + 1] == CLAY;
		if (rclay != lclay)
			return false;
		if (rclay)
			return true;
		++sy;
		if (sy > max_y)
			return false;
	}
	return false;
}

static void water_at(int sx, int sy)
{
	if (sx < 0 || sx >= 1000)
		return;
	if (sy > max_y)
		return;
	if (grid[sy][sx] != SAND)
		return;
	int clay_depth = -1;
	for (int y = sy; y <= max_y; ++y) {
		if (grid[y][sx] == CLAY) {
			clay_depth = y;
			break;
		} else {
			grid[y][sx] = FALL;
		}
	}
	if (clay_depth == -1)
		return;
	bool should_check_spill = true;
	int clay_right = get_clay_right(sx, clay_depth - 1);
	for (int x = sx; x < clay_right; ++x) {
		if (grid[clay_depth][x] == SAND) {
			water_at(x, clay_depth);
			should_check_spill = false;
			break;
		}
	}
	int clay_left = get_clay_left(sx, clay_depth - 1);
	for (int x = sx; x > clay_left; --x) {
		if (grid[clay_depth][x] == SAND) {
			water_at(x, clay_depth);
			should_check_spill = false;
			break;
		}
	}
	if (should_check_spill)
		spill_check(sx, sy, clay_depth, clay_right, clay_left);
	int spout_y = -1;
	for (int y = clay_depth - 1; y >= sy; --y) {
		if (grid[y][sx] == FALL) {
			spout_y = y;
			break;
		}
	}
	if (spout_y == -1)
		return;
	clay_right = get_clay_right(sx, spout_y);
	if (clay_right > max_x)
		return;
	clay_left = get_clay_left(sx, spout_y);
	if (clay_left < min_x)
		return;
	if (confirm_box(spout_y, clay_right, clay_left))
		outer_spill_check(sx, sy, spout_y, clay_right, clay_left);
}

static inline char printable(char what)
{
	switch (what) {
	case CLAY:
		return '8';
	case WATER:
		return '~';
	case FALL:
		return '|';
	case MARKER:
		return 'X';
	default:
		return(' ');
	}
}

static inline void big_print()
{
	for (int y = min_y; y <= max_y; ++y) {
		for (int x = min_x; x <= max_x; ++x) {
			putchar(printable(grid[y][x]));
		}
		putchar('\n');
	}
}

static inline int water_count()
{
	int ret = 0;
	for (int y = min_y; y <= max_y; ++y) {
		ret += std::count(grid[y], grid[y] + 1000, WATER);
		ret += std::count(grid[y], grid[y] + 1000, FALL);
	}
	return ret;
}

#define BIG_PRINT

int main(int argc, char **argv)
{
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	read_all(fname);
	water_at(500, 0);
#ifdef BIG_PRINT
	big_print();
#else
	int ans = water_count();
	trace("ans = " << ans);
#endif
}
