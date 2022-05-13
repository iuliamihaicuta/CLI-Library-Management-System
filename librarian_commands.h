// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef LIBRARIAN_COMMANDS_H_
#define LIBRARIAN_COMMANDS_H_

#include "LinkedList.h"
#include "Hashtable.h"

typedef struct book_t book_t;
struct book_t {
    hashtable_t *book;
    double rating;
    int purchase;
    int is_borrowed;
};

char *
read_name();

hashtable_t *
add_book(hashtable_t *library);

void
get_book(hashtable_t *library);

void
rmv(hashtable_t *library, char *book_name);

void
rmv_book(hashtable_t *library);

void
add_def(hashtable_t *library);

void
get_def(hashtable_t *library);

void
rmv_def(hashtable_t *library);

void
free_def(void *info_def);

void
free_book(void *info_book);

#endif  // LIBRARIAN_COMMANDS_H_
