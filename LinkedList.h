// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "utils.h"

typedef struct ll_node_t
{
    void* data;
    struct ll_node_t* next;
} ll_node_t;

typedef struct linked_list_t
{
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
} linked_list_t;

ll_node_t *
alloc_node(const void *data, unsigned int data_size);

linked_list_t *
ll_create(unsigned int data_size);

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data);

ll_node_t *
ll_remove_nth_node(linked_list_t* list, unsigned int n);

unsigned int
ll_get_size(linked_list_t* list);

void
ll_free(linked_list_t* pp_list, void (*free_data)(void*));


#endif  // LINKEDLIST_H_
