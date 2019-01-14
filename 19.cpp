#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

//#define one

static inline void assert(bool what)
{
	if (what)
		return;
	fprintf(stderr, "assert failed\n");
	exit(1);
}

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 0; i < to; ++i)

#define ADDR 0
#define ADDI 1
#define MULR 2
#define MULI 3
#define BANR 4
#define BANI 5
#define BORR 6
#define BORI 7
#define SETR 8
#define SETI 9
#define GTIR 10
#define GTRI 11
#define GTRR 12
#define EQIR 13
#define EQRI 14
#define EQRR 15

const char *const OP_STR[16] = {
	"addr",
	"addi",
	"mulr",
	"muli",
	"banr",
	"bani",
	"borr",
	"bori",
	"setr",
	"seti",
	"gtir",
	"gtri",
	"gtrr",
	"eqir",
	"eqri",
	"eqrr",
};

static int op_from_name(const char *str)
{
	FOR(i, 16) {
		if (strcmp(OP_STR[i], str) == 0)
			return i;
	}
	return -1;
}

#define oprr(how)(sto[o[3]] = (sto[o[1]] how sto[o[2]]))
#define opri(how)(sto[o[3]] = (sto[o[1]] how o[2]))
#define opir(how)(sto[o[3]] = (o[1] how sto[o[2]]))

struct tuple {
	int o[4];
	tuple() = default;
	tuple(int a, int b, int c, int d) {
		o[0] = a;
		o[1] = b;
		o[2] = c;
		o[3] = d;
	}
	int &operator[](int index) {
		return o[index];
	}
};

typedef std::vector<tuple> vec_t;

static inline void run(vec_t &op_list, int ip)
{
#ifdef one
	int sto[6] = { 0, 0, 0, 0, 0, 0 };
#else
	int sto[6] = { 1, 0, 0, 0, 0, 0 };
#endif
	while (sto[ip] >= 0 && sto[ip] < (int)op_list.size()) {
		tuple &o = op_list[sto[ip]];
		switch (o[0]) {
		case ADDR:
			oprr(+);
			break;
		case ADDI:
			opri(+);
			break;
		case MULR:
			oprr(*);
			break;
		case MULI:
			opri(*);
			break;
		case BANR:
			oprr(&);
			break;
		case BANI:
			opri(&);
			break;
		case BORR:
			oprr(|);
			break;
		case BORI:
			opri(|);
			break;
		case SETR:
			sto[o[3]] = sto[o[1]];
			break;
		case SETI:
			sto[o[3]] = o[1];
			break;
		case GTIR:
			opir(>);
			break;
		case GTRI:
			opri(>);
			break;
		case GTRR:
			oprr(>);
			break;
		case EQIR:
			opir(==);
			break;
		case EQRI:
			opri(==);
			break;
		case EQRR:
			oprr(==);
			break;
		default:
			trace("bad op == " << o[0]);
		}
		++sto[ip];
#ifndef one
		trace(sto[ip] << ": " << OP_STR[o[0]] << ' ' << o[1] << " " << o[2] << " " << o[3] << " :: " << sto[0] << ", " << sto[1] << ", " << sto[2] << ", " << sto[3] << ", " << sto[4] << ", " << sto[5]);
		char c = getchar();
		if (c >= '0' && c <= '5')
			sto[c - '0'] = 10551380;
#endif
		
	}
	trace("end: " << sto[0] << ", " << sto[1] << ", " << sto[2] << ", " << sto[3]);
}

static inline void run_file(FILE *f)
{
	int o[4];
	char ins_name[10];
	int ip;
	if (fscanf(f, "#ip %d\n", &ip) != 1) {
		trace("bad input");
		exit(1);
	}
	vec_t op_list;
	while (fscanf(f, "%s %d %d %d\n", ins_name, o + 1, o + 2, o + 3) == 4) {
		o[0] = op_from_name(ins_name);
		op_list.push_back({o[0], o[1], o[2], o[3]});
	}
	run(op_list, ip);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	FILE *f = fopen("in.txt", "r");
	run_file(f);
	fclose(f);
}
