#ifndef MINMAX_HEAP_H
#define MINMAX_HEAP_H

#include "PCB.h"

#define MAX_HEAP_SIZE 100

/* ---------- Structures ---------- */

// Node storing process + efficiency score
typedef struct {
    PCB* process;
    int efficiency_score;   // Lower value = higher efficiency
} HeapNode;

// Min-Max Heap structure
typedef struct {
    HeapNode heap[MAX_HEAP_SIZE];
    int size;
} MinMaxHeap;

/* ---------- Core Operations ---------- */

MinMaxHeap* create_minmax_heap();

void minmax_insert(MinMaxHeap* h, PCB* p, int score);

PCB* minmax_extract_min(MinMaxHeap* h);
PCB* minmax_extract_max(MinMaxHeap* h);

PCB* minmax_peek_min(MinMaxHeap* h);
PCB* minmax_peek_max(MinMaxHeap* h);

void minmax_delete_by_pcb(MinMaxHeap* h, PCB* p);

int minmax_is_empty(MinMaxHeap* h);

void minmax_destroy(MinMaxHeap* h);

/* ---------- Helper ---------- */

// Returns level of node (0-based)
int get_level(int index);

#endif