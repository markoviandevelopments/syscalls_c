CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGETS = file_syscall

all: $(TARGETS)

file_syscall: file_syscall.c
	$(CC) $(CFLAGS) file_syscall.c -o file_syscall

clean:
	rm -f $(TARGETS)

.PHONY: all clean