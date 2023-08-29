#define internal static

#ifndef BASE
#define BASE 10
#endif

internal void uintToStr(unsigned int value, char *out)
{
    char *ptr = out;
    while(value){
        unsigned int digit = value % BASE;
        value = value / BASE;

        *ptr++ = digit + '0';
    }

    *ptr-- = '\0';

    while(out < ptr) {
        char temp = *ptr;
        *ptr-- = *out;
        *out++ = temp;
    }
}

void foo(int n, float f, char *b)
{
    (void)f;
    uintToStr(n, b);
}
