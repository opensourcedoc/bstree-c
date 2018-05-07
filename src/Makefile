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

ifeq ($(detected_OS),Darwin)
	DYNAMIC_LIB=libalgobstreei.dylib
else
	DYNAMIC_LIB=libalgobstreei.so
endif

.PHONY: all compile_debug compile trim clean

all: dynamic

dynamic:
	for f in `ls *.c`; do \
		$(CC) $(CFLAGS) -fPIC -c $$f -I../include; \
	done
	$(CC) $(CFLAGS) -shared -o $(DYNAMIC_LIB) *.o -I../include

static: compile
	$(AR) rcs -o libalgobstreei.a *.o

compile_debug: CFLAGS := $(CFLAGS_DEBUG)
compile_debug: compile

compile: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include

trim:
	perl -lpi -e "s{\s+$$}{}g;" *

clean:
	$(RM) $(DYNAMIC_LIB) libalgobstreei.a *.obj *.o
