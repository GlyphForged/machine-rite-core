CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

#Library sources
LIB_SRC = $(SRC_DIR)/vectrum.c
LIB_OBJS = $(LIB_SRC:.c=.o)

#App source
APP_SRC = $(SRC_DIR)/main.c
APP_OBJS = $(APP_SRC:.c=.o)

# Test sources
TEST_SRC = $(TEST_DIR)/test_main.c $(TEST_DIR)/test_vectrum.c
TEST_OBJS = $(TEST_SRC:.c=.o)

#Binaries
TARGET = $(BUILD_DIR)/mr_demo
TEST_TARGET = $(BUILD_DIR)/tests

# Default: Build the app
all: $(TARGET)

# Make sure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link main demo
$(TARGET): $(BUILD_DIR) $(APP_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) $(APP_OBJS) $(LIB_OBJS) -o $(TARGET)

$(TEST_TARGET): $(BUILD_DIR) $(TEST_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_OBJS) -o $(TEST_TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(TEST_TARGET)

test: tests
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(SRC_DIR)/*.o $(TEST_DIR)/*.o

.PHONY: all clean test tests
