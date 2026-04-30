#include "MinMaxHeap.h"
#include <stdlib.h>
#include <stdio.h>

// Get the level of a node at given index (0-indexed)
// Level 0 = 1 node, Level 1 = 2 nodes, etc.
int get_level(int index) {
    if (index == 0) return 0;
    int level = 0;
    int nodes = 1;
    int cumulative = 0;
    
    while (cumulative + nodes <= index) {
        cumulative += nodes;
        nodes *= 2;
        level++;
    }
    return level;
}

// Determine if a level is min level (0, 2, 4...) or max level (1, 3, 5...)
int is_min_level(int index) {
    return (get_level(index) % 2 == 0);
}

MinMaxHeap* create_minmax_heap() {
    MinMaxHeap* mmh = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    if (mmh) {
        mmh->size = 0;
    }
    return mmh;
}

void minmax_swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

int get_parent(int i) {
    return (i - 1) / 2;
}

int get_left_child(int i) {
    return 2 * i + 1;
}

int get_right_child(int i) {
    return 2 * i + 2;
}

// Insert a new element and bubble up maintaining min-max property
void minmax_insert(MinMaxHeap* mmh, PCB* p, int score) {
    if (!mmh || !p) {
        fprintf(stderr, "❌ Error: Invalid heap or process pointer\n");
        return;
    }
    if (mmh->size >= MAX_HEAP_SIZE) {
        fprintf(stderr, "❌ Error: MinMax Heap is full (max: %d jobs)\n", MAX_HEAP_SIZE);
        return;
    }
    
    // Insert at end
    int i = mmh->size;
    mmh->heap[i].process = p;
    mmh->heap[i].efficiency_score = score;
    mmh->size++;
    
    // Bubble up
    while (i > 0) {
        int parent = get_parent(i);
        
        if (is_min_level(i)) {
            // Current is on min level
            if (mmh->heap[i].efficiency_score < mmh->heap[parent].efficiency_score) {
                // Smaller than parent, swap with parent and continue
                minmax_swap_nodes(&mmh->heap[i], &mmh->heap[parent]);
                i = parent;
            } else {
                break;
            }
        } else {
            // Current is on max level
            if (mmh->heap[i].efficiency_score > mmh->heap[parent].efficiency_score) {
                // Larger than parent, swap with parent and continue
                minmax_swap_nodes(&mmh->heap[i], &mmh->heap[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }
}

// Trickle down helper for min level
void trickle_down_min(MinMaxHeap* mmh, int i) {
    int smallest = i;
    int left = get_left_child(i);
    int right = get_right_child(i);
    
    // Check children
    if (left < mmh->size && mmh->heap[left].efficiency_score < mmh->heap[smallest].efficiency_score) {
        smallest = left;
    }
    if (right < mmh->size && mmh->heap[right].efficiency_score < mmh->heap[smallest].efficiency_score) {
        smallest = right;
    }
    
    // Check grandchildren if needed
    int left_left = get_left_child(left);
    int left_right = get_right_child(left);
    int right_left = get_left_child(right);
    int right_right = get_right_child(right);
    
    if (left_left < mmh->size && mmh->heap[left_left].efficiency_score < mmh->heap[smallest].efficiency_score) {
        smallest = left_left;
    }
    if (left_right < mmh->size && mmh->heap[left_right].efficiency_score < mmh->heap[smallest].efficiency_score) {
        smallest = left_right;
    }
    if (right_left < mmh->size && mmh->heap[right_left].efficiency_score < mmh->heap[smallest].efficiency_score) {
        smallest = right_left;
    }
    if (right_right < mmh->size && mmh->heap[right_right].efficiency_score < mmh->heap[smallest].efficiency_score) {
        smallest = right_right;
    }
    
    if (smallest != i) {
        minmax_swap_nodes(&mmh->heap[i], &mmh->heap[smallest]);
        if (is_min_level(smallest)) {
            trickle_down_min(mmh, smallest);
        } else {
            trickle_down_min(mmh, smallest);  // Will check max property
        }
    }
}

// Trickle down helper for max level
void trickle_down_max(MinMaxHeap* mmh, int i) {
    int largest = i;
    int left = get_left_child(i);
    int right = get_right_child(i);
    
    // Check children
    if (left < mmh->size && mmh->heap[left].efficiency_score > mmh->heap[largest].efficiency_score) {
        largest = left;
    }
    if (right < mmh->size && mmh->heap[right].efficiency_score > mmh->heap[largest].efficiency_score) {
        largest = right;
    }
    
    // Check grandchildren
    int left_left = get_left_child(left);
    int left_right = get_right_child(left);
    int right_left = get_left_child(right);
    int right_right = get_right_child(right);
    
    if (left_left < mmh->size && mmh->heap[left_left].efficiency_score > mmh->heap[largest].efficiency_score) {
        largest = left_left;
    }
    if (left_right < mmh->size && mmh->heap[left_right].efficiency_score > mmh->heap[largest].efficiency_score) {
        largest = left_right;
    }
    if (right_left < mmh->size && mmh->heap[right_left].efficiency_score > mmh->heap[largest].efficiency_score) {
        largest = right_left;
    }
    if (right_right < mmh->size && mmh->heap[right_right].efficiency_score > mmh->heap[largest].efficiency_score) {
        largest = right_right;
    }
    
    if (largest != i) {
        minmax_swap_nodes(&mmh->heap[i], &mmh->heap[largest]);
        if (is_min_level(largest)) {
            trickle_down_min(mmh, largest);
        } else {
            trickle_down_max(mmh, largest);
        }
    }
}

// Extract minimum element (always at root)
PCB* minmax_extract_min(MinMaxHeap* mmh) {
    if (!mmh || mmh->size == 0) return NULL;
    
    PCB* min_process = mmh->heap[0].process;
    
    if (mmh->size == 1) {
        mmh->size = 0;
        return min_process;
    }
    
    // Move last element to root
    mmh->heap[0] = mmh->heap[mmh->size - 1];
    mmh->size--;
    
    // Trickle down from root (min level)
    trickle_down_min(mmh, 0);
    
    return min_process;
}

// Extract maximum element (at index 1 or 2 for small heaps, or child of root)
PCB* minmax_extract_max(MinMaxHeap* mmh) {
    if (!mmh || mmh->size == 0) return NULL;
    
    int max_idx = -1;
    
    if (mmh->size == 1) {
        max_idx = 0;
    } else if (mmh->size == 2) {
        max_idx = 1;
    } else {
        // Max is either at index 1 or 2 (children of root on max level)
        if (mmh->heap[1].efficiency_score >= mmh->heap[2].efficiency_score) {
            max_idx = 1;
        } else {
            max_idx = 2;
        }
    }
    
    PCB* max_process = mmh->heap[max_idx].process;
    
    // Move last element to max position
    mmh->heap[max_idx] = mmh->heap[mmh->size - 1];
    mmh->size--;
    
    if (max_idx < mmh->size) {
        if (is_min_level(max_idx)) {
            trickle_down_min(mmh, max_idx);
        } else {
            trickle_down_max(mmh, max_idx);
        }
    }
    
    return max_process;
}

// Peek at minimum (O(1))
PCB* minmax_peek_min(MinMaxHeap* mmh) {
    if (!mmh || mmh->size == 0) return NULL;
    return mmh->heap[0].process;
}

// Peek at maximum (O(1))
PCB* minmax_peek_max(MinMaxHeap* mmh) {
    if (!mmh || mmh->size == 0) return NULL;
    
    if (mmh->size == 1) return mmh->heap[0].process;
    if (mmh->size == 2) return mmh->heap[1].process;
    
    // Return child of root with larger value (max level)
    return (mmh->heap[1].efficiency_score >= mmh->heap[2].efficiency_score) 
           ? mmh->heap[1].process 
           : mmh->heap[2].process;
}

// Delete a specific job by PCB pointer
void minmax_delete_by_pcb(MinMaxHeap* mmh, PCB* p) {
    if (!mmh || !p || mmh->size == 0) return;
    
    // Find the index of the job
    int idx = -1;
    for (int i = 0; i < mmh->size; i++) {
        if (mmh->heap[i].process == p) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) return;  // Job not found
    
    // Move last element to deleted position
    mmh->heap[idx] = mmh->heap[mmh->size - 1];
    mmh->size--;
    
    if (idx < mmh->size) {
        // Restore heap property
        if (is_min_level(idx)) {
            trickle_down_min(mmh, idx);
        } else {
            trickle_down_max(mmh, idx);
        }
    }
}

int minmax_is_empty(MinMaxHeap* mmh) {
    return !mmh || mmh->size == 0;
}

void minmax_destroy(MinMaxHeap* mmh) {
    if (mmh) {
        free(mmh);
    }
}
