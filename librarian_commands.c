#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Hashtable.h"
#include "librarian_commands.h"
#include "utils.h"

#define MAX_LEN 256
#define BOOK_NAME 40
#define KEY_LEN 20
#define HMAX 100

book_t *
alloc_book(uint def_nr)
{
    book_t *book = (book_t *)malloc(sizeof(book_t));

    book->purchase = 0;
    book->rating = 0;

    book->book = ht_create(def_nr, hash_function_string, compare_function_strings, sizeof(hashtable_t));

    return book;
}

hashtable_t *
add_book(hashtable_t *library)
{
    char book_name[BOOK_NAME];
    uint def_nr;
    scanf("%s %d", book_name, &def_nr);

    book_t *book = alloc_book(def_nr);

    book->book = ht_create(HMAX, hash_function_string, compare_function_strings, KEY_LEN * sizeof(char) + 1);
    for (uint i = 0; i < def_nr; ++i) {
        char name[20], value[20];
        scanf("%s%s", name, value);
        ht_put(book->book, name, strlen(name) + 1, value, strlen(value) + 1);
    }

    printf("%d %f\n", book->purchase, book->rating);

    ht_put(library, book_name, sizeof(book), &book, sizeof(book_t **));

    return library;
}

void
get_book(hashtable_t *library)
{
    char book_name[BOOK_NAME];
    scanf("%s", book_name);

    if (ht_has_key(library, book_name)) {
        book_t **book = (ht_get(library, book_name));
        printf("ok\n");

        printf("Nume: %s\tRating:%f\tPurchase:%d\n", book_name, (*book)->rating, (*book)->purchase);
    } else {
        printf("The book is not in the library.\n");
    }
}