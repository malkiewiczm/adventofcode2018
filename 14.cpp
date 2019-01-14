#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define S 440231

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 0; i < to; ++i)

#define BUF_SIZE 1000000000

int main()
{
#ifndef one
	const char *target = "440231";
	int target_len = strlen(target);
	static char start[BUF_SIZE];
	start[0] = '3';
	start[1] = '7';
	char *end = start + 2;
	char *first = start;
	char *second = start + 1;
	char *where = nullptr;
	for ( ; ; ) {
		int sum = (first[0] - '0') + (second[0] - '0');
		if (sum >= 10) {
			end[0] = '1';
			end[1] = sum - 10 + '0';
			end += 2;
		} else {
			end[0] = sum + '0';
			end += 1;
		}
		int diff = end - start;
		first = start + ((first - start) + first[0] - '0' + 1) % diff;
		second = start + ((second - start) + second[0] - '0' + 1) % diff;
		if (end - start > BUF_SIZE) {
			trace("panic, overflow");
			exit(1);
		}
		if (end - target_len >= start) {
			where = end - target_len;
			if (memcmp(where, target, target_len) == 0)
				break;
			where = end - target_len - 1;
			if (memcmp(where, target, target_len) == 0)
				break;
		}
	}
	trace(where - start);
#else
	static char start[S * 2];
	start[0] = '3';
	start[1] = '7';
	char *end = start + 2;
	char *first = start;
	char *second = start + 1;
	FOR(i, S + 10) {
		int sum = (first[0] - '0') + (second[0] - '0');
		if (sum >= 10) {
			end[0] = '1';
			end[1] = sum - 10 + '0';
			end += 2;			
		} else {
			end[0] = sum + '0';
			end += 1;
		}
		int diff = end - start;
		first = start + ((first - start) + first[0] - '0' + 1) % diff;
		second = start + ((second - start) + second[0] - '0' + 1) % diff;
	}
	FOR(i, 10) {
		putchar(start[S + i]);
	}
	putchar('\n');
#endif
}
