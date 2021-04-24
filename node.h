//
// Created by Nafany on 23.04.2021.
//

#ifndef LAB4A_NODE_H
#define LAB4A_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct Item Item;

struct Node{
    Item* item;
    Node* next;
};

Node* nodeInit();
void nodeAdd(Node** node, Item* item);
void printNode(Node* node);
void freeNode(Node* node);

#endif //LAB4A_NODE_H
