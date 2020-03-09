#include <hw1/struct.h>

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