CFLAGS=-O3 -Wall -ansi # Entrega
#CFLAGS=-O3 -Wall -Wextra -pedantic -ansi
#CFLAGS=-Wall -Wextra -pedantic -ansi
#CFLAGS=-g -pg -Wall -Wextra -pedantic -ansi
#CFLAGS=-g -Wall -Wextra -pedantic -ansi
CPPFLAGS=-MP -MMD
LDFLAGS=
CC=gcc
SRC=$(wildcard *.c)
EXEC=wordmorph

all:
	make $(EXEC)
	rm -rf *.d

$(EXEC): $(SRC:%.c=%.o)
# This will implicity make all the .c files with *FLAGS and with
# dependencies generated automatically by CPPFLAGS, included below (.d files)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

-include $(SRC:%.c=%.d)

clean:
	rm -rf *.o *.d *.out* $(EXEC)

# This rebuilds everything if the Makefile was modified
# http://stackoverflow.com/questions/3871444/making-all-rules-depend-on-the-makefile-itself/3892826#3892826
-include .dummy
.dummy: Makefile
	touch $@
	$(MAKE) -s clean

# TODO: criar make test: automatizar memcheck, massif e gprof
