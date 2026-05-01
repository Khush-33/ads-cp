# ☁️ ECO-CLOUD JOB SCHEDULER

A high-performance job scheduling system built with advanced data structures for cloud computing environments.

---

## 📋 Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [System Requirements](#system-requirements)
- [Project Structure](#project-structure)
- [Data Structures Used](#data-structures-used)
- [Compilation](#compilation)
- [How to Run](#how-to-run)
- [Usage Guide](#usage-guide)
- [Implementation Details](#implementation-details)
- [Time Complexity Analysis](#time-complexity-analysis)

---

## 🎯 Project Overview

**ECO-CLOUD JOB SCHEDULER** is a terminal-based application that manages and schedules computational jobs in a cloud environment. It efficiently handles job prioritization, efficiency tracking, and intelligent job retrieval using state-of-the-art data structures.

The system is designed for a 2nd-year Advanced Data Structures course project, demonstrating practical implementation of:
- **Priority Queues** for job scheduling
- **MinMax Heaps** for dual optimization
- **Tries** for fast job lookups
- **Edit Distance** for spell correction

---

## ✨ Features

### 1. ➕ **Add New Job**
- Create and store new cloud jobs
- Define job properties: name, priority, efficiency, memory requirements
- Automatic case-insensitive name handling
- Input validation for all parameters

**Parameters:**
- **Job Name**: Unique identifier (lowercase enforced)
- **Priority**: 1-10 (1 = highest, 10 = lowest)
- **Efficiency Score**: 1-100 (1 = most efficient, 100 = least efficient)
- **Memory Required**: 1-10,000 MB

### 2. 🔍 **Search for Job by Name**
- Fast O(log n) search using Trie data structure
- Case-insensitive search
- Returns full job details if found
- Instant feedback with not-found alerts

### 3. ⏱️ **Schedule Next Job**
- Extract the highest priority job from the queue
- Removes job from all data structures simultaneously
- Maintains data structure synchronization
- Shows scheduled job details
- Tracks remaining jobs

### 4. 📊 **Show Most/Least Efficient Jobs**
- Identifies most efficient job (lowest score) in O(1) time
- Identifies least efficient job (highest score) in O(1) time
- Uses MinMax Heap for dual optimization
- Useful for performance analysis and bottleneck identification

### 5. ✏️ **Job Name Spell Checker**
- Validates exact job name matches
- Uses Levenshtein (Edit) Distance algorithm
- Provides correction suggestions (expandable feature)
- Case-insensitive validation

### 6. 📋 **List All Jobs**
- Display all active (unscheduled) jobs
- Shows total job count
- Traverses Trie structure alphabetically
- Only displays jobs with `is_active = 1` flag
- Formatted output with job details

---

## 💻 System Requirements

### Minimum Requirements
- **OS**: Windows / Linux / macOS
- **Compiler**: GCC 6.3.0 or higher
- **RAM**: 10 MB minimum
- **Storage**: 200 KB for executable

### Recommended Setup
- GCC 9.0+
- 100 MB available RAM
- Windows 10+ / Ubuntu 18.04+ / macOS 10.14+

---

## 📂 Project Structure

```
ads-cp/
├── README.md                 # This file
├── main.c                    # Main application logic & UI
├── PCB.c / PCB.h            # Process Control Block (Job representation)
├── PriorityQueue.c / .h     # Priority Queue (min-heap based)
├── MinMaxHeap.c / .h        # MinMax Heap (dual extrema tracking)
├── JobTrie.c / JobTrie.h    # Trie (job name storage & search)
├── JobCorrector.c / .h      # Edit Distance (spell checking)
├── scheduler.exe            # Compiled executable
└── Makefile                 # Build configuration (optional)
```

---

## 🏗️ Data Structures Used

### 1. **Priority Queue (Min-Heap)**
- **File**: `PriorityQueue.c / .h`
- **Purpose**: Schedule jobs by priority
- **Implementation**: Binary heap with min-property
- **Operations**: 
  - Insert: O(log n)
  - Extract min: O(log n)
  - Peek min: O(1)

**Example:**
```
Jobs ordered by priority (lower = higher):
[Priority=1, Priority=3, Priority=5, Priority=7]
         ↓
    Scheduled first
```

### 2. **MinMax Heap**
- **File**: `minMax.c / MinMaxHeap.h`
- **Purpose**: Track most and least efficient jobs simultaneously
- **Implementation**: Dual-level binary heap (min at even levels, max at odd levels)
- **Operations**:
  - Insert: O(log n)
  - Extract min: O(log n)
  - Extract max: O(log n)
  - Peek min: O(1) ✨
  - Peek max: O(1) ✨
  - Delete by PCB: O(n) → O(log n) after deletion

**Structure:**
```
                    Min (Index 0)
                   /            \
            Max (1)              Max (2)
            /    \               /    \
         Min(3) Min(4)       Min(5)  Min(6)
```

### 3. **Trie (Prefix Tree)**
- **File**: `JobTrie.c / JobTrie.h`
- **Purpose**: Store job names and enable fast retrieval
- **Implementation**: 26-character alphabet tree
- **Operations**:
  - Insert: O(m) where m = job name length
  - Search: O(m)
  - Traverse (list all): O(n)

**Example:**
```
Jobs: "dataprocessor", "imagerenderer", "videoencoder"

                    root
                   / | \
                  d  i  v
                  |  |  |
                  a  m  i
                  |  |  |
              [dataprocessor] [imagerenderer] [videoencoder]
```

### 4. **Edit Distance (Levenshtein)**
- **File**: `JobCorrector.c / JobCorrector.h`
- **Purpose**: Spell check and job name correction
- **Implementation**: Dynamic Programming with 2D DP table
- **Operations**:
  - Edit distance: O(m*n) where m, n = string lengths
  - Allowed operations: Insert, Delete, Replace

**Example:**
```
edit_distance("imagerenderer", "imagrenderer") = 1
              (one deletion needed)
```

---

## 🔨 Compilation

### Using GCC (Recommended)

#### **Basic Compilation:**
```bash
gcc -o scheduler main.c PCB.c PriorityQueue.c JobTrie.c minMax.c JobCorrector.c
```

#### **With Warnings:**
```bash
gcc -Wall -Wextra -o scheduler main.c PCB.c PriorityQueue.c JobTrie.c minMax.c JobCorrector.c
```

#### **Optimized Build:**
```bash
gcc -O2 -o scheduler main.c PCB.c PriorityQueue.c JobTrie.c minMax.c JobCorrector.c
```

#### **Debug Build:**
```bash
gcc -g -o scheduler main.c PCB.c PriorityQueue.c JobTrie.c minMax.c JobCorrector.c
```

### Expected Output
```
✅ Compilation successful!
```

---

## 🚀 How to Run

### Step 1: Navigate to Project Directory
```bash
cd "c:\Users\HP\Desktop\Workspace\VIT MODULE 4\ADS\cp\ads-cp"
```

### Step 2: Run the Executable
```bash
./scheduler
```
or
```bash
scheduler.exe
```

### Step 3: See Welcome Screen
```
🚀 Welcome to ECO-CLOUD JOB SCHEDULER!

═══════════════════════════════════════════════════════════
        ☁️  ECO-CLOUD JOB SCHEDULER ☁️
═══════════════════════════════════════════════════════════
  1. ➕ Add a new job
  2. 🔍 Search for a job by name
  3. ⏱️  Schedule next job (by priority)
  4. 📊 Show most/least efficient job
  5. ✏️  Suggest correct job name (spell check)
  6. 📋 List all jobs
  0. 🚪 Exit
═══════════════════════════════════════════════════════════
```

---

## 📖 Usage Guide

### **Complete Workflow Example**

#### **Step 1: Add Jobs (Option 1)**
```
➤ Enter your choice: 1

Adding new job...
─────────────────────────────────
Job name: DataProcessor
Priority (1-10, lower = higher priority): 3
Efficiency score (1-100, lower = more efficient): 25
Memory required (MB, 1-10000): 512
✅ Job 'dataprocessor' added successfully! (Total jobs: 1)
```

#### **Step 2: Add More Jobs**
```
➤ Enter your choice: 1
Job name: ImageRenderer
Priority (1-10, lower = higher priority): 1
Efficiency score (1-100, lower = more efficient): 60
Memory required (MB, 1-10000): 1024
✅ Job 'imagerenderer' added successfully! (Total jobs: 2)

➤ Enter your choice: 1
Job name: VideoEncoder
Priority (1-10, lower = higher priority): 2
Efficiency score (1-100, lower = more efficient): 45
Memory required (MB, 1-10000): 2048
✅ Job 'videoencoder' added successfully! (Total jobs: 3)
```

#### **Step 3: Show Efficiency (Option 4)**
```
➤ Enter your choice: 4

Job Efficiency Analysis
─────────────────────────────────
⭐ Most efficient job:
  ├─ Job ID: dataprocessor
  ├─ Burst Time: 25 units
  └─ Memory Required: 512 MB

⚠️  Least efficient job:
  ├─ Job ID: imagerenderer
  ├─ Burst Time: 60 units
  └─ Memory Required: 1024 MB
```

#### **Step 4: Search Job (Option 2)**
```
➤ Enter your choice: 2

Searching for job...
─────────────────────────────────
Enter job name: videoencoder
✅ Job found:
  ├─ Job ID: videoencoder
  ├─ Burst Time: 45 units
  └─ Memory Required: 2048 MB
```

#### **Step 5: Schedule Next Job (Option 3)**
```
➤ Enter your choice: 3

Scheduling next job...
─────────────────────────────────
✅ Next scheduled job:
  ├─ Job ID: imagerenderer
  ├─ Burst Time: 60 units
  └─ Memory Required: 1024 MB

(Scheduled by highest priority = 1)
```

#### **Step 6: List All Jobs (Option 6)**
```
➤ Enter your choice: 6

All Jobs in Database
─────────────────────────────────
Total jobs: 2

  ├─ Job ID: dataprocessor
  ├─ Burst Time: 25 units
  └─ Memory Required: 512 MB

  ├─ Job ID: videoencoder
  ├─ Burst Time: 45 units
  └─ Memory Required: 2048 MB

(Note: imagerenderer is NOT listed - it was scheduled!)
```

#### **Step 7: Exit (Option 0)**
```
➤ Enter your choice: 0

Shutting down...
📊 Cleanup Summary:
  • Destroying Priority Queue...
  • Destroying MinMax Heap...
  • Destroying Job Database...

✨ ECO-CLOUD JOB SCHEDULER closed successfully!
Thank you for using our service! 👋
```

---

## 🔍 Implementation Details

### Job Addition Flow
```
User Input (name, priority, efficiency, memory)
         ↓
Create PCB (Process Control Block)
         ↓
    ┌────┴────┬────────────┬──────────────┐
    ↓         ↓            ↓              ↓
Enqueue to  Insert into  Insert into   Insert into
Priority    MinMaxHeap   Trie          Database
Queue                    (with flag)
    ↓         ↓            ↓              ↓
    └────┬────┴────────────┴──────────────┘
         ↓
    Confirm & Display
```

### Job Scheduling Flow
```
User selects "Schedule" (Option 3)
         ↓
Dequeue from Priority Queue (highest priority)
         ↓
    ┌────┴────┬────────────┐
    ↓         ↓            ↓
Mark as    Delete from   Display
Inactive   MinMaxHeap    Job Details
in Trie                   
    ↓         ↓            ↓
    └────┬────┴────────────┘
         ↓
    Decrement job_count
```

### Data Structure Synchronization
```
3 Independent Data Structures:
1. Priority Queue   → Ordered by PRIORITY (1-10)
2. MinMaxHeap      → Ordered by EFFICIENCY (1-100)
3. Trie            → Ordered by JOB NAME (alphabetical)

When Adding Job:
├─ Priority Queue receives (job, priority)
├─ MinMaxHeap receives (job, efficiency)
└─ Trie receives (jobname, job_pointer)

When Scheduling Job:
├─ Find job in Priority Queue → dequeue()
├─ Find SAME job in MinMaxHeap → delete_by_pcb()
├─ Find SAME job in Trie → mark_as_inactive()
└─ All point to SAME PCB object (pointer-based)
```

### Memory Management
```
Total Active Jobs: ≤ 100 (MAX_QUEUE_SIZE)

Memory per Job:
- PCB struct: ~50 bytes
- Queue node: ~12 bytes
- Heap node: ~12 bytes
- Trie nodes: ~104 bytes (26 pointers)

Total: ~170 bytes per job minimum
Max memory usage: ~17 KB (for 100 jobs)
```

---

## ⏱️ Time Complexity Analysis

| Operation | Data Structure | Time Complexity | Space |
|-----------|----------------|-----------------|-------|
| **Add Job** | All | O(log n) | O(1) |
| **Search Job** | Trie | O(m) | O(1) |
| **Schedule Job** | Priority Queue | O(log n) | O(1) |
| **Get Most Efficient** | MinMaxHeap | O(1) ✨ | O(1) |
| **Get Least Efficient** | MinMaxHeap | O(1) ✨ | O(1) |
| **List All Jobs** | Trie | O(n + m) | O(n) |
| **Delete by PCB** | MinMaxHeap | O(n) search + O(log n) delete | O(1) |

**Legend:**
- **n** = number of jobs
- **m** = average job name length
- ✨ = constant time (very fast!)

---

## 🧪 Test Cases

### Test Case 1: Basic Operations
```
1. Add 4 jobs with different priorities
2. Schedule 2 jobs
3. List remaining jobs (should show 2)
4. Check efficiency (should be correct)
Expected: ✅ All operations succeed
```

### Test Case 2: Data Structure Sync
```
1. Add 3 jobs: A(p=1,e=20), B(p=3,e=50), C(p=2,e=80)
2. Show efficiency: A is most efficient ✅
3. Schedule job (removes by priority)
4. Show efficiency: Should NOT show scheduled job ✅
Expected: ✅ Sync maintained
```

### Test Case 3: Edge Cases
```
1. Try to search non-existent job
2. Try to schedule from empty queue
3. Try invalid priority (11)
4. Try empty job name
Expected: ✅ Graceful error handling
```

### Test Case 4: Full Workflow
```
1. Add 5 jobs
2. Schedule 3 jobs
3. List all (should show 2)
4. Search each remaining job
5. Show efficiency correctly
Expected: ✅ All features work together
```

---

## 🐛 Known Limitations

1. **Fixed Size**: Maximum 100 jobs (configurable via `MAX_QUEUE_SIZE`)
2. **Job Names**: Lowercase only (enforced for consistency)
3. **Memory**: Single machine (no distributed scheduling)
4. **Persistence**: No database - jobs lost after exit
5. **Concurrency**: Single-threaded (no simultaneous operations)

---

## 🚀 Future Enhancements

1. **Dynamic Memory**: Replace fixed arrays with dynamic allocation
2. **Persistence**: SQLite database integration
3. **REST API**: Replace CLI with HTTP endpoints
4. **Multi-threading**: Concurrent job execution
5. **Web Dashboard**: Real-time monitoring UI
6. **Job Retry Logic**: Automatic retry on failure
7. **Resource Limits**: Enforce CPU and memory quotas
8. **Job Dependencies**: Support job sequencing

---

## 📝 Code Quality

### Best Practices Implemented
- ✅ Input validation with helpful error messages
- ✅ Memory safety (strncpy instead of strcpy)
- ✅ Proper error handling
- ✅ Modular code structure
- ✅ Clear function documentation
- ✅ Consistent naming conventions
- ✅ Resource cleanup on exit

### Compiler Warnings
```
GCC -Wall -Wextra: CLEAN ✅
No warnings or errors
```

---

## 📚 Educational Value

This project demonstrates:
- **Priority Queue**: Job scheduling in operating systems
- **MinMax Heap**: Dual optimization (finding min and max efficiently)
- **Trie**: Fast string lookup (used in autocomplete, DNS)
- **Edit Distance**: String similarity (spell checkers, DNA analysis)
- **Data Structure Synchronization**: Multi-index data management
- **Memory Management**: Pointer-based object sharing
- **Error Handling**: Robust CLI application design

---
