#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <tuple>
#include <limits.h>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

static int djb_hash(const char *c)
{
	int ret = 5381;
	while (*c) {
		ret = ((ret << 5) + ret) + *c;
		++c;
	}
	return ret;
}

#define contains(s, what)(s.find(what) != s.end())

struct group_t;
static inline std::ostream &operator<< (std::ostream &, const group_t *);

static int boost = 1570;

struct group_t {
	bool evil;
	int n;
	int hp;
	std::set<int> weak;
	std::set<int> immune;
	int attack_mode;
	int attack_amt;
	int rank;
	int power() const {
		if (evil)
			return n * attack_amt;
		else
			return n * (attack_amt + boost);
	}
	bool dead() const {
		return n == 0;
	}
	bool selected;
	group_t *target;
	void reset() {
		selected = false;
		target = nullptr;
	}
	int damage_est(const group_t *o) const {
		if (o == nullptr) {
			trace("problem: damage_est against null");
			exit(1);
		}
		if (contains(o->immune, attack_mode))
			return 0;
		int ret = power();
		if (contains(o->weak, attack_mode))
			ret *= 2;
		return ret;
	}
	int attack_target() {
		if (target == nullptr)
			return 0;
		const int dmg = damage_est(target);
		const int units_dead = dmg / target->hp;
		int tdmg = target->n;
		target->n -= units_dead;
		if (target->n < 0)
			target->n = 0;
		tdmg -= target->n;
#ifdef print_attacks
		trace(this << " kills " << tdmg << " of " << target << " (" << dmg << ")");
#endif
		return tdmg;
	}
};

static inline std::ostream &operator<< (std::ostream &o, const group_t *rhs)
{
	if (rhs)
		o  << (rhs->evil ? "evil" : "good") << rhs->rank;
	else
		o << "(null)";
	return o;
}

//#define SAMPLE
#define JOE
#include "day24.hpp"

#define FOR for (group_t** iter = groups; iter != groups + GROUP_COUNT; ++iter)
#define g (*iter)
#define group_sort(cmp)(std::sort(groups, groups + GROUP_COUNT, cmp))

static bool by_power(const group_t *lhs, const group_t *rhs)
{
	if (lhs->power() != rhs->power())
		return lhs->power() > rhs->power();
	return lhs->rank > rhs->rank;
}

static bool by_rank(const group_t *lhs, const group_t *rhs)
{
	return lhs->rank > rhs->rank;
}

static void get_target(group_t *me)
{
	group_t *ret = nullptr;
	FOR {
		if (g->dead())
			continue;
		if (me->evil == g->evil || g->selected)
			continue;
		if (ret == nullptr) {
			ret = g;
			continue;
		}
		std::tuple<int, int, int> rt = std::make_tuple(me->damage_est(ret), ret->power(), ret->rank);
		std::tuple<int, int, int> gt = std::make_tuple(me->damage_est(g), g->power(), g->rank);
		if (gt > rt)
			ret = g;
	}
	if (ret == nullptr)
		return;
	if (me->damage_est(ret) == 0)
		return;
	me->target = ret;
	ret->selected = true;
}

static void count_alive(int &evil, int &good)
{
	evil = 0;
	good = 0;
	FOR {
		if (g->dead())
			continue;
		if (g->evil)
			++evil;
		else
			++good;
	}
}

bool go(int *ans)
{
	for (int i = 0; i < GROUP_COUNT; ++i) {
		groups_working[i] = groups_solid[i];
	}
	*ans = -1;
	bool winner = false;
	int stall_count = 0;
	for ( ; ; ) {
		FOR {
			if (g->dead())
				continue;
			g->reset();
		}
		group_sort(by_power);
		FOR {
			if (g->dead())
				continue;
			get_target(g);
		}
		group_sort(by_rank);
		int dmg = 0;
		FOR {
			if (g->dead())
				continue;
			dmg += g->attack_target();
		}
		if (dmg == 0) {
			++stall_count;
			if (stall_count > 10)
				return true;
		}
		int evil_left, good_left;
		count_alive(evil_left, good_left);
		if (evil_left == 0) {
			winner = false;
			break;
		}
		if (good_left == 0) {
			winner = true;
			break;
		}
	}
	*ans = 0;
	FOR {
		if (g->evil == winner) {
			*ans += g->n;
		}
	}
	return winner;
}

int main()
{
	init();
	for (int i = 0; i < GROUP_COUNT; ++i) {
		groups[i] = groups_working + i;
	}
	boost = 0;
	int ans;
	while (go(&ans)) {
		++boost;
	}
	trace("ans = " << ans);
	trace("boost = " << boost);
}
