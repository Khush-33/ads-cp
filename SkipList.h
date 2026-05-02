#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "PCB.h"

#define MAX_LEVEL 4   // 4 levels is plenty for up to 100 jobs

typedef struct SkipNode {
    int priority;
    int efficiency;
    char job_id[50];
    struct SkipNode* next[MAX_LEVEL];  // pointer for each level
} SkipNode;

typedef struct {
    SkipNode* head;  // dummy starting node (does not store a job)
    int size;        // number of jobs in history
} SkipList;

SkipList* create_skip_list();
void skip_insert(SkipList* sl, PCB* job, int priority, int efficiency);
void skip_search_by_priority(SkipList* sl, int priority);
void skip_print_all(SkipList* sl);
void skip_print_stats(SkipList* sl);
void destroy_skip_list(SkipList* sl);

#endif