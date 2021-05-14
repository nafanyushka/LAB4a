//
// Created by Nafany on 07.05.2021.
//

#include "dialogue.h"

int main(){
    FILE* fd = fopen("test", "wb");
    int key = 0;
    do{
        printf("k ");
        key = getInt();
        printf("n ");
        float num = getFloat();
        fwrite(&key, sizeof(int), 1, fd);
        fwrite(&num, sizeof(float), 1, fd);
    } while(key != 90);
    fclose(fd);
    return 0;
}