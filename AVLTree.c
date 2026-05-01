#include "AVLTree.h"
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* node) {
    return (node == NULL) ? 0 : node->height;
}

int get_balance(AVLNode* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

AVLNode* insert_avl(AVLNode* node, PCB* job, int execution_time) {
    if (node == NULL) {
        AVLNode* new_node = (AVLNode*)malloc(sizeof(AVLNode));
        new_node->job = job;
        new_node->execution_time = execution_time;
        new_node->left = new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }
    
    if (execution_time < node->execution_time)
        node->left = insert_avl(node->left, job, execution_time);
    else if (execution_time > node->execution_time)
        node->right = insert_avl(node->right, job, execution_time);
    else
        return node;
    
    node->height = 1 + max(height(node->left), height(node->right));
    
    int balance = get_balance(node);
    
    if (balance > 1 && execution_time < node->left->execution_time)
        return right_rotate(node);
    
    if (balance < -1 && execution_time > node->right->execution_time)
        return left_rotate(node);
    
    if (balance > 1 && execution_time > node->left->execution_time) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    
    if (balance < -1 && execution_time < node->right->execution_time) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    
    return node;
}

AVLNode* search_avl(AVLNode* node, int execution_time) {
    if (node == NULL || node->execution_time == execution_time)
        return node;
    
    if (execution_time < node->execution_time)
        return search_avl(node->left, execution_time);
    else
        return search_avl(node->right, execution_time);
}

void range_query_avl(AVLNode* node, int min_time, int max_time) {
    if (node == NULL) return;
    
    if (node->execution_time > min_time)
        range_query_avl(node->left, min_time, max_time);
    
    if (node->execution_time >= min_time && node->execution_time <= max_time) {
        printf("  %s: %d seconds\n", node->job->job_id, node->execution_time);
    }
    
    if (node->execution_time < max_time)
        range_query_avl(node->right, min_time, max_time);
}

void inorder_avl(AVLNode* node) {
    if (node == NULL) return;
    
    inorder_avl(node->left);
    printf("  %s: %d seconds\n", node->job->job_id, node->execution_time);
    inorder_avl(node->right);
}

AVLTree* create_avl_tree() {
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

void destroy_avl(AVLNode* node) {
    if (node == NULL) return;
    
    destroy_avl(node->left);
    destroy_avl(node->right);
    free(node);
}

void destroy_avl_tree(AVLTree* tree) {
    if (tree == NULL) return;
    destroy_avl(tree->root);
    free(tree);
}
