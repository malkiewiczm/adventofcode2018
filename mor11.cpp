#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 1; i <= to; ++i)

int main()
{
	puts("serial num,max grid");
	for (int S = 0; ; ++S) {
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
		FOR(s, 300) {
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
		FOR(i, biggest[3]) {
			putchar('8');
		}
		putchar('\n');
		//printf("%d,%d\n", S, biggest[3]);
	}
}
