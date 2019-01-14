#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <math.h>

#define trace(what)(std::cout << what << std::endl)

/*
static void read_all_lines(std::vector<std::string> &vec)
{
	std::string line;
	while (std::getline(std::cin, line)) {
		vec.push_back(line);
	}
}
*/
struct claim_t {
	int id, x, y, w, h;
	bool read() {
		return scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) == 5;
	}
};

static bool hittest(const claim_t &a, const claim_t &b)
{
	return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	//std::vector<std::string> ins;
	//read_all_lines(ins);
	std::vector<claim_t> claims;
	for ( ; ; ) {
		claim_t c;
		if (! c.read())
			break;
		claims.push_back(c);
	}
	for (unsigned i = 0; i < claims.size(); ++i) {
		bool unhit = true;
		for (unsigned j = 0; j < claims.size(); ++j) {
			if (i == j)
				continue;
			if (hittest(claims[i], claims[j])) {
				unhit = false;
				break;
			}
		}
		if (unhit) {
			trace(claims[i].id);
		}
	}
}

#ifdef one

static int grid[5000][5000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	//std::vector<std::string> ins;
	//read_all_lines(ins);
	std::vector<claim_t> claims;
	for ( ; ; ) {
		claim_t c;
		if (! c.read())
			break;
		claims.push_back(c);
	}
	int big_x = 0;
	int big_y = 0;
	for (auto item : claims) {
		big_x = std::max(big_x, item.w + item.x);
		big_y = std::max(big_y, item.h + item.y);
		for (int x = item.x; x < item.w + item.x; ++x) {
			for (int y = item.y; y < item.h + item.y; ++y) {
				++grid[x][y];
			}
		}
	}
	int count = 0;
	for (int x = 0; x <= big_x; ++x) {
		for (int y = 0; y <= big_y; ++y) {
			if (grid[x][y] > 1)
				++count;
		}
	}
	trace(count);
}
#endif
