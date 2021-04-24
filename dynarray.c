//
// Created by Nafany on 24.04.2021.
//

#include "dynarray.h"
#include "item.h"

DynArray* createArray(){
    DynArray* array = (DynArray*)malloc(sizeof(DynArray));
    array->maxsize = 8;
    array->size = 0;
    array->items = (Item**)malloc(sizeof(Item*) * 8);
    return array;
}

Item* getIndex(DynArray* array, int index){
    if(index > array->size){
        return NULL;
    }
    return array->items[index];
}

void add(DynArray** arrayosn, Item* item){
    DynArray* array = *arrayosn;
    Item** items = array->items;
    if(array->size == array->maxsize){
        array->maxsize += array->size;
        array->items = (Item**)realloc(array->items, (array->maxsize) * sizeof(Item*));
    }
    items[array->size] = item;
    array->size += 1;
}

void freeArray(DynArray* array){
    free(array->items);
    free(array);
}

void printArray(DynArray* array){
    Item** printer = array->items;
    for(int i = 0; i < array->size; i++){
        printInfo(*printer);
        printer++;
    }
}