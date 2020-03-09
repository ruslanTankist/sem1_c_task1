#include <stdio.h>
#include <hw1/struct.h>
#include <hw1/err.h>
#include <hw1/io.h>

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
			if( !((int)ch >= 48) || !((int)ch <= 57)) { input_struct.errflag = ERR_NAN; return input_struct; }
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
};

array_return output( array_return output_struct)
{
	if( output_struct.o_len < 1 ) { output_struct.errflag = ERR_ARR_EMPTY; return output_struct; }
	for( int i = 0; i < output_struct.o_len; i++ )
		printf("%d - %d\n", output_struct.o_arr_ptr[0][i], output_struct.o_arr_ptr[1][i]);
	return output_struct;
};