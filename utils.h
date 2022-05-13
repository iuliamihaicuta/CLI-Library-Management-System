// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
/**
 * Useful structures/macros
 *
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef UTILS_H_
#define UTILS_H_

#define uint unsigned int
#define uchar unsigned char

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)                                       \
    do {                                                                       \
        if (assertion) {                                                       \
            fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                 \
            perror(call_description);                                          \
            exit(errno);                                                       \
        }                                                                      \
    } while (0)

#endif  // UTILS_H_
