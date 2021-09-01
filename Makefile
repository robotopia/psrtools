CC = gcc
CFLAGS = -Wall -Wextra -Ofast -march=native
LDLIBS = -lpsrcat -lm

TARGETS = dmdelay \
		  libpsrtools.a
		  #nearby_pulsars

all: $(TARGETS)

dmdelay: dmdelay.o dm.o
nearby_pulsars: nearby_pulsars.o

libpsrtools.a: dm.o
	$(AR) rcs $@ $^

clean:
	$(RM) *.o $(TARGETS)
