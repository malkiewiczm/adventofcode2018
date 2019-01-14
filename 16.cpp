#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>

static inline void assert(bool what)
{
	if (what)
		return;
	fprintf(stderr, "assert failed\n");
	exit(1);
}

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

#define FOR(i, to) for (int i = 0; i < to; ++i)

#define possible_reg(i)(o[i] >= 0 && o[i] <= 3)
#define rr(op)((b[o[1]] op b[o[2]]) == a[o[3]])
#define ri(op)((b[o[1]] op o[2]) == a[o[3]])
#define ir(op)((o[1] op b[o[2]]) == a[o[3]])

#ifdef ONE

static inline int my_count(int *b, int *o, int *a)
{
	int ret = 0;
	if (possible_reg(1) && possible_reg(2)) {
		// register register
		if (rr(+))
			++ret;
		if (rr(*))
			++ret;
		if (rr(&))
			++ret;
		if (rr(|))
			++ret;
		if (b[o[1]] == a[o[3]])
			++ret;
		if (rr(>))
			++ret;
		if (rr(==))
			++ret;
	}
	if (possible_reg(1)) {
		// register immediate
		if (ri(+))
			++ret;
		if (ri(*))
			++ret;
		if (ri(&))
			++ret;
		if (ri(|))
			++ret;
		if (ri(>))
			++ret;
		if (ri(==))
			++ret;
	}
	if (possible_reg(2)) {
		// immediate register
		if (ir(>))
			++ret;
		if (ir(==))
			++ret;
	}
	if (possible_reg(3)) {
		if (o[1] == a[o[3]])
			++ret;
	}
	return ret;
}

static inline void go(FILE *f)
{
	int before[4];
	int op[4];
	int after[4];
	int matching = 0;
	int total = 0;
	while (fscanf(f, "Before: [%d, %d, %d, %d]\n", before, before + 1, before + 2, before + 3) == 4) {
		assert(fscanf(f, "%d %d %d %d\n", op, op + 1, op + 2, op + 3) == 4);
		assert(fscanf(f, "After: [%d, %d, %d, %d]\n", after, after + 1, after + 2, after + 3) == 4);
		int ret = my_count(before, op, after);
		if (ret >= 3)
			++matching;
		++total;
	}
	trace("matching = " << matching << " / " << total);
}

#else

static int exclude[16][16];
static int op_map[16];

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
	"ADDR",
	"ADDI",
	"MULR",
	"MULI",
	"BANR",
	"BANI",
	"BORR",
	"BORI",
	"SETR",
	"SETI",
	"GTIR",
	"GTRI",
	"GTRR",
	"EQIR",
	"EQRI",
	"EQRR",
};

#define meta(what)(++exclude[o[0]][what])

static inline void my_count(int *b, int *o, int *a)
{
	if (possible_reg(1) && possible_reg(2)) {
		// register register
		if (rr(+))
			meta(ADDR);
		if (rr(*))
			meta(MULR);
		if (rr(&))
			meta(BANR);
		if (rr(|))
			meta(BORR);
		if (rr(>))
			meta(GTRR);
		if (rr(==))
			meta(EQRR);
	}
	if (possible_reg(1)) {
		// register immediate
		if (ri(+))
			meta(ADDI);
		if (ri(*))
			meta(MULI);
		if (ri(&))
			meta(BANI);
		if (ri(|))
			meta(BORI);
		if (ri(>))
			meta(GTRI);
		if (ri(==))
			meta(EQRI);
	}
	if (possible_reg(2)) {
		// immediate register
		if (ir(>))
			meta(GTIR);
		if (ir(==))
			meta(EQIR);
	}
	if (possible_reg(3)) {
		if (possible_reg(1)) {
			if (b[o[1]] == a[o[3]])
				meta(SETR);
		}
		if (o[1] == a[o[3]])
			meta(SETI);
	}
}

static inline void one(FILE *f)
{
	int before[4];
	int op[4];
	int after[4];
	while (fscanf(f, "Before: [%d, %d, %d, %d]\n", before, before + 1, before + 2, before + 3) == 4) {
		assert(fscanf(f, "%d %d %d %d\n", op, op + 1, op + 2, op + 3) == 4);
		assert(fscanf(f, "After: [%d, %d, %d, %d]\n", after, after + 1, after + 2, after + 3) == 4);
		my_count(before, op, after);
	}
	FOR(i, 16) {
		op_map[i] = -1;
	}
	FOR(outer, 16) {
		FOR(i, 16) {
			int *where = std::max_element(exclude[i], exclude[i] + 16);
			int amt = std::count(exclude[i], exclude[i] + 16, where[0]);
			if (amt == 1) {
				int n = where - exclude[i];
				op_map[i] = n;
				FOR(k, 16) {
					exclude[k][n] = 0;
				}
			}
		}
	}
	FOR(i, 16) {
		trace(i << " = " << op_map[i]);
	}
}

#define oprr(how)(sto[o[3]] = (sto[o[1]] how sto[o[2]]))
#define opri(how)(sto[o[3]] = (sto[o[1]] how o[2]))
#define opir(how)(sto[o[3]] = (o[1] how sto[o[2]]))

static inline void two(FILE *f)
{
	int o[4];
	//int sto[4] = { -1, -1, -1, -1 };
	int sto[4] = { 0, 0, 0, 0 };
	while (fscanf(f, "%d %d %d %d", o, o + 1, o + 2, o + 3) == 4) {
		int op = op_map[o[0]];
		//trace(OP_STR[op]);
		switch (op) {
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
			trace("bad op == " << op);
		}
		/*
		trace(OP_STR[op] << ' ' << o[1] << o[2] << o[3] << " :: " << sto[0] << ", " << sto[1] << ", " << sto[2] << ", " << sto[3]);
		getchar();
		*/
	}
	trace(sto[0] << ", " << sto[1] << ", " << sto[2] << ", " << sto[3]);
	trace("answer is not 474, 471");
}

#endif

int main()
{
	std::ios_base::sync_with_stdio(false);
	FILE *f = fopen("in.txt", "r");
	one(f);
	two(f);
	fclose(f);
}
