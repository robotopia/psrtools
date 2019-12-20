CC = gcc
CFLAGS = -Wall -Wextra -Ofast -march=native
LDLIBS = -lpsrcat -lm

TARGETS = dmdelay \
		  nearby_pulsars

all: $(TARGETS)

dmdelay: dmdelay.o
nearby_pulsars: nearby_pulsars.o

clean:
	$(RM) *.o $(TARGETS)
