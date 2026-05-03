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

void bubble_up_min(MinMaxHeap* h, int i) {
    while (i > 2) {
        int gp = get_parent(get_parent(i));
        if (h->heap[i].efficiency_score < h->heap[gp].efficiency_score) {
            swap(&h->heap[i], &h->heap[gp]);
            i = gp;
        } else break;
    }
}

void bubble_up_max(MinMaxHeap* h, int i) {
    while (i > 2) {
        int gp = get_parent(get_parent(i));
        if (h->heap[i].efficiency_score > h->heap[gp].efficiency_score) {
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

    if (is_min_level(i)) {
        if (h->heap[i].efficiency_score > h->heap[parent].efficiency_score) {
            swap(&h->heap[i], &h->heap[parent]);
            bubble_up_max(h, parent);
        } else {
            bubble_up_min(h, i);
        }
    } else {
        if (h->heap[i].efficiency_score < h->heap[parent].efficiency_score) {
            swap(&h->heap[i], &h->heap[parent]);
            bubble_up_min(h, parent);
        } else {
            bubble_up_max(h, i);
        }
    }
}

/* ---------- Trickle Down ---------- */

void trickle_down_min(MinMaxHeap* h, int i) {
    int size = h->size;

    while (get_left(i) < size) {
        int smallest = i;

        // Check children + grandchildren
        for (int j = 1; j <= 6; j++) {
            int idx;

            if (j == 1) idx = get_left(i);
            else if (j == 2) idx = get_right(i);
            else idx = get_left(get_left(i)) + (j - 3);

            if (idx < size &&
                h->heap[idx].efficiency_score <
                h->heap[smallest].efficiency_score) {
                smallest = idx;
            }
        }

        if (smallest == i) break;

        swap(&h->heap[i], &h->heap[smallest]);

        // If grandchild, fix parent relation
        if (smallest >= get_left(get_left(i))) {
            int parent = get_parent(smallest);
            if (h->heap[smallest].efficiency_score >
                h->heap[parent].efficiency_score) {
                swap(&h->heap[smallest], &h->heap[parent]);
            }
        }

        i = smallest;
    }
}

void trickle_down_max(MinMaxHeap* h, int i) {
    int size = h->size;

    while (get_left(i) < size) {
        int largest = i;

        // Check children + grandchildren
        for (int j = 1; j <= 6; j++) {
            int idx;

            if (j == 1) idx = get_left(i);
            else if (j == 2) idx = get_right(i);
            else idx = get_left(get_left(i)) + (j - 3);

            if (idx < size &&
                h->heap[idx].efficiency_score >
                h->heap[largest].efficiency_score) {
                largest = idx;
            }
        }

        if (largest == i) break;

        swap(&h->heap[i], &h->heap[largest]);

        // If grandchild, fix parent relation
        if (largest >= get_left(get_left(i))) {
            int parent = get_parent(largest);
            if (h->heap[largest].efficiency_score <
                h->heap[parent].efficiency_score) {
                swap(&h->heap[largest], &h->heap[parent]);
            }
        }

        i = largest;
    }
}

/* ---------- Extract Min ---------- */

PCB* minmax_extract_min(MinMaxHeap* h) {
    if (!h || h->size == 0) return NULL;

    PCB* min = h->heap[0].process;

    h->heap[0] = h->heap[--h->size];

    trickle_down_min(h, 0);

    return min;
}

/* ---------- Extract Max ---------- */

PCB* minmax_extract_max(MinMaxHeap* h) {
    if (!h || h->size == 0) return NULL;

    int max_idx;

    if (h->size == 1) max_idx = 0;
    else if (h->size == 2) max_idx = 1;
    else {
        max_idx = (h->heap[1].efficiency_score >
                   h->heap[2].efficiency_score) ? 1 : 2;
    }

    PCB* max = h->heap[max_idx].process;

    h->heap[max_idx] = h->heap[--h->size];

    if (max_idx < h->size) {
        if (is_min_level(max_idx))
            trickle_down_min(h, max_idx);
        else
            trickle_down_max(h, max_idx);
    }

    return max;
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
        if (is_min_level(idx))
            trickle_down_min(h, idx);
        else
            trickle_down_max(h, idx);
    }
}

/* ---------- Utility ---------- */

int minmax_is_empty(MinMaxHeap* h) {
    return !h || h->size == 0;
}

void minmax_destroy(MinMaxHeap* h) {
    if (h) free(h);
}