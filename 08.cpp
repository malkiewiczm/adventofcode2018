#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

struct node {
	std::vector<node> children;
	std::vector<int> meta;
	int meta_sum;
	void read() {
		int num_children, num_meta;
		scanf("%d", &num_children);
		scanf("%d", &num_meta);
		for (int i = 0; i < num_children; ++i) {
			node child;
			child.read();
			children.push_back(child);
		}
		meta_sum = 0;
		for (int i = 0; i < num_meta; ++i) {
			int v;
			scanf("%d", &v);
			meta.push_back(v);
			meta_sum += v;
		}
	}
	int meta_sum_all() const {
		int sum = meta_sum;
		for (auto item : children) {
			sum += item.meta_sum_all();
		}
		return sum;
	}
	int get_value() const {
		if (children.empty()) {
			return meta_sum;
		}
		int sum = 0;
		for (auto item : meta) {
			int index = item - 1;
			if (index >= 0 && index < (int)children.size()) {
				sum += children[index].get_value();
			}
		}
		return sum;
	}
};

int main()
{
	node file;
	file.read();
	trace("done reading");
	int n0 = file.meta_sum_all();
	int n1 = file.get_value();
	trace(n0);
	trace(n1);
}
