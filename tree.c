//
// Created by Nafany on 22.04.2021.
//

#include <time.h>

#include "tree.h"

Tree* createTree(int key, Item* item){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    tree->previous = NULL;
    tree->next = NULL;
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
    Tree* deleter = *first;
    Tree* before = deleter;
    while(deleter->key != key){
        if(key <= deleter->key){
            before = deleter;
            deleter = deleter->left;
        }
        else{
            before = deleter;
            deleter = deleter->right;
        }
        if(deleter == NULL)
            return 0; //НЕ НАЙДЕН ТАКОЙ КЛЮЧ
    }
    Tree* previous = deleter->previous;
    Tree* next = deleter->next;
    if(previous == NULL && next == NULL){
        freeTree(deleter);
        *first = NULL;
        return 1;
    }
    if(previous == NULL && next != NULL){
        next->previous = NULL;
        if(next == before){
            before->left = NULL;
            freeItem(deleter->item);
            free(deleter);
            return 1;
        }
        else if(deleter->right == next) {
            if(deleter == *first)
                *first = next;
            else
                before->left = deleter->right;
            freeItem(deleter->item);
            free(deleter);
            return 1;
        }
        if(deleter == *first){
            *first = deleter->right;
        }
        else if(key <= before->key){
            before->left = deleter->right;
        }
        else{
            before->right = deleter->right;
        }
        freeItem(deleter->item);
        free(deleter);
        return 1;
    }
    if(previous != NULL && next == NULL){
        previous->next = NULL;
        if(before == previous){
            before->right = NULL;
            freeItem(deleter->item);
            free(deleter);
            return 1;
        }
        else if(deleter->left == previous){
            if(deleter == *first)
                *first = deleter->left;
            else
                before->right = deleter->left;
            freeItem(deleter->item);
            free(deleter);
            return 1;
        }
        if(deleter == *first){
            *first = deleter->left;
        }
        else if(key <= before->key){
            before->left = deleter->left;
        }
        else{
            before->right = deleter->left;
        }
        freeItem(deleter->item);
        free(deleter);
        return 1;
    }
/* TODO:
     *  По бокам нули.
     *  У превиуса есть левая ветка, и хрен что с ней сделаешь
     *
     *
                                                             */
    next->previous = previous;
    previous->next = next;
    Tree* pro = previous;
    while(pro->right != previous){
        pro = pro->previous;
        if(pro == NULL)
            break;
    }
    if(deleter->left == NULL && deleter->right == NULL){
        if(key <= before->key)
            before->left = NULL;
        else
            before->right = NULL;
        freeItem(deleter->item);
        free(deleter);
        return 1;
    }
    if(deleter->previous == deleter->left){
        if(deleter == *first){
            *first = previous;
        }
        else if(key <= before->key){
            before->left = previous;
        }
        else
            before->right = previous;
        previous->right = deleter->right;
        freeItem(deleter->item);
        free(deleter);
        return 1;
    }
    if(before == deleter->previous){
        before->right = deleter->right;
        previous->right = deleter->right;
        freeItem(deleter->item);
        free(deleter);
        return 1;
    }
    if(pro == NULL){
        if(previous->left == NULL){
            if(deleter == *first)
                *first = previous;
            else if(key <= before->key)
                before->left = previous;
            else
                before->right = previous;
            previous->left = deleter->left;
            previous->right = deleter->right;
            freeItem(deleter->item);
            free(deleter);
            return 1;
        }
        else{
            if(deleter == *first)
                *first = previous;
            else if(key <= before->key)
                before->left = previous;
            else
                before->right = previous;
            previous->left->right = previous->right;
            previous->left = deleter->left;
            previous->right = deleter->right;
            freeItem(deleter->item);
            free(deleter);
            return 1;
        }
    }
    else{
        Tree* lastBranch = previous;
        Tree* left = lastBranch->left;
        while(left != NULL){
            if(left->key == lastBranch->key)
                lastBranch = left;
            else
                break;
            left = left->left;
        }
        if(deleter == *first)
            *first = previous;
        else if(key <= before->key)
            before->left = previous;
        else
            before->right = previous;
        pro->right = lastBranch->left;
        lastBranch->left = deleter->left;
        previous->right = deleter->right;
        freeItem(deleter->item);
        free(deleter);
        return 1;
    }
}

