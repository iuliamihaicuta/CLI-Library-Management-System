#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Hashtable.h"
#include "utils.h"

#define uint unsigned char
#define uchar unsigned char

/*
 * Functii de comparare a cheilor:
 */
int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
uint
hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	uint uint_a = *((uint *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

uint
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashtable_t *
ht_create(uint hmax, uint (*hash_function)(void*),
		int (*compare_function)(void*, void*), uint data_size)
{
	hashtable_t *ht;
    ht = (hashtable_t *)malloc(sizeof(hashtable_t));

    ht->size = 0;
    ht->hmax = hmax;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;

    ht->buckets = (linked_list_t **)malloc(ht->hmax * sizeof(linked_list_t *));
    DIE(ht->buckets == NULL, "malloc failed");

    for (uint i = 0; i < ht->hmax; ++i) {
        ht->buckets[i] = ll_create(data_size);
        DIE(ht->buckets[i] == NULL, "malloc failed");
    }

    return ht;
}

int
ht_has_key(hashtable_t *ht, void *key)
{
	int index = ht->hash_function(key) % ht->hmax;
    if(ht->buckets[index]->size == 0)
        return 0;

    ll_node_t *node = ht->buckets[index]->head;

    do {
        if(ht->compare_function(((info *)node->data)->key, key) == 0)
            return 1;

        node = node->next;
    } while(node->next != NULL);

	return 0;
}

void *
ht_get(hashtable_t *ht, void *key)
{
    int index = ht->hash_function(key) % ht->hmax;

    ll_node_t *node = ht->buckets[index]->head;

    do {
        if(ht->compare_function(((info *)node->data)->key, key) == 0)
            return ((info *)node->data)->value;

        node = node->next;
    } while(node->next != NULL);  

	return NULL;
}

void
ht_put(hashtable_t *ht, void *key, uint key_size,
	void *value, uint value_size)
{
    int index = ht->hash_function(key) % ht->hmax;

    if(ht_has_key(ht, key) == 0) {
        info *new_info;

        new_info = (info *)malloc(sizeof(info));
        new_info->key = malloc(key_size);
        memcpy(new_info->key, key, key_size);
        new_info->value = malloc(value_size);
        memcpy(new_info->value, value, value_size);

        ll_add_nth_node(ht->buckets[index], ht->buckets[index]->size, new_info);

        free(new_info);

        ht->size++;
    } else {
        ll_node_t *node = ht->buckets[index]->head;

        do {
            if(ht->compare_function(((info *)node->data)->key, key) == 0)
                break;
            node = node->next;
        } while(node->next != NULL);

        memcpy(((info *)node->data)->value, value, value_size);

    }
}

void
ht_remove_entry(hashtable_t *ht, void *key)
{
	int index = ht->hash_function(key) % ht->hmax;

    if(ht_has_key(ht, key) == 1) {
        int node_index = 0;

        ll_node_t *node = ht->buckets[index]->head;
        do {
            if(ht->compare_function(((info *)node->data)->key, key) == 0)
                break;
            node = node->next;
            node_index++;
        } while(node->next != NULL);

        ll_remove_nth_node(ht->buckets[index], node_index);
        ht->size--;
    }
}

