// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <ctype.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"
#include "ranking.h"
#include "users_commands.h"
#include "librarian_commands.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
    char *name;
    int num;
    float rating;
} rank_t;

rank_t
new_userpoints(unsigned int data_size, char *data, int num, float rating)
{
    // initializes elements in array
    rank_t user;
    user.name = malloc(data_size);
    strcpy(user.name, data);

    user.num = num;

    if (num)
        user.rating = rating / num;
    else
        user.rating = 0;

    return user;
}

// compares strings
static int compare_names(const void* a, const void* b)
{
    return strcmp(((rank_t *)a)->name, ((rank_t *)b)->name);
}

// compare ints
static int compare_num(const void* a, const void* b)
{
    return ((rank_t *)b)->num - ((rank_t *)a)->num;
}

// compare floats
static int compare_rating(const void* a, const void* b)
{
    float x = ((rank_t *)b)->rating - ((rank_t *)a)->rating;

    if (x > 0)
        return 1;
    if (x < 0)
        return -1;

    return 0;
}


void
top_users(hashtable_t *users)
{
    rank_t *users_points = malloc(users->size * sizeof(rank_t));
    unsigned int nr = 0;

    // we go through the hashtable and save the data necessary
    // for comparison in the array
    unsigned int j = 0;
    for (unsigned int i = 0; i < users->size; ++i) {
        while (users->buckets[j]->head == NULL)
            ++j;

        ll_node_t *user = users->buckets[j]->head;

        while (user != NULL) {
            if (((user_t *)(((info *)user->data)->value))->points > 0) {
                users_points[nr] =
                    new_userpoints(strlen(((info *)user->data)->key) + 1,
                    ((info *)user->data)->key,
                    ((user_t *)(((info *)user->data)->value))->points, 0);

                // increasing the number of unbanned users
                ++nr;
            }

            user = user->next;
            ++i;
        }
        --i;
        ++j;
    }

    // sorts by name and points
    qsort(users_points, nr, sizeof(rank_t), compare_names);
    qsort(users_points, nr, sizeof(rank_t), compare_num);

    printf("Users ranking:\n");
    for (unsigned int i = 0; i < nr; ++i) {
        printf("%d. Name:%s Points:%d\n", i + 1, users_points[i].name,
                users_points[i].num);

        free(users_points[i].name);
    }

    free(users_points);
}

void
top_books(hashtable_t *library)
{
    rank_t *book_rating = malloc(library->size * sizeof(rank_t));

    // we go through the hashtable and save the data necessary
    // for comparison in the array
    unsigned int j = 0;
    for (unsigned int i = 0; i < library->size; ++i) {
        while (library->buckets[j]->head == NULL)
            ++j;

        ll_node_t *book = library->buckets[j]->head;

        while (book != NULL) {
            book_rating[i] =
                new_userpoints(strlen(((info *)book->data)->key) + 1,
                ((info *)book->data)->key,
                ((book_t *)(((info *)book->data)->value))->purchase,
                ((book_t *)(((info *)book->data)->value))->rating);

            book = book->next;
            ++i;
        }
        --i;
        ++j;
    }

    // sorts by names, number of acquisitions and rating
    qsort(book_rating, library->size, sizeof(rank_t), compare_names);
    qsort(book_rating, library->size, sizeof(rank_t), compare_num);
    qsort(book_rating, library->size, sizeof(rank_t), compare_rating);

    printf("Books ranking:\n");
    for (unsigned int i = 0; i < library->size; ++i) {
        printf("%d. Name:%s Rating:%.3f Purchases:%d\n", i + 1,
            book_rating[i].name, book_rating[i].rating, book_rating[i].num);

        free(book_rating[i].name);
    }

    free(book_rating);
}
