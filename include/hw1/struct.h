#ifndef _STRUCT_H_
#define _STRUCT_H_

#define MAX_INPUT_SIZE (200)

#include <stdlib.h>

typedef struct {
	int * i_arr_ptr;
	int i_len;
	int ** o_arr_ptr;
	int o_len;
	int errflag;
} array_return;

void free_all( array_return );

#endif