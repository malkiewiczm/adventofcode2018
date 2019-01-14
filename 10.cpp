#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)
#define inf 1e9

struct star_t {
	int x, y;
	int vx, vy;
	bool read(FILE *f) {
		return fscanf(f, "position=< %d, %d> velocity=< %d, %d>\n", &x, &y, &vx, &vy) == 4;
	}
	int px(int t) const {
		return x + vx * t;
	}
	int py(int t) const {
		return y + vy * t;
	}
};

std::vector<star_t> stars;

static void bb_coords(int t, int &min_x, int &min_y, int &max_x, int &max_y)
{
	min_x = inf;
	min_y = inf;
	max_x = -inf;
	max_y = -inf;
	for (auto item : stars) {
		int x = item.px(t);
		int y = item.py(t);
		min_x = std::min(x, min_x);
		min_y = std::min(y, min_y);
		max_x = std::max(x, max_x);
		max_y = std::max(y, max_y);
	}
}

static float bb_size(int t) {
	int min_x, min_y, max_x, max_y;
	bb_coords(t, min_x, min_y, max_x, max_y);
	return ((float)max_x - (float)min_x) * ((float)max_y - (float)min_y);
}

static int find_t() {
	int left = 0;
	int right = 1e9;
	for ( ; ; ) {
		if (abs(right - left) <= 2)
			return left + (right - left) / 2;
		int left3 = left + (right - left) / 3;
		int right3 = right - (right - left) / 3;
		if (bb_size(left3) > bb_size(right3))
			left = left3;
		else
			right = right3;
	}
	return 0;
}

//#define benchmark
#ifdef benchmark
#include <windows.h>
static inline LONGLONG get_time() {
	LONGLONG ret;
	QueryPerformanceCounter((LARGE_INTEGER*)&ret);
	return ret;
}
#define to_micro(what)((what) * 0.341639f)

static int find_t_linear() {
	float last = 1e30;
	for (int t = 0; t < 1e9; ++t) {
		float now = bb_size(t);
		if (now > last)
			return t - 1;
		last = now;
	}
	return 0;
}
#endif

#define TERM_W 85
#define TERM_H 20

int main(int argc, char **argv)
{
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	trace("input file name = " << fname);
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file can't be opened");
		exit(1);
	}
	for ( ; ; ) {
		star_t star;
		if (! star.read(f))
			break;
		stars.push_back(star);
	}
	fclose(f);
#ifdef benchmark
	LONGLONG start, end;
	int tmp;
	start = get_time();
	tmp = find_t_linear();
	end = get_time();
	trace("linear (" << tmp << "): " << to_micro(end - start));
	start = get_time();
	tmp = find_t();
	end = get_time();
	trace("ternary (" << tmp << "): " << to_micro(end - start));
	start = get_time();
	Sleep(1);
	end = get_time();
	trace("Sleep(1): " << to_micro(end - start));
	exit(0);
#endif
	int t = find_t();
	int min_x, min_y, max_x, max_y;
	bb_coords(t, min_x, min_y, max_x, max_y);
	trace("t = " << t << " : " << min_x << ", " << min_y << " : " << max_x << ", " << max_y);
	static char grid[TERM_H][TERM_W];
	for (int y = 0; y < TERM_H; ++y) {
		for (int x = 0; x < TERM_W; ++x) {
			grid[y][x] = ' ';
		}
	}
	int missing_count = 0;
	for (auto item : stars) {
		int x =  item.px(t) - min_x;
		int y = item.py(t) - min_y;
		if (x > TERM_W || y > TERM_H) {
			++missing_count;
			continue;
		}
		grid[y][x] = '8';
	}
	for (int y = 0; y < TERM_H; ++y) {
		for (int x = 0; x < TERM_W; ++x) {
			putchar(grid[y][x]);
		}
		putchar('\n');
	}
	trace("offscreen : " << missing_count);
}
