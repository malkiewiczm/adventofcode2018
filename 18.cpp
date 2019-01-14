#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 0; i < to; ++i)

static char grid[55][55];

#define OPEN '.'
#define TREE '|'
#define YARD '#'

static void read_all()
{
	FILE *f = fopen("in.txt", "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
	int y = 0;
	while (fgets(grid[y], 55, f)) {
		++y;
	}
	fclose(f);
}

static const int dx[8] = { 0, 0, 1, 1, 1, -1, -1, -1 };
static const int dy[8] = { 1, -1, 1, 0, -1, 1, 0, -1 };

static void get_adj(int *adj, int y, int x)
{
	FOR(i, 8) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		adj[i] = 0;
		if (nx < 0 || nx > 50)
			continue;
		if (ny < 0 || ny > 50)
			continue;
		adj[i] = grid[ny][nx];
	}
}

#define count_adj(what)(std::count(adj, adj + 8, what))

static void step()
{
	static char back[50][55];
	FOR(y, 50) {
		FOR(x, 50) {
			int adj[8];
			get_adj(adj, y, x);
			switch (grid[y][x]) {
			case OPEN:
				if (count_adj(TREE) >= 3)
					back[y][x] = TREE;
				else
					back[y][x] = OPEN;
				break;
			case TREE:
				if (count_adj(YARD) >= 3)
					back[y][x] = YARD;
				else
					back[y][x] = TREE;
				break;
			case YARD:
				if (count_adj(YARD) && count_adj(TREE))
					back[y][x] = YARD;
				else
					back[y][x] = OPEN;
				break;
			}
		}
	}
	FOR(y, 50) {
		FOR(x, 50) {
			grid[y][x] = back[y][x];
		}
	}
}

static inline void print_grid()
{
	FOR(y, 10) {
		FOR(x, 10) {
			putchar(grid[y][x]);
		}
		putchar('\n');
	}
}

typedef long long int lld;

static inline lld get_ans()
{
	lld count_tree = 0;
	lld count_yard = 0;
	FOR(y, 50) {
		FOR(x, 50) {
			if (grid[y][x] == TREE)
				++count_tree;
			else if (grid[y][x] == YARD)
				++count_yard;
		}
	}
	//trace(count_tree << " * " << count_yard);
	return count_tree * count_yard;
}

#define TARGET 1000000000

//#define TARGET 3000

static inline void naive()
{
	FOR(i, TARGET) {
		step();
	}
	trace(get_ans());
}

int main()
{
	read_all();
	//naive();
	//read_all();
	FOR(i, 1000) {
		step();
	}
	lld last_ans = get_ans();
	static lld delta[28];
	lld total_delta = 0;
	FOR(i, 28) {
		step();
		lld ans = get_ans();
		delta[i] = ans - last_ans;
		total_delta += delta[i];
		last_ans = ans;
	}
	lld current = last_ans;
	const lld target = TARGET - 1000 - 28;
	current += target / 28 * total_delta;
	FOR(i, target % 28) {
	current += delta[i];
	}
	trace("ans = " << current);
}

