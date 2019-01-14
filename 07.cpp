#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <map>
#include <queue>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

typedef std::priority_queue<int, std::vector<int>, std::greater<int>> pq_t;

//#define SAMPLE
#ifdef SAMPLE
#define NUM_WORKERS 2
#define time_weight(v)(v - 'A' + 1)
#define DEFAULT_FILE "ain.txt"
#else
#define NUM_WORKERS 5
#define DEFAULT_FILE "in.txt"
#define time_weight(v)(v - 'A' + 61)
#endif

int main(int argc, char **argv)
{
	const char *fname = DEFAULT_FILE;
	if (argc >= 2)
		fname = argv[1];
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be opened");
		exit(1);
	}
#ifdef SAMPLE
	trace("sample mode");
#else
	trace("normal mode");
#endif
	std::map<char, int> prereq;
	std::map<char, std::vector<char>> adj;
	for ( ; ; ) {
		char before, after;
		int r = fscanf(f, "Step %c must be finished before step %c can begin.\n", &before, &after);
		if (r != 2)
			break;
		if (prereq.find(after) == prereq.end()) {
			prereq[after] = 1;
		} else {
			++prereq[after];
		}
		if (prereq.find(before) == prereq.end()) {
			prereq[before] = 0;
		}
		if (adj.find(before) == adj.end()) {
			adj[before] = std::vector<char>();
		}
		adj[before].push_back(after);
	}
	fclose(f);
	int worker[NUM_WORKERS] = { 0 };
	char last_job[NUM_WORKERS] = { 0 };
	pq_t pq;
	int t;
	for (t = 0; ; ++t) {
		std::vector<char> reduce;
		std::vector<char> remove;
		for (int i = 0; i < NUM_WORKERS; ++i) {
			if (worker[i] <= t && last_job[i]) {
				char r = last_job[i];
				for (auto item : adj[r]) {
					--prereq[item];
				}
				last_job[i] = 0;
				break;
			}
		}
		for (auto item : prereq) {
			if (item.second)
				continue;
			for (int i = 0; i < NUM_WORKERS; ++i) {
				if (worker[i] <= t) {
					if (last_job[i]) {
						reduce.push_back(last_job[i]);
					}
					worker[i] = t + time_weight(item.first);
					last_job[i] = item.first;
					remove.push_back(item.first);
					trace("worker " << i << " is doing " << item.first << " ;; t = " << t << " finishes at " << worker[i]);
					break;
				}
			}
		}
		for (auto r : remove) {
			prereq.erase(r);
		}
		for (auto r : reduce) {
			for (auto item : adj[r]) {
				--prereq[item];
			}	
		}
		if (prereq.empty())
			break;
	}
	int biggest = 0;
	for (int i = 0; i < NUM_WORKERS; ++i) {
		if (worker[i] > biggest)
			biggest = worker[i];
		trace("worker[" << i << "] = " << worker[i]);
	}
	trace("biggest = " << biggest << ", t = " << t);
}
