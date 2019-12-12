ifeq ($(detected_OS),Darwin)
	ifeq ($(CC),clang)
		CFLAGS_DEBUG=-O1 -Wall -Wextra -g -std=c11 -fsanitize=address -fno-omit-frame-pointer
	else
		CFLAGS_DEBUG=-Wall -Wextra -g -std=c11
	endif
else
	CFLAGS_DEBUG=-Wall -Wextra -g -std=c11
endif

CFLAGS_RELEASE=-Wall -Wextra -O2 -std=c11

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

STATIC_LIB=libalgobstreei.a

DIST_DIR=../dist


.PHONY: all compile_debug compile trim clean

all: dynamic

dynamic:
	for f in `ls *.c`; do \
		$(CC) $(CFLAGS) -fPIC -c $$f -I../include; \
	done
	$(CC) $(CFLAGS) -shared -o $(DIST_DIR)/$(DYNAMIC_LIB) *.o -I../include

static: compile
ifeq ($(detected_OS),Darwin)
	libtool -static -o $(DIST_DIR)/$(STATIC_LIB) *.o
else
	$(AR) rcs -o $(DIST_DIR)/$(STATIC_LIB) *.o
endif

compile_debug: CFLAGS := $(CFLAGS_DEBUG)
compile_debug: compile

compile: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include

trim:
	perl -lpi -e "s{\s+$$}{}g;" *

clean:
	$(RM) $(DIST_DIR)/$(DYNAMIC_LIB) $(DIST_DIR)/$(STATIC_LIB) -- *.obj *.o
