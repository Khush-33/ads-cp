#include "SkipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int random_level() {
    int level = 0;
    while (rand() % 2 == 0 && level < MAX_LEVEL - 1)
        level++;
    return level;
}

SkipList* create_skip_list() {
    SkipList* sl = (SkipList*)malloc(sizeof(SkipList));
    sl->size = 0;

    // Create dummy head node
    sl->head = (SkipNode*)malloc(sizeof(SkipNode));
    sl->head->priority   = -1;
    sl->head->efficiency = 0;
    strcpy(sl->head->job_id, "HEAD");

    // All head pointers start as NULL (empty list)
    for (int i = 0; i < MAX_LEVEL; i++)
        sl->head->next[i] = NULL;

    return sl;
}

void skip_insert(SkipList* sl, PCB* job, int priority, int efficiency) {
    // update[i] = the node just before the insertion point at level i
    SkipNode* update[MAX_LEVEL];
    SkipNode* cur = sl->head;

    // Step 1: find insertion point at each level (top to bottom)
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (cur->next[i] != NULL && cur->next[i]->priority < priority)
            cur = cur->next[i];
        update[i] = cur;
    }

    // Step 2: create the new node
    SkipNode* new_node = (SkipNode*)malloc(sizeof(SkipNode));
    new_node->priority   = priority;
    new_node->efficiency = efficiency;
    strncpy(new_node->job_id, job->job_id, sizeof(new_node->job_id) - 1);
    new_node->job_id[sizeof(new_node->job_id) - 1] = '\0';

    // Step 3: link new node at levels 0 up to its random level
    int new_level = random_level();
    for (int i = 0; i <= new_level; i++) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }
    // unused levels point to NULL
    for (int i = new_level + 1; i < MAX_LEVEL; i++)
        new_node->next[i] = NULL;

    sl->size++;
}

void skip_search_by_priority(SkipList* sl, int priority) {
    SkipNode* cur = sl->head;

    // Walk from top level down
    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (cur->next[i] != NULL && cur->next[i]->priority < priority)
            cur = cur->next[i];
    }

    // Now cur->next[0] is the candidate
    cur = cur->next[0];

    if (cur != NULL && cur->priority == priority) {
        printf("  Found in history:\n");
        printf("    Job: %s | Priority: %d | Efficiency: %d\n",
               cur->job_id, cur->priority, cur->efficiency);
    } else {
        printf("  No job with priority %d found in history.\n", priority);
    }
}

void skip_print_all(SkipList* sl) {
    if (sl->size == 0) {
        printf("  No jobs have been scheduled yet.\n");
        return;
    }

    printf("  %-5s %-20s %-10s %-12s\n", "#", "Job Name", "Priority", "Efficiency");
    printf("  -----------------------------------------------\n");

    SkipNode* cur = sl->head->next[0];  // start from first real node
    int count = 1;
    while (cur != NULL) {
        printf("  %-5d %-20s %-10d %-12d\n",
               count++, cur->job_id, cur->priority, cur->efficiency);
        cur = cur->next[0];
    }
}

void skip_print_stats(SkipList* sl) {
    if (sl->size == 0) {
        printf("  No jobs have been scheduled yet.\n");
        return;
    }

    int total_priority   = 0;
    int total_efficiency = 0;
    int min_eff = 10000;
    int max_eff = -1;

    SkipNode* cur = sl->head->next[0];
    while (cur != NULL) {
        total_priority   += cur->priority;
        total_efficiency += cur->efficiency;
        if (cur->efficiency < min_eff) min_eff = cur->efficiency;
        if (cur->efficiency > max_eff) max_eff = cur->efficiency;
        cur = cur->next[0];
    }

    printf("  Total jobs scheduled : %d\n",   sl->size);
    printf("  Avg priority         : %.1f\n", (float)total_priority   / sl->size);
    printf("  Avg efficiency score : %.1f\n", (float)total_efficiency / sl->size);
    printf("  Best efficiency      : %d\n",   min_eff);
    printf("  Worst efficiency     : %d\n",   max_eff);
}

void destroy_skip_list(SkipList* sl) {
    SkipNode* cur = sl->head;
    while (cur != NULL) {
        SkipNode* next = cur->next[0];
        free(cur);
        cur = next;
    }
    free(sl);
}