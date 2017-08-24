CC = gcc
LINK = $(CC)
AR = ar

BUILD = ./build
TEST = ./tests

CFLAGS = -std=gnu99 -g -Wall

TESTS = $(BUILD)/test_bitset

all: prebuild $(TESTS)

$(BUILD)/test_bitset: \
	$(BUILD)/test_bitset.o
	$(LINK) -o $(BUILD)/test_bitset $(BUILD)/test_bitset.o

$(BUILD)/test_bitset.o: \
	$(TEST)/test_bitset.c
	$(CC) -c $(CFLAGS) -o $(BUILD)/test_bitset.o $(TEST)/test_bitset.c

clean:
	rm -rf $(BUILD)

prebuild:
	test -d $(BUILD) || mkdir -p $(BUILD)

install: all
	test -d /usr/local/include/bitforce || mkdir -p /usr/local/include/bitforce
	cp src/*.h /usr/local/include/bitforce/
