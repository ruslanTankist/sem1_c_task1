#include <hw1/struct.h>
#include <hw1/err.h>
#include <hw1/numfreq.h>

array_return number_frequency( array_return this_struct )
{
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
			if (this_struct.o_arr_ptr[0][j] == cur_num)
			{
				flag_is_new = 0;
				index_to_inc = j;
				break;
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
	
	int * tmp;
	tmp = realloc( this_struct.o_arr_ptr[0], this_struct.o_len * sizeof(int) );
	if (!tmp)	{ this_struct.errflag = ERR_ALLOC; return this_struct; }
	this_struct.o_arr_ptr[0] = tmp;
	
	tmp = realloc(this_struct.o_arr_ptr[1], this_struct.o_len * sizeof(int));
	if (!tmp)	{ this_struct.errflag = ERR_ALLOC; return this_struct; }
	this_struct.o_arr_ptr[1] = tmp;
	
	return this_struct;
};