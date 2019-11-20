CC = gcc
CFLAGS = -Wall -Wextra -Ofast -march=native
#LDLIBS = 

TARGETS = dmdelay

all: $(TARGETS)

dmdelay: dmdelay.o

clean:
	$(RM) *.o $(TARGETS)
