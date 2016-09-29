/*
 * semrelay.c
 *
 *  Created on: 2013-08-19
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <semaphore.h>

#include "semrelay.h"
#include "statistics.h"
#include "multilock.h"
#include "utils.h"

void *semrelay_worker(void * data) {
    unsigned long i, j;
    struct experiment * e = data;

    for (i = 0; i < e->outer; i++) {
        sem_wait(e->lock);
        for (j = 0; j < e->inner; j++) {
            unsigned long idx = (i * e->inner) + j;
            statistics_add_sample(e->data, (double) idx);
        }
        sem_post(e->lock);
    }
    return NULL;
}

void semrelay_initialization(struct experiment * e) {
    e->data = make_statistics();
    e->lock = malloc(sizeof(sem_t));
    sem_init(e->lock, 0, 1);
}

void semrelay_destroy(struct experiment * e) {
    int i;

    // copie finale dans e->stats
    statistics_copy(e->stats, e->data);
    free(e->data);

    sem_destroy(e->lock);
    free(e->lock);
}

