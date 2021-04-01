// private headers
#include "parallel_counter.h"
// c headers
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct info {
    // массив чисел
    int* arr;
    // массив счётчиков
    int* l_arr;
    // От какого числа
    size_t from;
    // До какого числа
    size_t to;
    // Номер счётчика в l_arr
    size_t i;
} info_t;


void* thread_work(void* arg){
    info_t* tmp = (info_t*)arg;
    for (size_t i = tmp->from; i < tmp->to; ++i){
        if (tmp->arr[i] % 2 == 0)
            ++tmp->l_arr[tmp->i];
    }
    return arg;
}

int parallel_count (int* arg, const int size){
    // Максимальное колическтво потоков
    const int numCPU = sysconf(_SC_NPROCESSORS_ONLN);;
    // Массив потоков
    pthread_t threadIds[numCPU];
    // Конечный массив, где будем считать количество чётных элементов
    int* last_array = (int*)malloc(numCPU * sizeof(int));

    for (int i = 0; i < numCPU; ++i){
        last_array[i] = 0;
    }
    // Массив структур, для потоков, чтобы не менялись
    // значения полей в процессе их работы
    info_t* infos = (info_t*)malloc(numCPU * sizeof(info_t));

    // Количество ячеек, которые обрабатывает каждый поток
    int col = size / numCPU;


    for (size_t i = 0; i < numCPU; ++i){
        // заполняем структуру
        infos[i].arr = arg;
        infos[i].l_arr = last_array;
        infos[i].from = i * col;
        if (i != numCPU - 1) {
            infos[i].to = i * col + col;
        } else {
            infos[i].to = size;
        }
        infos[i].i = i;
        pthread_create(&threadIds[i], NULL, thread_work, (void*)&infos[i]);
    }

    for (size_t i = 0; i < numCPU; ++i){
        pthread_join(threadIds[i], NULL);
    }

    int sum = 0;
    for (size_t i = 0; i < numCPU; ++i){
        sum += last_array[i];
    }
    return sum;
}