//
// Created by chastikov on 31.03.2021.
//
#include "sequential_counter.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    int size = 20;
    int* p = (int*)malloc(size * sizeof(int)); //Необходимо 100 млн. элементов
    for (int i = 0; i < size; ++i){
        p[i] = i;
    }
    int num_ch = seq_count(p, size);
    printf("ch : %d \n nch : %d", num_ch, size - num_ch);
    free(p);
    return 0;
}
