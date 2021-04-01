//
// Created by chastikov on 31.03.2021.
//

#ifndef IDZ_2_PARALLEL_COUNTER_H
#define IDZ_2_PARALLEL_COUNTER_H

// Возвращаю только чётные элементы, т.к. нечётные это size - количество чётных
void* thread_work(void* arg);

int counter (int* arg, const int size);

#endif //IDZ_2_PARALLEL_COUNTER_H
