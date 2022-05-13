// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "librarian_commands.h"
#include "utils.h"
#include "users_commands.h"
#include "ranking.h"

#define MAX_LEN 20
#define HMAX 10

int main(void)
{
	char command[MAX_LEN];
    hashtable_t *library = ht_create(HMAX, hash_function_string,
			compare_function_strings, &free_book);
	hashtable_t *users = ht_create(HMAX, hash_function_string,
			compare_function_strings, &free_user);

	// calls the desired function depending on the command
	while (1) {
        scanf("%s", command);
        if (strcmp(command, "ADD_BOOK") == 0) {
            add_book(library);
		} else if (strcmp(command, "GET_BOOK") == 0) {
			get_book(library);
		} else if (strcmp(command, "RMV_BOOK") == 0) {
			rmv_book(library);
		} else if (strcmp(command, "ADD_DEF") == 0) {
			add_def(library);
		} else if (strcmp(command, "GET_DEF") == 0) {
			get_def(library);
		} else if (strcmp(command, "RMV_DEF") == 0) {
			rmv_def(library);
		} else if (strcmp(command, "ADD_USER") == 0) {
			add_user(users);
		} else if (strcmp(command, "BORROW") == 0) {
			borrow_book(library, users);
		} else if (strcmp(command, "RETURN") == 0) {
			return_book(library, users);
		} else if (strcmp(command, "LOST") == 0) {
			lost_book(users, library);
		} else if (strcmp(command, "EXIT") == 0) {
			break;
		}
    }

	// displays user and book rankings
	top_books(library);
	top_users(users);

	// frees the alocated memory
	ht_free(library);
	ht_free(users);

	return 0;
}
