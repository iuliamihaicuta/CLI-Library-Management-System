#ifndef LIBRARIAN_COMMANDS_H_
#define LIBRARIAN_COMMANDS_H_

#include "LinkedList.h"
#include "Hashtable.h"

typedef struct book_t book_t;
struct book_t {
    hashtable_t *book;
    double rating;
    int purchase;
};


hashtable_t *
add_book(hashtable_t *library);

void
get_book(hashtable_t *library);

#endif