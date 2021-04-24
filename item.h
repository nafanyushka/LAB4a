//
// Created by Nafany on 22.04.2021.
//

#ifndef LAB4A_ITEM_H
#define LAB4A_ITEM_H

#include "dynarray.h"

typedef struct Item Item;

struct Item{
    float number;
    char* text;
    int key;
};

Item* createItem(float number, char* text, int key);
void printInfo(Item* item);
void freeItem(Item* item);

#endif //LAB4A_ITEM_H
