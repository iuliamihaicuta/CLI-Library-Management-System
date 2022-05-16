// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "librarian_commands.h"
#include "utils.h"
#include "users_commands.h"

#define BOOK_NAME 40
#define LEN 20

user_t
new_user()
{
    user_t user;
    user.has_book = 0;
    user.points = 100;
    user.book_name = NULL;

    return user;
}

void
add_user(hashtable_t *users)
{
    char user_name[LEN];
    scanf("%s", user_name);

    if (ht_has_key(users, user_name)) {
        printf("User is already registered.\n");
    } else {
        // adds user to the sistem
        user_t user = new_user();
        ht_put(users, user_name, strlen(user_name) + 1,
                &user, sizeof(user));
    }
}

void
borrow_book(hashtable_t *library, hashtable_t *users)
{
    char user_name[LEN], *book_name;
    scanf("%s", user_name);
    book_name = read_name();

    int days;
    scanf("%d", &days);

    if (ht_has_key(users, user_name)) {
        user_t *user = (user_t *)(ht_get(users, user_name));

        // checks if the operation can be executed
        if (user->points < 0) {
            printf("You are banned from this library.\n");
            goto end;
        }
        if (user->has_book) {
            printf("You have already borrowed a book.\n");
            goto end;
        }

        if (ht_has_key(library, book_name)) {
            book_t *book = (book_t *)(ht_get(library, book_name));
            if (book->is_borrowed) {
                printf("The book is borrowed.\n");
                goto end;
            } else {
                // sets the book as borrowed
                book->is_borrowed = 1;
                user->has_book = 1;
                user->days = days;

                user->book_name = malloc(strlen(book_name) + 1);
                strcpy(user->book_name, book_name);
            }
        } else {
            printf("The book is not in the library.\n");
            goto end;
        }
    } else {
        printf("You are not registered yet.\n");
    }
end:

    free(book_name);
}

void
return_book(hashtable_t *library, hashtable_t *users)
{
    char user_name[LEN], *book_name;
    int days_since_borrow;
    double rating;

    scanf("%s", user_name);
    book_name = read_name();
    scanf("%d%lf", &days_since_borrow, &rating);

    // checks if the operation can be executed
    user_t *user = (user_t *)(ht_get(users, user_name));
    if (user->points < 0) {
        printf("You are banned from this library.\n");
        goto end;
    }

    if (user->has_book == 0 || strcmp(user->book_name, book_name) != 0) {
        printf("You didn't borrow this book.\n");
        goto end;
    }

    book_t *book = (book_t *)(ht_get(library, book_name));
    book->is_borrowed = 0;
    book->rating += rating;
    ++(book->purchase);
    user->has_book = 0;

    free(user->book_name);
    user->book_name = NULL;

    // adds points to user
    if (user->days - days_since_borrow > 0) {
        user->points += user->days - days_since_borrow;
    } else {
        user->points = user->points + 2 * (user->days - days_since_borrow);

        if (user->points < 0) {
            printf("The user %s has been banned from this library.\n",
                    user_name);
            goto end;
        }
    }
end:

    free(book_name);
}

void
lost_book(hashtable_t *users, hashtable_t *library)
{
    char user_name[LEN], *book_name;
    scanf("%s", user_name);
    book_name = read_name();

    if (ht_has_key(users, user_name)) {
        user_t *user = (user_t *)(ht_get(users, user_name));

        if (user->points < 0) {
            printf("You are banned from this library.\n");
        } else if (ht_has_key(library, book_name)) {
            // removes book from library
            rmv(library, book_name);
            user->points -= 50;
            user->has_book = 0;

            free(user->book_name);
            user->book_name = NULL;

            if (user->points < 0)
                printf("The user %s has been banned from this library.\n",
                        user_name);
        }
    } else {
        printf("You are not registered yet.\n");
    }

    free(book_name);
}

void
free_user(void *info_user)
{
    // frees the memory alocated to user
    user_t *user = ((info *)info_user)->value;

    if (user->book_name)
        free(user->book_name);
    free(user);

    free(((info *)info_user)->key);
    free(info_user);
}
