
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "PCB.h"
#include "PriorityQueue.h"
#include "JobTrie.h"
#include "MinMaxHeap.h"
#include "JobCorrector.h"


void print_menu() {
    printf("\n  ECO-CLOUD JOB SCHEDULER \n");
    printf("  1.Add a new job\n");
    printf("  2.Search for a job by name\n");
    printf("  3.Schedule next job (by priority)\n");
    printf("  4.Show most/least efficient job\n");
    printf("  5.Suggest correct job name (spell check)\n");
    printf("  6.List all jobs\n");
    printf("  0.Exit\n");
}

int get_valid_int(const char* prompt, int min, int max) {
    int value;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) continue;
        if (sscanf(buffer, "%d", &value) == 1 && value >= min && value <= max) return value;
        printf(" Invalid input! Please enter a number between %d and %d.\n", min, max);
    }
}

void get_valid_string(const char* prompt, char* buffer, size_t size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, size, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) > 0) return;
        }
        printf(" Input cannot be empty. Please try again.\n");
    }
}

void to_lowercase(char* str) {
    for (int i = 0; str[i]; i++) str[i] = tolower(str[i]);
}

void calculate_job_properties(int priority, const char* name, int* efficiency, int* memory) {
    *efficiency = priority * 10;
    *memory = priority * 100;
    if (strstr(name, "data") || strstr(name, "compute")) {
        *efficiency += 20; *memory += 512;
    } else if (strstr(name, "log") || strstr(name, "backup")) {
        *efficiency -= 10; *memory -= 256;
    }
    if (*efficiency < 1) *efficiency = 1;
    if (*memory < 100) *memory = 100;
}

int main() {
    PriorityQueue* pq = create_priority_queue();
    MinMaxHeap* mmh = create_minmax_heap();
    Trie* jobDatabase = create_trie();
    int running = 1;
    int job_count = 0;
    
    printf("\n Welcome to ECO-CLOUD JOB SCHEDULER!\n");
    
    while (running) {
        print_menu();
        printf("Enter your choice: ");
        
        char choice_str[10];
        if (fgets(choice_str, sizeof(choice_str), stdin) == NULL) continue;
        
        int choice;
        if (sscanf(choice_str, "%d", &choice) != 1) {
            printf(" Invalid input! Please enter a valid number.\n");
            continue;
        }
        
        switch (choice) {
            case 1: {
                printf("\nAdding new job...\n");
                char name[64];
                get_valid_string("Job name: ", name, sizeof(name));
                to_lowercase(name);
                int priority = get_valid_int("Priority (1-10, lower = higher priority): ", 1, 10);
                int efficiency, memory;
                calculate_job_properties(priority, name, &efficiency, &memory);
                PCB* p = create_pcb(name, efficiency, memory);
                if (p) {
                    enqueue(pq, p, priority);
                    minmax_insert(mmh, p, efficiency);
                    insert_job(jobDatabase, name, p);
                    job_count++;
                    printf("Job '%s' added successfully! (Total jobs: %d)\n\n", name, job_count);
                } else printf("Failed to create job. Memory allocation error.\n\n");
                break;
            }
            
            case 2: {
                if (job_count == 0) printf("No jobs in database. Please add some jobs first.\n\n");
                else {
                    printf("\nSearching for job...\n");
                    char name[64];
                    get_valid_string("Enter job name: ", name, sizeof(name));
                    to_lowercase(name);
                    PCB* found = search_job(jobDatabase, name);
                    if (found) {
                        printf("Job found:\n");
                        print_pcb_details(found);
                    } else printf("Job '%s' not found in database.\n", name);
                    printf("\n");
                }
                break;
            }
            
            case 3: {
                printf("\nScheduling next job...\n");
                if (!is_empty(pq)) {
                    PCB* job = dequeue(pq);
                    printf("Next scheduled job:\n");
                    print_pcb_details(job);
                    mark_job_scheduled(jobDatabase, job->job_id);
                    minmax_delete_by_pcb(mmh, job);
                    job_count--;
                } else printf("No jobs in queue to schedule.\n");
                printf("\n");
                break;
            }
            
            case 4: {
                printf("\nJob Efficiency Analysis\n");
                if (mmh->size > 0) {
                    printf("Most efficient job:\n");
                    print_pcb_details(minmax_peek_min(mmh));
                    printf("Least efficient job:\n");
                    print_pcb_details(minmax_peek_max(mmh));
                } else printf("No jobs in database.\n");
                printf("\n");
                break;
            }
            
            case 5: {
                if (job_count == 0) printf(" No jobs in database for spell check.\n\n");
                else {
                    printf("\n Job name spell checker...\n");
                    char name[64];
                    get_valid_string("Enter job name to check: ", name, sizeof(name));
                    to_lowercase(name);
                    PCB* found = search_job(jobDatabase, name);
                    if (found) printf("Name is correct!\n");
                    else printf("Did not find exact match.\n   Use option 2 (Search) to find similar jobs.\n");
                    printf("\n");
                }
                break;
            }
            
            case 6: {
                printf("\nAll Jobs in Database\n");
                if (job_count == 0) printf(" No jobs in database.\n");
                else {
                    printf("Total jobs: %d\n\n", job_count);
                    list_all_jobs(jobDatabase->root, "");
                }
                printf("\n");
                break;
            }
            
            case 0: {
                printf("\nShutting down...\n");
                running = 0;
                break;
            }
            
            default: {
                printf("Invalid choice! Please enter a number between 0-6.\n\n");
            }
        }
    }
    
    printf("Cleanup Summary:\n Destroying Priority Queue...\n");
    destroy_priority_queue(pq);
    printf(" Destroying MinMax Heap...\n");
    minmax_destroy(mmh);
    printf(" Destroying Job Database...\n");
    destroy_trie(jobDatabase);
    printf("\n ECO-CLOUD JOB SCHEDULER closed successfully!\n");
    return 0;
}
