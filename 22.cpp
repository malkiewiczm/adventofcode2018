#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 1; i <= to; ++i)

//#define sample
#ifdef sample
#define DEPTH 510
#define TARGET_X 10
#define TARGET_Y 10
#else
#define DEPTH 4002
#define TARGET_X 5
#define TARGET_Y 746
#endif
#define MOD 20183
#define SX 2000
#define SY 2000

static int grid[SX + 1][SY + 1];

static inline int clean_mult(int a, int b)
{
	int ret = 0;
	const int base = std::max(a, b);
	const int times = std::min(a, b);
	FOR(i, times) {
		ret = (ret + base) % MOD;
	}
	return ret;
}

static inline int get_level(int i)
{
	return (i + DEPTH) % MOD;
}

#define ROCK 0
#define WET 1
#define NARROW 2

#define NONE 0
#define TORCH 1
#define GEAR 2

struct tuple {
	int x, y, w, g;
	tuple(int x0, int y0, int w0, int g0)
		: x(x0), y(y0), w(w0), g(g0) {}
	bool operator< (const tuple &rhs) const {
		return w < rhs.w;
	}
	bool operator> (const tuple &rhs) const {
		return w > rhs.w;
	}
};

#define pq_t(T) std::priority_queue<T, std::vector<T>, std::greater<T>>

static int shortest_path()
{
	const int dx[4] = { 0, 0, 1, -1 };
	const int dy[4] = { 1, -1, 0, 0 };
	pq_t(tuple) pq;
	pq.push({ 0, 0, 0, TORCH });
	std::set<std::vector<int>> seen;
	while (! pq.empty()) {
		int x = pq.top().x;
		int y = pq.top().y;
		int w = pq.top().w;
		int g = pq.top().g;
		pq.pop();
		if (x == TARGET_X && y == TARGET_Y && g == TORCH) {
			return w;
		}
		if (w >= 5000)
			continue;
		if (seen.find({ x, y, g }) != seen.end())
			continue;
		seen.insert({ x, y, g });
		switch (grid[x][y]) {
		case ROCK:
			if (g == TORCH)
				pq.push({ x, y, w + 7, GEAR });
			else
				pq.push({ x, y, w + 7, TORCH });
			break;
		case WET:
			if (g == GEAR)
				pq.push({ x, y, w + 7, NONE });
			else
				pq.push({ x, y, w + 7, GEAR});
			break;
		case NARROW:
			if (g == TORCH)
				pq.push({ x, y, w + 7, NONE });
			else
				pq.push({ x, y, w + 7, TORCH });
			break;
		}
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx > SX || ny > SY)
				continue;
			switch (grid[nx][ny]) {
			case ROCK:
				if (g != NONE)
					pq.push({ nx, ny, w + 1, g });
				break;
			case WET:
				if (g != TORCH)
					pq.push({ nx, ny, w + 1, g });
				break;
			case NARROW:
				if (g != GEAR)
					pq.push({ nx, ny, w + 1, g });
				break;
			}
		}
	}
	return -8;
}

int main()
{
	FOR(x, SX) {
		grid[x][0] = x * 16807;
	}
	FOR(y, SY) {
		grid[0][y] = y * 48271;
	}
	FOR(x, SX) {
		FOR(y, SY) {
			grid[x][y] = get_level(grid[x - 1][y]) * get_level(grid[x][y - 1]);
		}
	}
	grid[TARGET_X][TARGET_Y] = 0;
	for (int y = 0; y <= SY; ++y) {
		for (int x = 0; x <= SX; ++x) {
			grid[x][y] = get_level(grid[x][y]) % 3;
		}
	}
	int ans = shortest_path();
	trace("ans = " << ans);
#ifdef sample
	if (ans == 45)
		trace("sample is right");
	else
		trace("sample should be 45");
#endif
#ifdef one
	int sum = 0;
	for (int y = 0; y <= TARGET_Y; ++y) {
		for (int x = 0; x <= TARGET_X; ++x) {
			sum += grid[x][y];
		}
	}
	trace("sum = " << sum);
#endif
}
