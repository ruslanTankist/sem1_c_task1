#include <stdio.h>
#include "struct.h"
#include "functionality.h"

//input of numbers' array
array_return input( array_return input_struct )
{
    int * tmp = (int *)malloc( MAX_INPUT_SIZE * sizeof(int) );
    if( !tmp ) { input_struct.errflag = ERR_ALLOC; return input_struct; }
    input_struct.i_arr_ptr = tmp;

    int cur_num = 0;
    int flag_new_num = 0;
    printf("Печатайте числа через пробел, для завершения нажмите Enter\n");
    char ch = getc(stdin);
    do
    {				
        if(ch != ' ' && ch != '\n')
        {
            if( !((int)ch >= '0') || !((int)ch <= '9')) { input_struct.errflag = ERR_NAN; return input_struct; }
            if( cur_num > ( MAX_INT )) { input_struct.errflag = ERR_BIG_NUMBER; return input_struct; }
            cur_num *= 10;
            cur_num += (int)ch - 48;
            flag_new_num = 1;
        }
        else
        {		
            if( flag_new_num )
            {
                input_struct.i_len++;	
                if (input_struct.i_len >= MAX_INPUT_SIZE - 1) { input_struct.errflag = ERR_BIG_INPUT; return input_struct; }
                input_struct.i_arr_ptr[input_struct.i_len-1] = cur_num;
                cur_num = 0;
                flag_new_num = 0;
            }
        }
        if(ch == '\n')
        break;
        ch = getc(stdin);
    } while(1);

    if(input_struct.i_len == 0) { input_struct.errflag = ERR_ARR_EMPTY; return input_struct; }
	
    tmp = (int *)realloc( input_struct.i_arr_ptr, input_struct.i_len * sizeof(int) );
    if(!tmp) { input_struct.errflag = ERR_ALLOC; return input_struct; }
    input_struct.i_arr_ptr = tmp;
	
    return input_struct;
}

//output of histogram table: *number* - *amount*
array_return output( array_return output_struct)
{
    if( output_struct.o_len < 1 ) { output_struct.errflag = ERR_ARR_EMPTY; return output_struct; }
    for( int i = 0; i < output_struct.o_len; i++ )
        printf("%d - %d\n", output_struct.o_arr_ptr[0][i], output_struct.o_arr_ptr[1][i]);
    return output_struct;
}

void free_all( array_return struct_to_free )
{
    if( struct_to_free.o_arr_ptr )
    {
        if( struct_to_free.o_arr_ptr[0] )
            free( struct_to_free.o_arr_ptr[0] );
        if( struct_to_free.o_arr_ptr[1] )
            free( struct_to_free.o_arr_ptr[1] );
        free( struct_to_free.o_arr_ptr );
	}
    if( struct_to_free.i_arr_ptr )
        free( struct_to_free.i_arr_ptr );
}

int print_error_msg( const int error_code )
{
    switch( error_code )
    {
    case 0:
        return 0;	
    case ERR_NAN:
        printf("Ошибка! Вы ввели не число\n");
        return 1;
    case ERR_BIG_NUMBER:
        printf("Ошибка! Вы ввели слишком большое число (>1000000) \n");
        return 1;
	case ERR_ALLOC:	
		printf("Ошибка реаллокации\n");
		return 1;
    case ERR_ARR_EMPTY:
        printf("Результирущий массив пуст\n");
        return 1;
    case ERR_BIG_INPUT:	
        printf("Вводимый массив чисел слишком велик (>200 элементов)\n");
        return 1;
    case ERR_WRONG_AMOUNT:
        printf("Ошибка output[0] != output[1]\n");
        return 1;
    default: 
        printf("Неизвестная ошибка\n");
        return 1;
	}
}

array_return number_frequency( array_return this_struct )
{
    if( !this_struct.i_len || !this_struct.i_arr_ptr ) { this_struct.errflag = ERR_WRONG_AMOUNT; return this_struct; }

    this_struct.o_arr_ptr = (int **)malloc( 2 * sizeof(int *) );
    if( !this_struct.o_arr_ptr ) { this_struct.errflag = ERR_ALLOC; return this_struct; }

    this_struct.o_arr_ptr[0] = (int *)malloc( this_struct.i_len * sizeof(int) );
    if(!this_struct.o_arr_ptr[0]) { this_struct.errflag = ERR_ALLOC; return this_struct; }

    this_struct.o_arr_ptr[1] = (int *)malloc( this_struct.i_len * sizeof(int) );
    if(!this_struct.o_arr_ptr[1]) { this_struct.errflag = ERR_ALLOC; return this_struct; }

    int index_to_inc = 0;

    for (int i = 0; i < this_struct.i_len; i++)
    {
        int cur_num = this_struct.i_arr_ptr[i];
        int flag_is_new = 1;

        for (int j = 0; j < (this_struct.o_len); j++)
        {
            if (this_struct.o_arr_ptr[0][j] == cur_num)
            {
                flag_is_new = 0;
                index_to_inc = j;
                break;
            }
        }

        if (flag_is_new)
        {
            this_struct.o_arr_ptr[0][this_struct.o_len] = cur_num;
            this_struct.o_arr_ptr[1][this_struct.o_len] = 1;
            this_struct.o_len++;
        }
        else
        {
            this_struct.o_arr_ptr[1][index_to_inc]++;
        }
    } 

    int * tmp = realloc( this_struct.o_arr_ptr[0], this_struct.o_len * sizeof(int) );
    if (!tmp)	{ this_struct.errflag = ERR_ALLOC; return this_struct; }
    this_struct.o_arr_ptr[0] = tmp;

    tmp = realloc(this_struct.o_arr_ptr[1], this_struct.o_len * sizeof(int));
    if (!tmp)	{ this_struct.errflag = ERR_ALLOC; return this_struct; }
    this_struct.o_arr_ptr[1] = tmp;

    return this_struct;
}