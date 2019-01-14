#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>

#define trace(what)(std::cout << "[line " << __LINE__ << "] " << what << std::endl)

struct node_t {
	int x, y;
	node_t *up;
	node_t *down;
	node_t *left;
	node_t *right;
	char form;
};

#define UP 0
#define DOWN 1
#define LEFT 2 
#define RIGHT 3

#define TURN_LEFT 0
#define TURN_STRAIGHT 1
#define TURN_RIGHT 2

struct cart_t {
	node_t *where;
	int dir;
	int turn;
	bool failed;
	cart_t() = default;
	cart_t(node_t *_where, int _dir)
		: where(_where), dir(_dir), turn(-1), failed(false)
	{}
	void update() {
		switch (where->form) {
		case '-':
			where = dir == RIGHT ? where->right : where->left;
			break;
		case '|':
			where = dir == DOWN ? where->down : where->up;
			break;
		case '/':
			switch (dir) {
			case UP:
				where = where->right;
				dir = RIGHT;
				break;
			case DOWN:
				where = where->left;
				dir = LEFT;
				break;
			case LEFT:
				where = where->down;
				dir = DOWN;
				break;
			default:
				where = where->up;
				dir = UP;
			}
			break;
		case '\\':
			switch (dir) {
			case UP:
				where = where->left;
				dir = LEFT;
				break;
			case DOWN:
				where = where->right;
				dir = RIGHT;
				break;
			case LEFT:
				where = where->up;
				dir = UP;
				break;
			default:
				where = where->down;
				dir = DOWN;
			}
			break;
		case '+':
			turn = (turn + 1) % 3;
			switch (turn) {
			case TURN_RIGHT:
				switch (dir) {
				case UP:
					where = where->right;
					dir = RIGHT;
					break;
				case DOWN:
					where = where->left;
					dir = LEFT;
					break;
				case LEFT:
					where = where->up;
					dir = UP;
					break;
				default:
					where = where->down;
					dir = DOWN;
				}
				break;
			case TURN_LEFT:
				switch (dir) {
				case UP:
					where = where->left;
					dir = LEFT;
					break;
				case DOWN:
					where = where->right;
					dir = RIGHT;
					break;
				case LEFT:
					where = where->down;
					dir = DOWN;
					break;
				default:
					where = where->up;
					dir = UP;
				}
				break;
			default:
				switch (dir) {
				case UP:
					where = where->up;
					break;
				case DOWN:
					where = where->down;
					break;
				case LEFT:
					where = where->left;
					break;
				default:
					where = where->right;
				}
			}
			break;
		default:
			trace("panic --> " << where->form);
			exit(1);
		}
	}
	bool operator==(const cart_t &rhs) const {
		return where == rhs.where;
	}
	bool operator<(const cart_t &rhs) const {
		if (where->y != rhs.where->y)
			return where->y < rhs.where->y;
		return where->x < rhs.where->x;
	}
};

static std::ostream &operator<<(std::ostream &o, const cart_t &cart)
{
	o << cart.where->x << ", " << cart.where->y << " (";
	switch (cart.dir) {
	case UP:
		o << "UP";
		break;
	case DOWN:
		o << "DOWN";
		break;
	case LEFT:
		o << "LEFT";
		break;
	default:
		o << "RIGHT";
	}
	o << ")";
	return o;
}

#define FOR(i, to) for (unsigned i = 0; i < to; ++i)

int main(int argc, char **argv)
{
	const char *fname = "in.txt";
	if (argc >= 2)
		fname = argv[1];
	std::vector<cart_t> carts;
	FILE *f = fopen(fname, "r");
	if (f == nullptr) {
		trace("file cannot be open");
		exit(1);
	}
	static char grid[256][256];
	unsigned height = 0;
	unsigned width = 0;
	while (fgets(grid[height], 256, f)) {
		width = std::max(width, strlen(grid[height]) - 1);
		++height;
	}
	static node_t nodes[256][256];
	FOR(y, height) {
		FOR(x, width) {
			char form = grid[y][x];
			switch (grid[y][x]) {
			case '^':
				carts.emplace_back(&nodes[y][x], UP);
				form = '|';
				break;
			case 'V':
			case 'v':
				carts.emplace_back(&nodes[y][x], DOWN);
				form = '|';
				break;
			case '<':
				carts.emplace_back(&nodes[y][x], LEFT);
				form = '-';
				break;
			case '>':
				carts.emplace_back(&nodes[y][x], RIGHT);
				form = '-';
				break;
			}
			nodes[y][x].x = x;
			nodes[y][x].y = y;
			nodes[y][x].form = form;
			nodes[y][x].up = &nodes[y - 1][x];
			nodes[y][x].down = &nodes[y + 1][x];
			nodes[y][x].left = &nodes[y][x - 1];
			nodes[y][x].right = &nodes[y][x + 1];
		}
	}
	fclose(f);
	unsigned num_failed = 0;
	for (int step = 1; ; ++step) {
		std::sort(carts.begin(), carts.end());
		bool done = false;
		FOR(i, carts.size()) {
			cart_t &cart = carts[i];
			if (cart.failed)
				continue;
			cart.update();
			FOR(j, carts.size()) {
				if (i == j)
					continue;
				if (carts[j].failed)
					continue;
				if (cart == carts[j]) {
					cart.failed = true;
					carts[j].failed = true;
					num_failed += 2;
					trace("crash at " << cart);
					if (num_failed == carts.size() - 1) {
						trace("done at step " << step);
						done = true;
					}
					break;
				}
			}
		}
		if (done)
			break;
	}
	for (auto cart : carts) {
		if (cart.failed)
			continue;
		trace(cart << " did not crash");
	}
}

