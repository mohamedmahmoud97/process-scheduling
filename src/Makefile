# Default to debugging flags. Set to -O3 if you want optimisations
# (either change it here, or type 'make CFLAGS=-O3' in the shell).
CFLAGS?=-g -Wall -Wno-unused-value

all: scheduling

scheduling: scheduling.h scheduling.c
	$(CC) $(CFLAGS) -o scheduling scheduling.c 

run: scheduling
	./scheduling 0 sample
	./scheduling 1 1 sample

clean:
	$(RM) scheduling
	$(RM) -r *.dSYM
