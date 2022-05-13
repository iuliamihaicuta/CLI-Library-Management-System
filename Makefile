# Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g

# define targets
TARGETS=main

all: main

build: $(TARGETS)

main: main.c LinkedList.c Hashtable.c librarian_commands.c users_commands.c ranking.c
	$(CC) $(CFLAGS) main.c LinkedList.c Hashtable.c librarian_commands.c users_commands.c ranking.c -o main

clean:
	rm -f $(TARGETS)

