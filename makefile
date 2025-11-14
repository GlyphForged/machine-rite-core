CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Iinclude
SRC_DIR = src
BUILD_DIR = build

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/vectrum.c # Add more as we go.
OBJS = $(SRC:.c=.o)
TARGET = $(BUILD_DIR)/mr_demo

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(BUILD_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(SRC_DIR)/*.o

.PHONY: all clean
