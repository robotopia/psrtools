CC = gcc
CFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -lgcov -lm --coverage

TARGETS = dm_TEST

all_TESTS: $(TARGETS)

run_dm_TEST: dm_TEST
	./$<
	
dm_TEST: dm_TEST.o dm.o vec.o
