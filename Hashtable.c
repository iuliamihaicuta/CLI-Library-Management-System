// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#include "Hashtable.h"
#include "librarian_commands.h"

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

unsigned int
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	int32_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*), void (*free_info)(void *))
{
	hashtable_t *ht;
    ht = (hashtable_t *)malloc(sizeof(hashtable_t));

    ht->size = 0;
    ht->hmax = hmax;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;
    ht->free_info = free_info;

    ht->buckets = (linked_list_t **)calloc(ht->hmax, sizeof(linked_list_t *));
    DIE(ht->buckets == NULL, "calloc failed");

    for (unsigned int i = 0; i < ht->hmax; ++i) {
        ht->buckets[i] = ll_create(sizeof(info));
        DIE(ht->buckets[i] == NULL, "malloc failed");
    }

    return ht;
}

int
ht_has_key(hashtable_t *ht, void *key)
{
    int index = ht->hash_function(key) % ht->hmax;
    if (ht->buckets[index]->size == 0)
        return 0;

    ll_node_t *node = ht->buckets[index]->head;
    do {
        if (ht->compare_function(((info *)node->data)->key, key) == 0)
            return 1;

        node = node->next;
    } while (node != NULL);

	return 0;
}

void *
ht_get(hashtable_t *ht, void *key)
{
    int index = ht->hash_function(key) % ht->hmax;
    ll_node_t *node = ht->buckets[index]->head;

    do {
        if (ht->compare_function(((info *)node->data)->key, key) == 0) {
            return ((info *)node->data)->value;
        }

        node = node->next;
    } while (node != NULL);

	return NULL;
}

void
ht_resize(hashtable_t *ht)
{
    hashtable_t *new_ht = ht_create(2 * ht->hmax, ht->hash_function,
            ht->compare_function, ht->free_info);

    for (unsigned int i = 0; i < ht->hmax; ++i) {
            ll_node_t *node = ht->buckets[i]->head;

            while (node) {
                void *key = ((info *)node->data)->key;
                unsigned int index = new_ht->hash_function(key) % new_ht->hmax;

                ll_add_nth_node(new_ht->buckets[index], 0, node->data);
                new_ht->size++;

                node = node->next;
            }
            ll_free(ht->buckets[i], &free);
    }

    free(ht->buckets);

    ht->hmax *= 2;
    ht->buckets = new_ht->buckets;
    free(new_ht);
}

void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
    float load_factor = ht->size * 1. / ht->hmax;
    if (load_factor > 1)
        ht_resize(ht);

    int index = ht->hash_function(key) % ht->hmax;

    if (ht_has_key(ht, key) == 0) {
        info new_info;

        new_info.key = calloc(1, key_size);
        memcpy(new_info.key, key, key_size);
        new_info.value = calloc(1, value_size);
        memcpy(new_info.value, value, value_size);

        ll_add_nth_node(ht->buckets[index], 0, &new_info);

        ht->size++;
    } else {
        ll_node_t *node = ht->buckets[index]->head;

        do {
            if (ht->compare_function(((info *)node->data)->key, key) == 0) {
                free(((info *)node->data)->value);

                ((info *)node->data)->value = calloc(1, value_size);
                memcpy(((info *)node->data)->value, value, value_size);
                break;
            }
            node = node->next;
        } while (node != NULL);
    }
}

ll_node_t *
ht_remove_entry(hashtable_t *ht, void *key)
{
	int index = ht->hash_function(key) % ht->hmax;

    if (ht_has_key(ht, key) == 1) {
        int node_index = 0;

        ll_node_t *node = ht->buckets[index]->head;
        do {
            if (ht->compare_function(((info *)node->data)->key, key) == 0)
                break;
            node = node->next;
            node_index++;
        } while (node->next != NULL);

        ll_node_t *info = ll_remove_nth_node(ht->buckets[index], node_index);

        ht->size--;

        return info;
    }
    return NULL;
}

void
ht_free(hashtable_t *ht)
{
    for (unsigned int i = 0; i < ht->hmax; ++i) {
        ll_free(ht->buckets[i], ht->free_info);
    }

    free(ht->buckets);
    free(ht);
}
