// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Hashtable.h"
#include "librarian_commands.h"
#include "utils.h"

#define BOOK_NAME 40
#define LEN 20

// allocates memory for a book_t variable
book_t
new_book(int def_nr)
{
    if (def_nr == 0)
        ++def_nr;

    book_t book;

    book.purchase = 0;
    book.is_borrowed = 0;
    book.rating = 0;
    // creates a hashtable to stores definitions
    book.book = ht_create(def_nr, hash_function_string,
        compare_function_strings, &free_def);

    return book;
}

// read the name of the book in quotation marks
char *
read_name()
{
    char *name = calloc(BOOK_NAME, sizeof(char));
	char c;

	scanf("%c", &c);
	while (c == ' ')
		scanf("%c", &c);

	scanf("%c", &c);

	int i = 0;
	while (c != '"') {
		name[i] = c;
		++i;
		scanf("%c", &c);
	}
	name[i] = '\0';

    return name;
}

// adds a book to the library
hashtable_t *
add_book(hashtable_t *library)
{
    char *book_name;
    uint def_nr;
    book_name = read_name();
    scanf("%d", &def_nr);

    book_t book = new_book(def_nr);

    // if the book already exists, we remove it
    if (ht_has_key(library, book_name)) {
        rmv(library, book_name);
    }

    // adds the definitions in book.book
    for (uint i = 0; i < def_nr; ++i) {
        char name[20], value[20];
        scanf("%s%s", name, value);
        ht_put(book.book, name, strlen(name) + 1, value, strlen(value) + 1);
    }
    // adds book to library
    ht_put(library, book_name, strlen(book_name) + 1, &book, sizeof(book_t));

    free(book_name);
    return library;
}

void
get_book(hashtable_t *library)
{
    char *book_name;
    book_name = read_name();

    if (ht_has_key(library, book_name)) {
        // gets book from library
        book_t *book = (book_t *)(ht_get(library, book_name));

        float rating;
        // find the rating
        if (book->purchase)
            rating = book->rating / book->purchase;
        else
            rating = 0;


        printf("Name:%s Rating:%.3f Purchases:%d\n", book_name,
                rating, book->purchase);
    } else {
        printf("The book is not in the library.\n");
    }

    free(book_name);
}

void
rmv(hashtable_t *library, char *book_name)
{
    if (ht_has_key(library, book_name)) {
        // removes the entry
        ll_node_t *buff = ht_remove_entry(library, book_name);

        // frees the alocated memory
        free_book(buff->data);
        free(buff);
    } else {
        printf("The book is not in the library.\n");
    }
}

void
rmv_book(hashtable_t *library)
{
    char *book_name;
    book_name = read_name();

    // remove the given book from library
    rmv(library, book_name);

    free(book_name);
}

void
add_def(hashtable_t *library)
{
    char *book_name;
    book_name = read_name();

    char key[LEN], value[LEN];
    scanf("%s%s", key, value);

    // if the book exists, adds the definitions to it
    if (ht_has_key(library, book_name)) {
        book_t *book = (book_t *)(ht_get(library, book_name));
        ht_put(book->book, key, strlen(key) + 1, value, strlen(value) + 1);
    } else {
        printf("The book is not in the library.\n");
    }

    free(book_name);
}

void
get_def(hashtable_t *library)
{
    char *book_name, key[LEN];
    book_name = read_name();
    scanf("%s", key);

    // displays the definition if any
    if (ht_has_key(library, book_name)) {
        book_t *book = (book_t *)(ht_get(library, book_name));

        if (ht_has_key(book->book, key)) {
            char *value = (char *)(ht_get(book->book, key));
            printf("%s\n", value);
        } else {
            printf("The definition is not in the book.\n");
        }
    } else {
        printf("The book is not in the library.\n");
    }

    free(book_name);
}

void
rmv_def(hashtable_t *library)
{
    char *book_name, key[LEN];
    book_name = read_name();
    scanf("%s", key);

    // remove the definition if any
    if (ht_has_key(library, book_name)) {
        book_t *book = (book_t *)(ht_get(library, book_name));
        if (ht_has_key(book->book, key)) {
            ll_node_t *buff = ht_remove_entry(book->book, key);

            free_def(buff->data);
            free(buff);
        } else {
            printf("The definition is not in the book.\n");
        }
    } else {
        printf("The book is not in the library.\n");
    }

    free(book_name);
}

void
free_def(void *info_def)
{
    // frees definitions
    free(((info *)info_def)->key);
    free(((info *)info_def)->value);

    free(info_def);
}

void
free_book(void *info_book)
{
    // frees the memory alocated to a book
    book_t *book = ((info *)info_book)->value;
    ht_free(book->book);
    free(book);
    book = NULL;

    free(((info *)info_book)->key);
    free(info_book);
}
