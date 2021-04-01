#include "parallel_counter.h"
#include <stdio.h>
#include <malloc.h>


int main(int argc, char *argv[]){
    int size;
    scanf("%d", size);
    int* p = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i){
        p[i] = i;
    }
    // Чётные числа
    int num_ch = counter(p, size);
    printf("ch : %d \n nch : %d", num_ch, size - num_ch);
    free(p);
    return 0;
}
