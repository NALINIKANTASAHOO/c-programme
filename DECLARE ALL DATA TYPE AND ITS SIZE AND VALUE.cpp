#include <stdio.h>

int main() {
    int a = 10;
    float b = 5.5;
    char c = 'A';

    int *p1 = &a;
    float *p2 = &b;
    char *p3 = &c;

    printf("INT: value=%d, address=%p, size=%zu bytes\n", a, &a, sizeof(a));
    printf("FLOAT: value=%.2f, address=%p, size=%zu bytes\n", b, &b, sizeof(b));
    printf("CHAR: value=%c, address=%p, size=%zu bytes\n", c, &c, sizeof(c));

    printf("Pointer p1 value (address stored) = %p, size = %zu bytes\n", p1, sizeof(p1));
    printf("Pointer p2 value (address stored) = %p, size = %zu bytes\n", p2, sizeof(p2));
    printf("Pointer p3 value (address stored) = %p, size = %zu bytes\n", p3, sizeof(p3));

    return 0;
}

