CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c \
      src/database.c \
      src/file_handler.c \
      src/memory_manager.c \
      src/utils.c \
      src/export.c

OUT = build/student_db

all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -rf build/*
