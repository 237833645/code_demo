#include <stdio.h>
#include "dynamic_lib.h"

int dynamic_lib_func(void)
{
	/* 这个函数内部写核心代码 */
	printf("dynamic_lib_func() call\n");
	return 0;
}