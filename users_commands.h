// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef USERS_COMMANDS_H_
#define USERS_COMMANDS_H_
#include <stdbool.h>

#include "Hashtable.h"

typedef struct user_t user_t;
struct user_t {
    char *book_name;
    int days;
    bool has_book;
    int points;
};

user_t
new_user();

void
add_user(hashtable_t *users);

void
borrow_book(hashtable_t *library, hashtable_t *users);

void
return_book(hashtable_t *library, hashtable_t *users);

void
lost_book(hashtable_t *users, hashtable_t *library);

void
free_user(void *info_user);

#endif  // USERS_COMMANDS_H_
