#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define meta if (x == x1 && y == y1) return false

static bool is_ok(int x0, int y0, int x1, int y1)
{
	if (x0 == x1 || y0 == y1)
		return false;
	int x, y;
	for (x = x0 + 1, y = y0 + 1; x < 8 && y < 8; ++x, ++y) {
		meta;
	}
	for (x = x0 + 1, y = y0 - 1; x < 8 && y >= 0; ++x, --y) {
		meta;
	}
	for (x = x0 - 1, y = y0 + 1; x >= 0 && y < 8; --x, ++y) {
		meta;
	}
	for (x = x0 - 1, y = y0 - 1; x >= 0 && y >= 0; --x, --y) {
		meta;
	}
	return true;
}

#define get_x(v)(v % 8)
#define get_y(v)(v / 8)

int main()
{
	int count = 0;
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < i; ++j) {
			int x0 = get_x(i);
			int y0 = get_y(i);
			int x1 = get_x(j);
			int y1 = get_y(j);
			if (is_ok(x0, y0, x1, y1))
				++count;
		}
	}
	trace("count = " << count);
}
