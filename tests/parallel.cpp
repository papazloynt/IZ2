#include "gtest/gtest.h"

extern "C" {
#include "parallel_counter.h"
#include <malloc.h>
}

TEST(parallel, true_res) {
    int size = 20;
    int* p = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i){
        p[i] = i;
    }
    int res = counter(p, size);
    ASSERT_EQ(res, 10);
}

TEST(parallel, big_numbers) {
    int size = 100000000;
    int* p = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i){
        p[i] = i % 2;
    }
    int res = counter(p, size);
    ASSERT_EQ(res, size / 2);
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}