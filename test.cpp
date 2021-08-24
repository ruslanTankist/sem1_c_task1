#include <gtest/gtest.h>

extern "C" {
    #include "struct.h"
    #include "functionality.h"
}

class TestInput : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            array_return input0 = { NULL, 0, NULL, 0, 0 };
            input0.i_arr_ptr = (int *)malloc(3 * sizeof(int));
            input0.i_arr_ptr[0] = 2;
            input0.i_arr_ptr[1] = 2;
            input0.i_arr_ptr[2] = 3;
            input0.i_len = 3;

            input1 = input0;
            input1 = number_frequency( input0 );
        }
        void TearDown() override
        {
            free_all( input1 );
        }
        array_return input1;
};

::testing::AssertionResult NotEmpty(array_return arr)
{   
    if( arr.i_arr_ptr != NULL && arr.i_len != 0 && arr.o_arr_ptr != NULL && arr.o_len != 0)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure();
    
}

TEST_F(TestInput, NotEmpty) {
    EXPECT_TRUE( NotEmpty( input1 ));
}

TEST_F(TestInput, isCorrect) {
    ASSERT_TRUE(input1.o_arr_ptr[0][0] == 2 && input1.o_arr_ptr[1][0] == 2 && input1.o_len == 2);
}