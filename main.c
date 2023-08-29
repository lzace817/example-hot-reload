#include <stdio.h>
#include "target.h"

int main()
{
    char buffer[4*1024];
    foo(17, 0.123, buffer);
    printf("%s\n", buffer);
    return 0;
}