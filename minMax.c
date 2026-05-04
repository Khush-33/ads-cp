#include "MinMaxHeap.h"
#include <stdlib.h>

/* ---------- Helper Functions ---------- */

int get_parent(int i) { return (i - 1) / 2; }
int get_left(int i) { return 2 * i + 1; }
int get_right(int i) { return 2 * i + 2; }

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Level calculation (clean version)
int get_level(int index) {
    int level = 0;
    index += 1;
    while (index > 1) {
        index /= 2;
        level++;
    }
    return level;
}

int is_min_level(int i) {
    return (get_level(i) % 2 == 0);
}

/* ---------- Heap Creation ---------- */

MinMaxHeap* create_minmax_heap() {
    MinMaxHeap* h = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    if (h) h->size = 0;
    return h;
}

/* ---------- Bubble Up ---------- */

void bubble_up(MinMaxHeap* h, int i, int is_min) {
    while (i > 2) {
        int gp = get_parent(get_parent(i));
        int comp = is_min ? (h->heap[i].efficiency_score < h->heap[gp].efficiency_score)
                          : (h->heap[i].efficiency_score > h->heap[gp].efficiency_score);
        if (comp) {
            swap(&h->heap[i], &h->heap[gp]);
            i = gp;
        } else break;
    }
}

/* ---------- Insert ---------- */

void minmax_insert(MinMaxHeap* h, PCB* p, int score) {
    if (!h || !p || h->size >= MAX_HEAP_SIZE) return;

    int i = h->size++;
    h->heap[i] = (HeapNode){p, score};

    if (i == 0) return;

    int parent = get_parent(i);
    int is_min = is_min_level(i);

    int comp = is_min ? (h->heap[i].efficiency_score > h->heap[parent].efficiency_score)
                      : (h->heap[i].efficiency_score < h->heap[parent].efficiency_score);

    if (comp) {
        swap(&h->heap[i], &h->heap[parent]);
        bubble_up(h, parent, !is_min);
    } else {
        bubble_up(h, i, is_min);
    }
}

/* ---------- Trickle Down ---------- */

void trickle_down(MinMaxHeap* h, int i, int is_min) {
    int size = h->size;

    while (get_left(i) < size) {
        int m = i;

        for (int j = 1; j <= 6; j++) {
            int idx = (j <= 2) ? get_left(i) + (j - 1) : get_left(get_left(i)) + (j - 3);

            if (idx < size) {
                int comp = is_min ? (h->heap[idx].efficiency_score < h->heap[m].efficiency_score)
                                  : (h->heap[idx].efficiency_score > h->heap[m].efficiency_score);
                if (comp) m = idx;
            }
        }

        if (m == i) break;

        swap(&h->heap[i], &h->heap[m]);

        if (m >= get_left(get_left(i))) {
            int parent = get_parent(m);
            int comp = is_min ? (h->heap[m].efficiency_score > h->heap[parent].efficiency_score)
                              : (h->heap[m].efficiency_score < h->heap[parent].efficiency_score);
            if (comp) swap(&h->heap[m], &h->heap[parent]);
        }

        i = m;
    }
}

/* ---------- Peek ---------- */

PCB* minmax_peek_min(MinMaxHeap* h) {
    return (!h || h->size == 0) ? NULL : h->heap[0].process;
}

PCB* minmax_peek_max(MinMaxHeap* h) {
    if (!h || h->size == 0) return NULL;

    if (h->size == 1) return h->heap[0].process;
    if (h->size == 2) return h->heap[1].process;

    return (h->heap[1].efficiency_score >
            h->heap[2].efficiency_score)
           ? h->heap[1].process
           : h->heap[2].process;
}

/* ---------- Delete ---------- */

void minmax_delete_by_pcb(MinMaxHeap* h, PCB* p) {
    if (!h || !p) return;

    int idx = -1;

    for (int i = 0; i < h->size; i++) {
        if (h->heap[i].process == p) {
            idx = i;
            break;
        }
    }

    if (idx == -1) return;

    h->heap[idx] = h->heap[--h->size];

    if (idx < h->size) {
        trickle_down(h, idx, is_min_level(idx));
    }
}

/* ---------- Utility ---------- */

void minmax_destroy(MinMaxHeap* h) {
    if (h) free(h);
}