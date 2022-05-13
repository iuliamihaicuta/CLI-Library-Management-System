// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

ll_node_t *new_node(const void *data, unsigned int data_size)
{
    ll_node_t *n = (ll_node_t *)malloc(sizeof(ll_node_t));

    n->data = calloc(1, data_size);
    memcpy(n->data, data, data_size);

    n->next = NULL;

    return n;
}

linked_list_t* ll_create(unsigned int data_size)
{
    linked_list_t *l = (linked_list_t *)malloc(sizeof(linked_list_t));

    l->size = 0;
    l->head = NULL;
    l->data_size = data_size;

    return l;
}

ll_node_t *get_nth_node(linked_list_t *l, unsigned int n)
{
    ll_node_t *tmp = l->head;
    if (n > l->size)
        n = l->size;

    for (unsigned int i = 0; i < n; ++i)
        tmp = tmp->next;

    return tmp;
}

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    if (n > list->size)
        n = list->size;

    ll_node_t *node = new_node(new_data, list->data_size);

    if (n == 0) {
        node->next = list->head;
        list->head = node;
    } else {
        ll_node_t *prev = list->head;

        for (unsigned int i = 0; i < n - 1; ++i)
            prev = prev->next;

        node->next = prev->next;
        prev->next = node;
    }

    (list->size)++;
}


ll_node_t* ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    if (n > list->size)
        n = list->size;

    ll_node_t *node;
    if (n == 0) {
        node = list->head;
        list->head = node->next;
    } else {
        ll_node_t *prev = list->head;

        for (unsigned int i = 0; i < n - 1; ++i)
            prev = prev->next;

        node = prev->next;
        prev->next = node->next;
    }
    (list->size)--;

    return node;
}

unsigned int ll_get_size(linked_list_t* list)
{
    return list->size;
}

void
ll_free(linked_list_t* pp_list, void (*free_data)(void*))
{
    if (!pp_list) {
		return;
	}

    while (pp_list->head != NULL) {
        ll_node_t *node = ll_remove_nth_node(pp_list, 0);

        free_data(node->data);
        free(node);
    }

    free(pp_list);
}
