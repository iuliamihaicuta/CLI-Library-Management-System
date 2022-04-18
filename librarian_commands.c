#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Hashtable.h"
#include "utils.h"

#define MAX_LEN 256
#define HMAX 100
#define uint unsigned char
#define uchar unsigned char

hashtable_t *
add_book(hashtable_t *library)
{
    char book_name[40], def_nr;
    scanf("%s%d", book_name, &def_nr);

    hashtable_t *book = ht_create(def_nr, hash_function_string, compare_function_strings, sizeof(hashtable_t));
    for (uint i = 0; i < def_nr; ++i) {
        char name[20], value[20];
        scanf("%s%s", name, value);
        ht_put(book, name, strlen(name), value, sizeof(value));
    }

    ht_put(library, book_name, sizeof(book), book, sizeof(hashtable_t));

    return library;
}