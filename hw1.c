// Условие ИЗ№1:

/*Составить программу расчета гистограммы, отражающей, сколько раз каждое число встречается в заданном массиве целых чисел.
Расчет оформить в виде функции, получающей на вход массив указателей на целые числа. На выход функция должна вернуть массив 
из двух указателей на массивы указателей(тройной указатель). Первый массив должен содержать указатели на встречающиеся во входном 
массиве числа. Второй — количество повторений числа, расположенного в первом массиве под тем же индексом.

Требования к оформлению :
Программа должна быть реализована на языке C и работать для произвольных наборов входных данных(в том числе и ошибочных), 
вводимых пользователем с клавиатуры.Должна быть выполнена грамотная декомпозиция на функции и файлы.
Помимо самой программы необходимо :
– разработать набор юнит - тестов, проверяющих корректную работу реализованных функций.
Обеспечить максимальное покрытие исходного кода тестами;
– оформить задачу в виде Merge Request отдельной ветки в master.
Внимание: в ветке master никакого кода быть не должно!
– развернуть CI, в рамках которого автоматизировать сборку проекта, прохождение юнит - тестов под valgrind,  
генерацию отчёта о покрытии кода тестами, линтера и статического анализатора исходного кода;
– после прохождения всех проверок необходимо отправить код на ревью своему преподавателю;
– ревью - процесс итерационный.До наступления дедлайна можно проходить несколько итераций, улучшая свою оценку.*/

#include <stdlib.h>
#include <stdio.h>

#define ERR_ALLOC (1)
#define ERR_NAN (2)
#define ERR_BIG_INPUT (3)
#define ERR_BIG_NUMBER (4)
#define ERR_ARR_EMPTY (5)
#define MAX_INT (999999)

#define MAX_INPUT_SIZE (200)

typedef struct {
	int * i_arr_ptr;
	int i_len;
	int ** o_arr_ptr;
	int o_len;
	int errflag;
} array_return;

array_return input( array_return );

array_return number_frequency( array_return );

array_return output( array_return );

int no_errors( array_return );

void free_all( array_return );

int main(int argc, char *argv[])
{
	//arr_ret is a common struct for returning array and error value
	array_return arr_ret = { NULL, 0, NULL, 0, 0 };
	
	arr_ret = input( arr_ret );
	if( !no_errors( arr_ret )) { return 0; }
	
	arr_ret = number_frequency(arr_ret);
	if( !no_errors( arr_ret )) { return 0; }
	
	arr_ret = output( arr_ret );
	if( !no_errors( arr_ret )) { return 0; }
	
	free_all( arr_ret );
	
	return 0;
}

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

array_return number_frequency( array_return this_struct )
{
	this_struct.o_arr_ptr = (int **)malloc( 2 * sizeof(int *) );
	if( !this_struct.o_arr_ptr ) { this_struct.errflag = ERR_ALLOC; return this_struct; }
	
	this_struct.o_arr_ptr[0] = (int *)malloc( this_struct.i_len * sizeof(int) );
	if(!this_struct.o_arr_ptr[0]) { this_struct.errflag = ERR_ALLOC; return this_struct; }
	
	this_struct.o_arr_ptr[1] = (int *)malloc( this_struct.i_len * sizeof(int) );
	if(!this_struct.o_arr_ptr[1]) { this_struct.errflag = ERR_ALLOC; return this_struct; }

	int flag_is_new = 1;
	int index_to_inc = 0;
	int cur_num;
	
	for (int i = 0; i < this_struct.i_len; i++)
	{
		cur_num = this_struct.i_arr_ptr[i];
		flag_is_new = 1;
		
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

array_return output( array_return output_struct)
{
	if( output_struct.o_len < 1 ) { output_struct.errflag = ERR_ARR_EMPTY; return output_struct; }
	for( int i = 0; i < output_struct.o_len; i++ )
		printf("%d - %d\n", output_struct.o_arr_ptr[0][i], output_struct.o_arr_ptr[1][i]);
};

int no_errors( array_return struct_to_check )
{
	if( struct_to_check.errflag == 0 )
	{
		return 1;
	}
	if( struct_to_check.errflag == ERR_NAN )
	{
		free_all( struct_to_check );
		printf("Ошибка! Вы ввели не число\n");
		return 0;
	}
	if( struct_to_check.errflag == ERR_BIG_NUMBER )
	{
		free_all( struct_to_check );
		printf("Ошибка! Вы ввели слишком большое число (>1000000) \n");
		return 0;
	}
	if( struct_to_check.errflag == ERR_ALLOC )
	{		
		free_all( struct_to_check );
		printf("Ошибка реаллокации\n");
		return 0;
	}
	if( struct_to_check.errflag == ERR_ARR_EMPTY )
	{
		free_all( struct_to_check );
		printf("Результирущий массив пуст\n");
		return 0;
	}
	if( struct_to_check.errflag == ERR_BIG_INPUT )
	{		
		free_all( struct_to_check );
		printf("Вводимый массив чисел слишком велик (>200 элементов)\n");
		return 0;
	}
};

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