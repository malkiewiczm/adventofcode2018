#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i) {
		int d;
		int ret = sscanf(argv[i], "%i", &d);
		if (ret == 1)
			printf("%d = 0x%x\n", d, d);
	}
}
