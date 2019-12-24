tournament: tournament.c
	gcc -std=c11 -Wall -Wextra -o tournament tournament.c

.PHONY: clean test

clean:
	rm -f tournament
test: tournament
	bats check.bats
