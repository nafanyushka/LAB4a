//
// Created by Nafany on 22.04.2021.
//

#include "tree.h"

Tree* createTree(int key, Item* item){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    tree->previous = NULL;
    tree->key = key;
    tree->item = item;
    return tree;
}

Tree* findToDelete(Tree* first, int key){
    Tree* pointer = first;
    while(1 == 1){
        if(pointer->key == key)
            return pointer;
        if(key < pointer->key){
            pointer = pointer->left;
        }
        else{
            pointer = pointer->right;
        }
        if(pointer == NULL)
            return NULL;
    }
}

int delete(Tree** first, int key){
    Tree* delete = findToDelete(*first, key);
    if(delete == NULL)
        return 0;
    if(delete != *first) {
        if (delete->right == NULL && delete->left == NULL) {
            if (key > delete->previous->key) {
                delete->previous->right = NULL;
                freeItem(delete->item);
                free(delete);
                return 1;
            } else {
                delete->previous->left = NULL;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        if (delete->left == NULL && delete->right != NULL) {
            Tree* pointer = delete->previous;
            if(key > pointer->key){
                pointer->right = delete->right;
                pointer->right->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
            else{
                pointer->left = delete->right;
                pointer->left->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        if(delete->left != NULL && delete->right == NULL){
            Tree* pointer = delete->previous;
            if(key > pointer->key){
                pointer->right = delete->left;
                pointer->right->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
            else{
                pointer->left = delete->left;
                delete->left->previous = pointer;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        if(delete->left != NULL && delete->right != NULL){
            Tree* pointer = delete->left;
            Tree* previous = delete->previous;
            if(pointer->right == NULL){
                if(pointer->key > previous->key){
                    previous->right = pointer;
                    pointer->right = delete->right;
                    pointer->previous = delete->previous;
                    freeItem(delete->item);
                    free(delete);
                    return 1;
                }
                else{
                    previous->left = pointer;
                    pointer->right = delete->right;
                    pointer->previous = delete->previous;
                    freeItem(delete->item);
                    free(delete);
                    return 1;
                }
            }
            while(pointer->right != NULL){
                pointer = pointer->right;
            }
            pointer->previous->right = pointer->left;
            if(pointer->key > previous->key){
                previous->right = pointer;
                pointer->right = delete->right;
                pointer->left = delete->left;
                pointer->previous = delete->previous;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
            else{
                previous->left = pointer;
                pointer->right = delete->right;
                pointer->left = delete->left;
                pointer->previous = delete->previous;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
        }
        }
    else{
        if(delete->left == NULL && delete->right == NULL){
            freeItem(delete->item);
            free(delete);
            *first = NULL;
            return 1;
        }
        if(delete->left == NULL && delete->right != NULL){
            *first = delete->right;
            (*first)->previous = NULL;
            freeItem(delete->item);
            free(delete);
            return 1;
        }
        if(delete->left != NULL && delete->right == NULL){
            *first = delete->left;
            (*first)->previous = NULL;
            freeItem(delete->item);
            free(delete);
            return 1;
        }
        if(delete->left != NULL && delete->right != NULL){
            Tree* pointer = delete->left;
            if(pointer->right == NULL){
                *first = pointer;
                (*first)->right = delete->right;
                (*first)->previous = NULL;
                freeItem(delete->item);
                free(delete);
                return 1;
            }
            while(pointer->right != NULL){
                pointer = pointer->right;
            }
            pointer->previous->right = pointer->left;
            pointer->left = delete->left;
            pointer->right = delete->right;
            *first = pointer;
            (*first)->previous = NULL;
            freeItem(delete->item);
            free(delete);
            return 1;
        }
    }
}



int addTree(Tree** first, Tree* plug){
    int key = plug->key;
    if(*first == NULL){
        *first = plug;
        return 0;
    }
    Tree* putIn = *first;
    while(1 == 1){
        if(key == putIn->key){
            plug->left = putIn->left;
            putIn->left = plug;
            plug->right = NULL;
            return 0;
        }
        if(key <= putIn->key){
            if(putIn->left != NULL){
                putIn = putIn->left;
                continue;
            }
            else{
                putIn->left = plug;
                plug->previous = putIn;
                return 0;
            }
        }
        else{
            if(putIn->right != NULL){
                putIn = putIn->right;
                continue;
            }
            else{
                putIn->right = plug;
                plug->previous = putIn;
                return 0;
            }
        }
    }
}

void printTree(Tree* tree){
    if(tree == NULL) {
        printf("На данный момент дерево пусто.\n");
        return;
    }
    if(tree->left == NULL && tree->right == NULL){
        printInfo(tree->item);
    }
    if(tree->left != NULL && tree->right != NULL){
        printTree(tree->left);
        printInfo(tree->item);
        printTree(tree->right);
    }
    if(tree->left != NULL && tree->right == NULL){
        printTree(tree->left);
        printInfo(tree->item);
    }
    if(tree->left == NULL && tree->right != NULL){
        printInfo(tree->item);
        printTree(tree->right);
    }
}

DynArray* findKey(Tree* tree, int key){
    DynArray* items = createArray();
    Tree* seeker = tree;
    while(seeker != NULL && seeker->key != key) {
        if (key > seeker->key)
            seeker = seeker->right;
        else
            seeker = seeker->left;
    }
    if(seeker == NULL) {
        freeArray(items);
        return NULL;
    }
    while(1 == 1){
        if(seeker != NULL){
            if(seeker->key != key)
                return items;
            else{
                add(&items, seeker->item);
                seeker = seeker->left;
            }
        }
        else
            return items;
    }
}

DynArray* findLess(Tree* tree, int key){
    Tree* finder = tree;
    Tree* variant = tree;
    while(finder != NULL){
        if(key == finder->key) {
            variant = finder;
            break;
        }
        if(key > finder->key){
            finder = finder->right;
            if(finder == NULL)
                break;
            else{
                if (key < finder->key && abs(finder->key - key) < abs(variant->key - key) || key > variant->key) {
                    variant = finder;
                }
            }
        }
        else{
            finder = finder->left;
            if(finder == NULL)
                break;
            else{
                if (key < finder->key && abs(finder->key - key) < abs(variant->key - key) || key > variant->key) {
                    variant = finder;
                }
            }
        }
    }
    if(key > tree->key && variant == tree)
        return NULL;
    if(key > variant->key){
        return NULL;
    }
    DynArray* array = createArray();
    int newKey = variant->key;
    while(variant != NULL){
        if(variant->key == newKey){
            add(&array, variant->item);
            variant = variant->left;
        }
        else{
            break;
        }
    }
    return array;
}

void printTreeKeys(Tree* tree, int i){
    if(tree == NULL) {
        return;
    }
    printTreeKeys(tree->right, i + 1);
    for(int space = 0; space < i; space++){
        printf(" ");
    }
    printf("%d\n", tree->key);
    printTreeKeys(tree->left, i + 1);
}
