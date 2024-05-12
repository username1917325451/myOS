#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "assert.h"

int32_t std_min(int32_t cnt, int32_t ptr_num, ...)
{
    assert(cnt > 0);

    va_list args;
    int32_t retval;
    va_start(args, ptr_num);
    int32_t ans = ptr_num;
    while(--cnt > 0)
    {
        int32_t arg_int = va_arg(args, int);
        // printf("min :: %d\n", arg_int);
        ans = ans < arg_int ? ans : arg_int;
    }
    va_end(args);
    return ans;
}

int32_t std_max(int32_t cnt, int32_t ptr_num, ...)
{
    assert(cnt > 0);
    va_list args;
    int32_t retval;
    va_start(args, ptr_num);
    int32_t ans = ptr_num;
    while(--cnt > 0)
    {
        int32_t arg_int = va_arg(args, int);
        ans = ans > arg_int ? ans : arg_int;
    }
    va_end(args);
    return ans;
}

int32_t std_abs(int32_t num)
{
    return num > 0 ? num : -num;
}