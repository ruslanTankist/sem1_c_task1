#ifndef _FUNCTIONALITY_H_
#define _FUNCTIONALITY_H_

#define ERR_ALLOC (1)
#define ERR_NAN (2)
#define ERR_BIG_INPUT (3)
#define ERR_BIG_NUMBER (4)
#define ERR_ARR_EMPTY (5)
#define ERR_WRONG_AMOUNT (6)

#define MAX_INT (999999)

int no_errors( array_return );

array_return input( array_return );

array_return output( array_return );

void free_all( array_return );

array_return number_frequency( array_return );

#endif