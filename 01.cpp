#include <stdio.h>
#include <set>
#include <vector>

int main() {
	char op;
	int n;
	std::vector<int> vec;
	while (scanf("%c%d\n", &op, &n) == 2) {
		if (op == '-')
			n = -n;
		vec.push_back(n);
	}
	std::set<int> set;
	int sum = 0;
	set.insert(0);
	for (int i = 0; ; ++i) {
		for (auto item : vec) {
			sum += item;
			if (set.find(sum) == set.end()) {
				set.insert(sum);
			} else {
				printf("ans = %d (i = %d)\n", sum, i);
				return 0;
			}
		}
	}
}
