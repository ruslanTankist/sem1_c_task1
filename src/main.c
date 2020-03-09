// Юзеев Руслан, АПО-12, Условие ИЗ№1:

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
#include <hw1/struct.h>
#include <hw1/io.h>
#include <hw1/err.h>
#include <hw1/numfreq.h>

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