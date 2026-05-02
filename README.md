# ECO-CLOUD JOB SCHEDULER

A job scheduling system's low level implementations simulation built with advanced data structures.

---

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Data Structures Used](#data-structures-used)
- [How to Run](#how-to-run)
- [Usage Guide](#usage-guide)
- [Implementation Details](#implementation-details)
- [Time Complexity Analysis](#time-complexity-analysis)
- [Test Cases](#test-cases)
- [Known Limitations](#known-limitations)
- [Educational Value](#educational-value)

---

## Project Overview

**ECO-CLOUD JOB SCHEDULER** is a terminal based simulation that manages and schedules computational jobs in a cloud environment. It efficiently handles job prioritization, efficiency tracking, and intelligent job retrieval using state-of-the-art data structures.

The system is designed for an Advanced Data Structures course project, demonstrating practical implementation of:
- **Priority Queues** for job scheduling
- **MinMax Heaps** for dual optimization
- **Tries** for fast job lookups
- **Levenshtein Distance Algorithm** for spell correction
- **AVL Trees** for execution time-based sorting and range queries
- **Skip Lists** for efficient scheduled job history tracking

---

## Features

### 1. Add New Job
- Create and store new cloud jobs
- Define job properties: name, priority, efficiency, memory requirements
- Automatic case-insensitive name handling
- Input validation for all parameters

**Parameters:**
- **Job Name**: Unique identifier (lowercase enforced)
- **Priority**: 1-10 (1 = highest, 10 = lowest)
- **Efficiency Score**: 1-100 (1 = most efficient, 100 = least efficient)
- **Memory Required**: 1-10,000 MB

### 2. Search for Job by Name
- Fast O(m) search using Trie data structure
- Case-insensitive search
- Returns full job details if found
- Spellchecker uses Levenshtein Distance for correction suggestions if job name isn't found

### 3. Schedule Next Job
- Extract the highest priority job from the queue
- Removes job from all active data structures simultaneously
- Records the scheduled job in history
- Shows scheduled job details

### 4. Show Most/Least Efficient Jobs
- Identifies most efficient job (lowest score) in O(1) time
- Identifies least efficient job (highest score) in O(1) time
- Uses MinMax Heap for dual optimization

### 5. List All Jobs
- Display all active (unscheduled) jobs
- Shows total job count
- Traverses Trie structure alphabetically

### 6. Show Jobs by Execution Time
- Lists all active jobs sorted by their estimated block execution time
- Maintained using an AVL Tree

### 7. Find Jobs in Time Range
- Perform range queries using the AVL tree to find jobs that require execution times between a specified minimum and maximum threshold

### 8. View Scheduled Jobs History
- Prints a fast-traversal history of all successfully scheduled jobs
- Powered by a scalable Skip List structure

### 9. View Scheduler Statistics
- Shows cumulative statistics, counts, and insights from the scheduled jobs history

---


## Project Structure

```
ads-cp/
├── README.md                 # This file
├── main.c                    # Main application logic & UI
├── PCB.c / PCB.h             # Process Control Block (Job representation)
├── PriorityQueue.c / .h      # Priority Queue (min-heap based)
├── MinMaxHeap.c / .h         # MinMax Heap (dual extrema tracking)
├── JobTrie.c / JobTrie.h     # Trie (job name storage & search)
├── JobCorrector.c /      # Edit Distance (spell checking)
├── AVLTree.c / AVLTree.h     # AVL Tree (execution time tracking)
├── SkipList.c / SkipList.h   # Skip List (scheduling history)
└── scheduler.exe             # Compiled executable
```

---

## Data Structures Used

### 1. Priority Queue (Min-Heap)
- **File**: `PriorityQueue.c / .h`
- **Purpose**: Schedule jobs by priority
- **Implementation**: Binary heap with min-property
- **Operations**:
  - Insert: O(log n)
  - Extract min: O(log n)
  - Peek min: O(1)

### 2. MinMax Heap
- **File**: `minMax.c / MinMaxHeap.h`
- **Purpose**: Track most and least efficient jobs simultaneously
- **Implementation**: Dual-level binary heap (min at even levels, max at odd levels)
- **Operations**:
  - Insert: O(log n)
  - Extract min: O(log n)
  - Extract max: O(log n)
  - Peek min: O(1)
  - Peek max: O(1)
  - Delete by PCB: O(n) search -> O(log n) after deletion

### 3. Trie (Prefix Tree)
- **File**: `JobTrie.c / JobTrie.h`
- **Purpose**: Store job names and enable fast retrieval
- **Implementation**: 26-character alphabet tree
- **Operations**:
  - Insert: O(m) where m = job name length
  - Search: O(m)
  - Traverse (list all): O(n)

### 4. Edit Distance (Levenshtein)
- **File**: `JobCorrector.c`
- **Purpose**: Spell check and job name correction
- **Implementation**: Dynamic Programming with 2D DP table
- **Operations**:
  - Edit distance: O(m*l) where m, l = string lengths
  - Allowed operations: Insert, Delete, Replace

### 5. AVL Tree
- **File**: `AVLTree.c / AVLTree.h`
- **Purpose**: Sort jobs by expected execution time and permit time-range queries
- **Implementation**: Self-balancing binary search tree
- **Operations**:
  - Insert/Delete: O(log n)
  - Search: O(log n)
  - Range Query: O(log n + k)

### 6. Skip List
- **File**: `SkipList.c / SkipList.h`
- **Purpose**: Maintain a history of completed/scheduled jobs for analysis
- **Implementation**: Probabilistic multi-level linked list
- **Operations**:
  - Insert: Expected O(log n)
  - Search: Expected O(log n)

---

## Compilation

### Using GCC (Recommended)

#### Basic Compilation:
```bash
gcc -o scheduler main.c PCB.c PriorityQueue.c JobTrie.c minMax.c JobCorrector.c AVLTree.c SkipList.c
```

---

## How to Run

### Step 1: Run the Executable
```bash
./scheduler
# or
scheduler.exe
```

### Step 2: See Welcome Screen
```
  ECO-CLOUD JOB SCHEDULER 
  1. Add a new job
  2. Search for a job by name
  3. Schedule next job (by priority)
  4. Show most/least efficient job
  5. List all jobs
  6. Show jobs by execution time
  7. Find jobs in time range
  8. View scheduled jobs history
  9. View scheduler statistics
  0. Exit
```

---

## Usage Guide

### Complete Workflow Example

#### Step 1: Add Jobs (Option 1)
```
Enter your choice: 1

Adding new job...
Job name: DataProcessor
Priority (1-10, lower = higher priority): 3
Efficiency score (1-100, lower = more efficient): 25
Memory required (MB, 1-10000): 512
Job 'dataprocessor' added successfully!
```

#### Step 2: Show Efficiency (Option 4)
```
Enter your choice: 4

Job Efficiency Analysis
Most efficient job:
  - Job ID: dataprocessor
  - Burst Time: 25 units
  - Memory Required: 512 MB
```

#### Step 3: Search Job (Option 2)
```
Enter your choice: 2

Searching for job...
Enter job name: dataprocessor
Job found:
  - Job ID: dataprocessor
  - Burst Time: 25 units
  - Memory Required: 512 MB
```

#### Step 4: Schedule Next Job (Option 3)
```
Enter your choice: 3

Scheduling next job...
Next scheduled job:
  - Job ID: dataprocessor
  - Burst Time: 25 units
  - Memory Required: 512 MB
```

#### Step 5: Exit (Option 0)
```
Enter your choice: 0

Shutting down...
Cleanup Summary:
  - Destroying Priority Queue...
  - Destroying MinMax Heap...
  - Destroying Job Database...
  - Destroying AVL Tree...
  - Destroying Job History...

ECO-CLOUD JOB SCHEDULER closed successfully!
```

---

## Implementation Details

### Data Structure Synchronization
```
5 Independent Data Structures:
1. Priority Queue   -> Ordered by PRIORITY (1-10)
2. MinMaxHeap       -> Ordered by EFFICIENCY (1-100)
3. Trie             -> Ordered by JOB NAME (alphabetical)
4. AVL Tree         -> Ordered by EXECUTION TIME
5. Skip List        -> Maintains History records indefinitely across loops

When Adding Job:
- Priority Queue receives (job, priority)
- MinMaxHeap receives (job, efficiency)
- Trie receives (jobname, job_pointer)
- AVL Tree receives (job, execution_time)

When Scheduling Job:
- Find job in Priority Queue -> dequeue()
- Find SAME job in MinMaxHeap -> delete_by_pcb()
- Find SAME job in Trie -> mark_as_inactive()
- Move record to Skip List History
- All point to SAME PCB object (pointer-based)
```

---

## Time Complexity Analysis

| Operation | Data Structure | Time Complexity | Space |
|-----------|----------------|-----------------|-------|
| Add Job | All Active | O(log n) | O(1) |
| Search Job | Trie | O(m) | O(1) |
| Schedule Job | PQ + Skip List| O(log n) | O(1) |
| Get Most Efficient | MinMaxHeap | O(1) | O(1) |
| Get Least Efficient | MinMaxHeap | O(1) | O(1) |
| List All Jobs | Trie | O(n + m) | O(n) |
| Range Query (Time) | AVL Tree | O(log n + k) | O(1) |
| Scheduled History | Skip List | O(n) print | O(n) |
| Delete by PCB | MinMaxHeap | O(n) search + O(log n) delete | O(1) |

Legend:
- n = number of jobs
- m = average job name length
- k = number of jobs in range query

---

## Test Cases

### Test Case 1: Basic Operations
```
1. Add 4 jobs with different priorities
2. Schedule 2 jobs
3. List remaining jobs (should show 2)
4. Check efficiency (should be correct)
Expected: All operations succeed
```

### Test Case 2: Data Structure Sync
```
1. Add 3 jobs: A(p=1,e=20), B(p=3,e=50), C(p=2,e=80)
2. Show efficiency: A is most efficient
3. Schedule job (removes by priority)
4. Show efficiency: Should NOT show scheduled job
Expected: Sync maintained
```

---

## Known Limitations

1. Fixed Size: Maximum 100 jobs (configurable via MAX_QUEUE_SIZE)
2. Job Names: Lowercase only (enforced for consistency)
3. Memory: Single machine (no distributed scheduling)
4. Persistence: No database - jobs lost after exit
5. Concurrency: Single-threaded (no simultaneous operations)

---

## Educational Value

This project demonstrates:
- Priority Queue: Job scheduling in operating systems
- MinMax Heap: Dual optimization (finding min and max efficiently)
- Trie: Fast string lookup (used in autocomplete)
- Edit Distance: String similarity (spell checkers)
- AVL Tree: Self-optimizing balanced searches and ranges
- Skip List: Performant probabilistic histories
- Data Structure Synchronization: Multi-index data management
- Object Sharing: Memory Management via reference counting and pointer-based structs
