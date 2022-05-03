#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Hashtable.h"
#include "librarian_commands.h"
#include "utils.h"

#define MAX_LEN 256
#define HMAX 100

// check that the command is entered correctly
int
validate_command(uint nr_arg, uint *idx1, uint *idx2)
{
	char line[MAX_LEN];
	fgets(line, MAX_LEN, stdin);

	line[strlen(line) - 1] = '\0';

	// divides the line into arguments and checks their number
	char *buff;
	buff = strtok(line, " ");
	if (buff == NULL) {
		if (nr_arg == 0)
			return 1;
		return 0;
	} else if (nr_arg == 0) {
		return 0;
	}

	*idx1 = atoi(buff);

	buff = strtok(NULL, " ");
	if (buff == NULL) {
		if (nr_arg == 1)
			return 1;
		return 0;
	} else if (nr_arg == 1) {
		return 0;
	}

	*idx2 = atoi(buff);

	buff = strtok(NULL, " ");
		if (buff != NULL)
			return 0;

	return 1;
}

int main(void)
{
    char command[MAX_LEN];
    hashtable_t *library = ht_create(HMAX, hash_function_string, compare_function_strings, sizeof(book_t **));

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "ADD_BOOK") == 0)
            add_book(library);
		else if (strcmp(command, "GET_BOOK") == 0)
			get_book(library);
    }
}