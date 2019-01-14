#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

#define FAST_ALLOC

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)
//#define N 468
//#define LAST 7101000
#define N 493
#define LAST 7186300
//#define LAST 71010
//#define N 30
//#define LAST 5808

typedef long long int lli;

struct node_t {
	int value;
	node_t *next;
	node_t *prev;
};

static lli players[N];
static node_t *alloc(int value) {
#ifdef FAST_ALLOC
	static node_t _nodes[LAST];
	static int which = 0;
	node_t *ret = _nodes + which;
	++which;
#else
	node_t *ret = new node_t;
#endif
	ret->value = value;
	ret->next = nullptr;
	ret->prev = nullptr;
	return ret;
}

static node_t *insert(node_t *node, int right, int value) {
	for (int i = 0; i < right; ++i) {
		node = node->next;
	}
	node_t *nn = alloc(value);
	nn->next = node->next;
	nn->prev = node;
	node->next->prev = nn;
	node->next = nn;
	return nn;
}

static int rm(node_t *node, int left, node_t **new_curr) {
	for (int i = 0; i < left; ++i) {
		node = node->prev;
	}
	int ret = node->value;
	new_curr[0] = node->next;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return ret;
}

#ifdef print_me
static void print(node_t *const node) {
	node_t *i = node;
	do {
		printf("%d ", i->value);
		i = i->next;
	} while (i != node);
	putchar('\n');
}
#endif

int main()
{
	for (int i = 0; i < N; ++i) {
		players[i] = 0;
	}
	node_t *curr = alloc(0);
	curr->next = curr;
	curr->prev = curr;
	for (int i = 1; i <= LAST; ++i) {
		if (i % 23 == 0) {
			lli *player = players + (i % N);
			player[0] += i;
			player[0] += rm(curr, 7, &curr);
		} else {
			curr = insert(curr, 1, i);
		}
#ifdef print_me
		print(curr);
#endif
	}
	lli biggest = 0;
	for (int i = 0; i < N; ++i) {
		if (players[i] > biggest) {
			biggest = players[i];
		}
	}
	trace("biggest = " << biggest);
}