void addLeft(Tree* tree, Tree* plug){
    if(tree->previous != NULL){
        tree->left = plug;
        tree->previous->next = plug;
        plug->previous = tree->previous;
        tree->previous = plug;
        plug->next = tree;
    }
    else{
        tree->left = plug;
        plug->previous = NULL;
        tree->previous = plug;
        plug->next = tree;
    }
}


void addRight(Tree* tree, Tree* plug){
    if(tree->next != NULL){
        tree->right = plug;
        plug->next = tree->next;
        tree->next->previous = plug;
        tree->next = plug;
        plug->previous = tree;
    }
    else{
        tree->right = plug;
        plug->next = NULL;
        tree->next = plug;
        plug->previous = tree;
    }
}

void addEquals(Tree* tree, Tree* plug){
    if(tree->left != NULL){
        plug->next = tree;
        plug->previous = tree->previous;
        tree->previous->next = plug;
        tree->previous = plug;
        plug->left = tree->left;
        tree->left = plug;
    }
    else{
        plug->next = tree;
        plug->previous = tree->previous;
        if(tree->previous != NULL){
            tree->previous->next = plug;
        }
        tree->previous = plug;
        tree->left = plug;
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
            addEquals(putIn, plug);
            return 0;
        }
        if(key <= putIn->key){
            if(putIn->left != NULL){
                putIn = putIn->left;
                continue;
            }
            else{
                addLeft(putIn, plug);
                return 0;
            }
        }
        else{
            if(putIn->right != NULL){
                putIn = putIn->right;
                continue;
            }
            else{
                addRight(putIn, plug);
                return 0;
            }
        }
    }
}

void printTree(Tree* tree){
    Tree* node = tree;
    if(node == NULL)
        return;
    while(node->left != NULL){
        node = node->left;
    }
    while(node != NULL){
        printInfo(node->item);
        node = node->next;
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

void freeTree(Tree* tree){
    if(tree == NULL) {
        return;
    }
    freeTree(tree->right);
    freeItem(tree->item);
    freeTree(tree->left);
    free(tree);
}

void f_Timing(){
    Tree* root = NULL;
    int n = 10, key[10000], k, cnt = 1000000, i, m;
    clock_t first, last;
    while(n-- > 0){
        srand(time(NULL));
        for(i = 0; i < 10000; i++)
            key[i] = rand() * rand();
        for(i = 0; i < cnt; ){
            k = rand() * rand();
            if(!addTree(&root, createTree(k, createItem(0, "0", k))))
                i++;
        }
        m = 0;
        first = clock();
        for(i = 0; i < 10000; i++) {
            if(i % 1000 == 0){
                printf("|");
            }
            if (findKey(root, key[i]))
                m++;
        }
        last = clock();
        printf("\n%d объектов найдено.\n", m);
        printf("Тест номер %d. Число узлов дерева: %d, время: %f сек.\n", (10 - n), (10 - n) * cnt,
               (float)(last - first) / CLOCKS_PER_SEC);
    }
    freeTree(root);
}

void d_Timing(){
    Tree* root = NULL;
    int n = 10, key[10000], k, cnt = 1000000, i, m;
    clock_t first, last;
    while(n-- > 0) {
        srand(time(NULL));
        for (i = 0; i < 10000; i++)
            key[i] = rand() * rand();
        for (i = 0; i < cnt;) {
            k = rand() * rand();
            if (!addTree(&root, createTree(k, createItem(0, "0", k))))
                i++;
        }
        m = 0;
        first = clock();
        for(i = 0; i < 10000; i++) {
            if(i % 1000 == 0){
                printf("|");
            }
            if (delete(&root, key[i]))
                m++;
        }
        last = clock();
        printf("\n%d объектов удалено.\n", m);
        printf("Тест номер %d. Число узлов дерева: %d, время: %d сек.\n", (10 - n), (10 - n) * cnt,
               (int)(last - first) / CLOCKS_PER_SEC);
    }
    freeTree(root);
}
