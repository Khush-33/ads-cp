#ifndef JOB_TRIE_H
#define JOB_TRIE_H

#include "PCB.h"

typedef struct TrieNode {
    struct TrieNode* children[26];
    int isEndOfWord;
    PCB* process;
} TrieNode;

typedef struct {
    TrieNode* root;
} Trie;

Trie* create_trie();
void insert_job(Trie* trie, const char* jobId, PCB* p);
PCB* search_job(Trie* trie, const char* jobId);
void list_all_jobs(TrieNode* node, char* prefix);
void mark_job_scheduled(Trie* trie, const char* jobId);
void destroy_trie(Trie* trie);
int count_active_jobs(TrieNode* node);
#endif
