CC := g++
CFLAGS := -Wall -Wextra -Wpedantic -Wshadow -std=c++11 -Ofast -march=native

MAKEFLAGS += Rr

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@.exe

.PHONY: clean

clean:
	rm -f *.exe
