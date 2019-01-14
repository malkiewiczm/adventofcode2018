#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 1; i <= to; ++i)

int main(int argc, char **argv)
{
	int S = 9798;
	if (argc >= 2) {
		if (sscanf(argv[1], "%i", &S) != 1) {
			trace("could not read integer");
			exit(1);
		}
	}
	bool part_one = argc >= 3;
	trace("serial no = " << S);
	static int G[301][301];
	FOR(y, 300) {
		FOR(x, 300) {
			int p = (x + 10) * y;
			p += S;
			p *= (x + 10);
			p = p / 100 % 10;
			p -= 5;
			G[y][x] = p + G[y - 1][x] + G[y][x - 1] - G[y - 1][x - 1];
		}
	}
	int biggest[4] = { 0 };
	int to = part_one ? 3 : 300;
	FOR(s, to) {
		FOR(y, 301 - s) {
			FOR(x, 301 - s) {
				int a = x + s - 1;
				int b = y + s - 1;
				int sum = G[b][a] + G[y - 1][x - 1] - G[y - 1][a] - G[b][x - 1];
				if (sum > biggest[0]) {
					biggest[0] = sum;
					biggest[1] = x;
					biggest[2] = y;
					biggest[3] = s;
				}
			}
		}
	}
	trace(biggest[1] << ", " << biggest[2] << ", " << biggest[3]);
}
