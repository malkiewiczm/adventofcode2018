#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

struct rule_t {
	char pattern[5];
};

static std::ostream &operator<<(std::ostream &o, rule_t &rule) {
	for (int i = 0; i < 5; ++i) {
		o << rule.pattern[i];
	}
	return o;
}

static void read_all_lines(std::vector<rule_t> &vec, char *first)
{
	FILE *f = fopen("in.txt", "r");
	static char buf[512];
	fgets(buf, 512, f);
	memcpy(first, buf, strlen(buf));
	for (char *b = buf; *b; ++b) {
		if (b[0] == '\n')
			b[0] = '\0';
	}
	while (fgets(buf, sizeof(buf), f)) {
		if (buf[0] <= ' ')
			continue;
		if (buf[9] == '.')
			continue;
		rule_t rule;
		for (int i = 0; i < 5; ++i)
			rule.pattern[i] = buf[i];
		vec.push_back(rule);
	}
	fclose(f);
}


#define BUF_SIZE 6144
#define BUF_SIZE_HALF (BUF_SIZE / 2)

static char scratch_buf[BUF_SIZE];
#define scratch()(std::string(scratch_buf))

static inline char find_pattern(std::vector<rule_t> &vec, char a0, char a1, char a2, char a3, char a4)
{
	for (auto rule : vec) {
		if (rule.pattern[0] == a0 && rule.pattern[1] == a1 && rule.pattern[2] == a2 && rule.pattern[3] == a3 && rule.pattern[4] == a4) {
			return '#';
		}
	}
	return '.';
}

int main()
{
	static char first[BUF_SIZE];
	std::vector<rule_t> rules;
	read_all_lines(rules, first + BUF_SIZE_HALF);
	for (int i = 0; i < BUF_SIZE - 1; ++i) {
		scratch_buf[i] = '.';
		if (first[i] != '.' && first[i] != '#')
			first[i] = '.';
	}
	first[BUF_SIZE - 1] = '\0';
	scratch_buf[BUF_SIZE - 1] = '\0';
	std::string working = first;
	int last_diff = 0;
	int last_sum = 0;
	unsigned long long accum = 0;
	for (int count = 1; count <= 200; ++count) {
		std::string sc = scratch();
		for (unsigned i = 2; i < working.size(); ++i) {
			sc[i] = find_pattern(rules, working[i - 2], working[i - 1], working[i], working[i + 1], working[i + 2]);
		}
		std::swap(sc, working);
		
		int sum = 0;
		for (int i = 0; i < BUF_SIZE; ++i) {
			if (working[i] == '#') {
				sum += i - BUF_SIZE_HALF - 15;
			}
		}
		int diff = sum - last_sum;
		last_diff = diff;
		last_sum = sum;
		accum += diff;
	}
	accum += last_diff * (50 * 1e9 - 200);
	trace(accum);
}
