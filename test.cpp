#include <gtest/gtest.h>

extern "C" {
    #include "struct.h"
    #include "functionality.h"
}

TEST(struct, ok) {
    array_return test_struct = { NULL, 0, NULL, 0, 0 };
    test_struct.o_arr_ptr = (int **)malloc(2 * sizeof(int));
    test_struct.o_arr_ptr[0] = (int *)malloc(10 * sizeof(int));
    test_struct.o_arr_ptr[1] = (int *)malloc(11 * sizeof(int));

    if(!no_errors(test_struct))
        ASSERT_TRUE(test_struct.o_arr_ptr == NULL);
}

TEST(struct, ok) {
    array_return test_check = { NULL, 0, NULL, 0, 0 };
    array_return test_struct = test_check;
    test_struct.i_arr_ptr = (int *)malloc( 100 * sizeof(int) );
    test_struct.o_arr_ptr = (int **)malloc( 100 * sizeof(int) );
    free_all(test_struct);
    ASSERT_EQ(test_struct, test_check);
}