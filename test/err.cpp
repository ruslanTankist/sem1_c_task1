#include "gtest/gtest.h"

extern "C" {
    #include "hw1/struct.h"
    #include "hw1/err.h"
}

TEST(struct, ok) {
    array_return test_struct = { NULL, 0, NULL, 0, 0 };
    test_struct.o_arr_ptr = (int **)malloc(2 * sizeof(int));
    test_struct.o_arr_ptr[0] = (int *)malloc(10 * sizeof(int));
    test_struct.o_arr_ptr[1] = (int *)malloc(11 * sizeof(int));

    if(!no_errors(test_struct))
        ASSERT_TRUE(test_struct.o_arr_ptr == NULL);
}