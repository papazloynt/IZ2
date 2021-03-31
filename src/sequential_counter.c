//
// Created by chastikov on 31.03.2021.
//
#include "sequential_counter.h"
#include <stdio.h>

int seq_count(int* arg, const int size){
    int ch = 0;
    for (size_t i = 0; i < size; ++i){
        if (arg[i] % 2 == 0)
            ++ch;
    }
    return ch;
}