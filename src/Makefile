ifeq ($(detected_OS),Darwin)
	ifeq ($(CC),cl)
		CFLAGS_DEBUG=-O1 -Wall -Wextra -g -std=c99 -fsanitize=address -fno-omit-frame-pointer
	else
		CFLAGS_DEBUG=-Wall -Wextra -g -std=c99
	endif
else
	CFLAGS_DEBUG=-Wall -Wextra -g -std=c99
endif

CFLAGS_RELEASE=-Wall -Wextra -O2 -std=c99

ifndef CFLAGS
	ifeq ($(TARGET),Debug)
		CFLAGS=$(CFLAGS_DEBUG)
	else
		CFLAGS=$(CFLAGS_RELEASE)
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
