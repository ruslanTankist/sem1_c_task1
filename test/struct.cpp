#include <gtest/gtest.h>

extern "C" {
    #include "hw1/struct.h"
}

TEST(struct, ok) {
    array_return test_check = { NULL, 0, NULL, 0, 0 };
    array_return test_struct = test_check;
    test_struct.i_arr_ptr = (int *)malloc( 100 * sizeof(int) );
    test_struct.o_arr_ptr = (int **)malloc( 100 * sizeof(int) );
    free_all(test_struct);
    ASSERT_EQ(test_struct, test_check);
}