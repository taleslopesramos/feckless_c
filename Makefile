CC := cc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS := -lcriterion

SRC := $(wildcard src/*.c)
TEST_SRC := $(wildcard tests/*.c)

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

SRC_OBJ := $(patsubst src/%.c,$(OBJ_DIR)/src/%.o,$(SRC))
TEST_OBJ := $(patsubst tests/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_SRC))

TEST_BIN := $(BUILD_DIR)/tests

.PHONY: all test clean

all: $(TEST_BIN)

$(TEST_BIN): $(SRC_OBJ) $(TEST_OBJ)
	$(CC) $(SANFLAGS) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/src/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SANFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: tests/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(SANFLAGS) -c $< -o $@

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)