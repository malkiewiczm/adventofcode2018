#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

static int char_diff(const char *a, const char *b)
{
	int ret = 0;
	while (a[0] != '\0' && b[0] != '\0') {
		if (*a != *b)
			++ret;
		++a;
		++b;
	}
	return ret;
}

static void print_diff(const char *a, const char *b)
{
	while (a[0] != '\0' && b[0] != '\0') {
		if (a[0] == b[0])
			putchar(a[0]);
		else
			putchar(' ');
		++a;
		++b;
	}
	putchar('\n');
}

int main()
{
#ifdef one
	static int freq[256];
	static char buf[1024];
	int num3 = 0;
	int num2 = 0;
	while (fgets(buf, 1024, stdin)) {
		for (int i = 'a'; i <= 'z'; ++i) {
			freq[i] = 0;
		}
		for (const char *c = buf; c[0] != '\n'; ++c) {
			++freq[(unsigned char)c[0]];
		}
		bool exp2 = false;
		bool exp3 = false;
		for (int i = 'a'; i <= 'z'; ++i) {
			if (freq[i] == 2) {
				exp2 = true;
			} else if (freq[i] == 3) {
				exp3 = true;
			}
		}
		if (exp2) {
			++num2;
		}
		if (exp3) {
			++num3;
		}
	}
	printf("%d * %d = %d\n", num2, num3, (num3 * num2));
#endif
	std::string line;
	std::vector<std::string> ins;
	while (std::getline(std::cin, line)) {
		if (line.length() > 1)
			ins.push_back(line);
	}
	for (unsigned i = 0; i < ins.size(); ++i) {
		for (unsigned j = 0; j < i; ++j) { 
			int n = char_diff(ins[i].c_str(), ins[j].c_str());
			if (n == 1) {
				std::cout << ins[i] << " -- " << ins[j] << std::endl;
				print_diff(ins[i].c_str(), ins[j].c_str());
			}
		}
	}
}
