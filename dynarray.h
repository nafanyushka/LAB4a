//
// Created by Nafany on 24.04.2021.
//

#ifndef LAB4A_DYNARRAY_H
#define LAB4A_DYNARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DynArray DynArray;
typedef struct Item Item;

struct DynArray{
    Item** items;
    int maxsize;
    int size;
};

DynArray* createArray();
Item* getIndex(DynArray* array, int index);
void add(DynArray** array, Item* item);
void freeArray(DynArray* array);
void printArray(DynArray* array);

#endif //LAB4A_DYNARRAY_H
