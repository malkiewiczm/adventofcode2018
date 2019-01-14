#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " #what " = " << what << std::endl)
#define lintf(fmt, ...)(printf("[line %d] " fmt, __LINE__, __VA_ARGS__))

#define FOR(i, to) for (int i = 0; i < to; ++i)

static std::vector<std::string> ins;

static inline void go(FILE *f)
{
	static char buf[512];
	while (fgets(buf, sizeof(buf), f)) {
		if (buf[0] > ' ')
			ins.push_back(buf);
	}
}

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(false);
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
	go(f);
	trace(ins.size());
	fclose(f);
}
