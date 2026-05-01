#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "PCB.h"

typedef struct AVLNode {
    PCB* job;
    int execution_time;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

typedef struct {
    AVLNode* root;
    int size;
} AVLTree;

AVLTree* create_avl_tree();
AVLNode* insert_avl(AVLNode* node, PCB* job, int execution_time);
AVLNode* delete_avl(AVLNode* node, int execution_time);
AVLNode* search_avl(AVLNode* node, int execution_time);
void range_query_avl(AVLNode* node, int min_time, int max_time);
void inorder_avl(AVLNode* node);
void destroy_avl(AVLNode* node);
void destroy_avl_tree(AVLTree* tree);

int max(int a, int b);
int height(AVLNode* node);
int get_balance(AVLNode* node);
AVLNode* right_rotate(AVLNode* y);
AVLNode* left_rotate(AVLNode* x);

#endif
