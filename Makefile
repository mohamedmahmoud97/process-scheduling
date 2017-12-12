# Default to debugging flags. Set to -O3 if you want optimisations
# (either change it here, or type 'make CFLAGS=-O3' in the shell).
CFLAGS?=-g -Wall -Wno-unused-value

all: scheduling

reaction: scheduling.h scheduling.c
	$(CC) $(CFLAGS) -o scheduling scheduling.c 

run: scheduling
	./scheduling 0
	./scheduling 0
	./scheduling 20
	./scheduling 20
	./scheduling 40
	./scheduling 40

clean:
	$(RM) scheduling
	$(RM) -r *.dSYM
