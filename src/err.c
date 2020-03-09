#include <stdio.h>
#include <hw1/struct.h>
#include <hw1/err.h>

int no_errors( array_return struct_to_check )
{
	switch( struct_to_check.errflag )
	{
	case 0:
		return 1;	
	case ERR_NAN:
		free_all( struct_to_check );
		printf("Ошибка! Вы ввели не число\n");
		return 0;
	case ERR_BIG_NUMBER:
		free_all( struct_to_check );
		printf("Ошибка! Вы ввели слишком большое число (>1000000) \n");
		return 0;
	case ERR_ALLOC:	
		free_all( struct_to_check );
		printf("Ошибка реаллокации\n");
		return 0;
	case ERR_ARR_EMPTY:
		free_all( struct_to_check );
		printf("Результирущий массив пуст\n");
		return 0;
	case ERR_BIG_INPUT:	
		free_all( struct_to_check );
		printf("Вводимый массив чисел слишком велик (>200 элементов)\n");
		return 0;
	default: 
		free_all( struct_to_check );
		printf("Неизвестная ошибка");
		return 0;
	}
};