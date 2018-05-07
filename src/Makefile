ifndef CFLAGS
	ifeq ($(TARGET),Debug)
		CFLAGS=-Wall -Wextra -g -std=c99
	else
		CFLAGS=-Wall -Wextra -O2 -std=c99
	endif
endif

OBJS=bstree.o bstnode.o bstiter.o

.PHONY: all compile trim clean

all: compile

compile: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include

trim:
	perl -lpi -e "s{\s+$$}{}g;" *

clean:
	$(RM) *.obj *.o
