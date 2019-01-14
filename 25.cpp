#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " #what " = " << what << std::endl)
#define lintf(fmt, ...)(printf("[line %d] " fmt, __LINE__, __VA_ARGS__))

#define FOR(i, to) for (unsigned i = 0; i < to; ++i)
#define N ins.size()

struct vec4 {
	int x, y, z, w;
	bool read(FILE *f) {
		return fscanf(f, "%d,%d,%d,%d\n", &x, &y, &z, &w) == 4;
	}
	int dist(const vec4 &rhs) {
		return std::abs(x - rhs.x) + std::abs(y - rhs.y) + std::abs(z - rhs.z) + std::abs(w - rhs.w);
	}
};

static int sets[2000];

static int rep(int n)
{
	if (sets[n] == n)
		return n;
	return sets[n] = rep(sets[n]);
}

static inline void join(int a, int b)
{
	sets[rep(a)] = sets[rep(b)];
}


static std::vector<vec4> ins;

static inline void go(FILE *f)
{
	for ( ; ; ) {
		vec4 vec;
		if (! vec.read(f))
			break;
		ins.push_back(vec);
	}
}

//#define GEN
#ifdef GEN
#include <time.h>

static inline int r()
{
	return (rand() % 40) - 20;
}

int main()
{
	srand(time(NULL));
	FOR(i, 1e6) {
		printf("%d,%d,%d,%d\n", r(), r(), r(), r());
	}
}
#else
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
	fclose(f);
	FOR(i, N) {
		sets[i] = i;
	}
	FOR(i, N) {
		FOR(j, i) {
			if (ins[i].dist(ins[j]) <= 3)
				join(j, i);
		}
	}
	std::set<int> unique;
	FOR(i, N) {
		unique.insert(rep(i));
	}
	trace(unique.size());
}
#endif
