//
// Created by Nafany on 22.04.2021.
//

#ifndef LAB4A_TREE_H
#define LAB4A_TREE_H

#include "item.h"

typedef struct Tree Tree;

struct Tree{
    Item* item;
    int key;
    Tree* left;
    Tree* right;
    Tree* previous;
    Tree* next;
};
Tree* createTree(int key, Item* item);
int addTree(Tree** first, Tree* plug);
void printTree(Tree* tree);
int delete(Tree** first, int key);
DynArray* findKey(Tree* tree, int key);
DynArray* findLess(Tree* tree, int key);
void printTreeKeys(Tree* tree, int i);
void freeTree(Tree* tree);
void f_Timing();
void d_Timing();

#endif //LAB4A_TREE_H
