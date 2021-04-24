//
// Created by Nafany on 22.04.2021.
//

#include "item.h"

Item* createItem(float number, char* text, int key){
    Item* item = (Item*)malloc(sizeof(Item));
    item->number = number;
    item->text = text;
    item->key = key;
    return item;
}

void printInfo(Item* item){
    printf("Ключ: %d. Информация: %f, %s.\n",item->key, item->number, item->text);
}

void freeItem(Item* item){
    free(item->text);
    free(item);
}