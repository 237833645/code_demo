#include <stdio.h>
#include "static_lib.h"

int static_lib_func(void)
{
	/* 这个函数内部写核心代码 */
	printf("static_lib_func() call\n");
	return 0;
}