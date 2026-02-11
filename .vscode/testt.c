#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREE struct tree

TREE {
    int value;
    TREE* left;
    TREE* right;
};

TREE* create_tree(int val) {
    TREE* newNode = (TREE*)malloc(sizeof(TREE));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    newNode->value = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void pre_order(TREE* T) {
    if (T == NULL) return;
    printf("%d ", T->value);
    pre_order(T->left);
    pre_order(T->right);
}

void post_order(TREE* T) {
    if (T == NULL) return;
    post_order(T->left);
    post_order(T->right);
    printf("%d ", T->value);
}

void in_order(TREE* T) {
    if (T == NULL) return;
    in_order(T->left);
    printf("%d ", T->value);
    in_order(T->right);
}

TREE* add_node(TREE* root, int value) {
    if (root == NULL) 
        return create_tree(value);
  
    if (value < root->value) {
        root->left = add_node(root->left, value);
    }
    else if (value > root->value) {
        root->right = add_node(root->right, value);
    }
    return root;
}

int main() {
    TREE* root = NULL;
    FILE* file = fopen("Nums.txt", "r");
    char line[256];
    
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            root = add_node(root, atoi(line));
        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
        return 1;
    }

    printf("\npre-order: ");
    pre_order(root);
    
    printf("\npost-order: ");
    post_order(root);
    
    printf("\nin-order: ");
    in_order(root);
    
    printf("\n");
    return 0;
}