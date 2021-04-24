//
// Created by Nafany on 22.04.2021.
//

#include "dialogue.h"

void dialogue(){
    printf("Введите первый ключ и информацию.\nКлюч: ");
    int key = getInt();
    printf("Число с плавающей точкой: ");
    float number = getFloat();
    char* text;

    do {
        printf("Строка: ");
        text = get_String();
    }while(strlen(text) < 1);

    Tree* tree = createTree(key, createItem(number, text, key));

    int choose;
    DynArray* items;
    Item* item;

    do{
        printf("\nВведите 1, чтобы добавить элемент в дерево.\n"
               "Введите 2, чтобы вывести дерево с информацией в порядке возрастания.\n"
               "Введите 3, чтобы вывести дерево.\n"
               "Введите 4, чтобы найти элемент(ы) по ключу.\n"
               "Введите 5, чтобы найти ближайший элемент к заданному ключу.\n"
               "Введите 6, чтобы удалить элемент по ключу.\n"
               "Введите 0, чтобы выйти из дерева.\n");
        choose = getInt();

        switch (choose) {

            case 0:
                break;
            case 1:
                printf("Введите первый ключ и информацию.\nКлюч: ");
                key = getInt();
                printf("Число с плавающей точкой: ");
                number = getFloat();
                do {
                    printf("Строка: ");
                    text = get_String();
                }while(strlen(text) < 1);
                addTree(&tree, createTree(key, createItem(number, text, key)));
                break;
            case 2:
                printf("\n\t////////////////////// ДЕРЕВО //////////////////////\n");
                printTree(tree);
                printf("\t////////////////////////////////////////////////////\n");
                break;
            case 3:
                printf("\n\n");
                printTreeKeys(tree, 0);
                printf("\n");
                break;
            case 4:
                printf("Введите ключ для поиска: ");
                key = getInt();
                items = findKey(tree, key);
                if(items == NULL) {
                    printf("Не найдено таких айтемов.\n");
                    break;
                }
                else{
                    printArray(items);
                }
                freeArray(items);
                break;
            case 5:
                printf("Введите ключ для поиска минимального: ");
                key = getInt();
                items = findLess(tree, key);
                if(items == NULL){
                    printf("Ничего не найдено.\n");
                }
                else{
                    printArray(items);
                    freeArray(items);
                }
                break;
            case 6:
                printf("Введите ключ для удаляшки: ");
                key = getInt();
                if(delete(&tree, key))
                    printf("Удачное удаление.\n");
                else
                    printf("Не найден элемент с таким ключом.\n");
                break;
            default:
                break;

        }
    }while(choose != 0);

}