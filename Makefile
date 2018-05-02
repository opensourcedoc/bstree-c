CC=gcc
RM=rm
RMFLAG=-rf
SOURCE_DIR=src
TEST_DIR=test
TARGET=test_bstree.out
SRC_OBJS := $(echo $(SOURCE_DIR)/*.o)

.PHONY: clean test

memo: compile
	make -C $(TEST_DIR) memo

test: compile
	make -C $(TEST_DIR) test

compile: $(SOURCE_DIR)/*.o

crline:
	perl -pi -e "s{\$+$$}{}g;" *

$(SOURCE_DIR)/*.o:
	make -C $(SOURCE_DIR)

clean:
	$(RM) $(RMFLAG) $(TEST_DIR)/$(TARGET) $(SOURCE_DIR)/*.o $(TEST_DIR)/*.o
