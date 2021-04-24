//
// Created by Nafany on 23.04.2021.
//

#include "node.h"
#include "item.h"

Node* nodeInit(){
    Node* node = (Node*)calloc(sizeof(Node), 1);
    return node;
}
void nodeAdd(Node** node, Item* item){
    if((*node)->item == NULL){
        (*node)->item = item;
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = *node;
    *node = newNode;
}
void printNode(Node* node){
    Node* printer = node;
    while(printer != NULL){
        printInfo(printer->item);
        printer = printer->next;
    }
}
void freeNode(Node* node){
    Node* checker = node;
    while(checker != NULL){
        Node* deleter = checker;
        checker = checker->next;
        free(deleter);
    }
    node = NULL;
}