#include <stdio.h>

int greatest(int a, int b, int c) {
    if (a >= b && a >= c) {
        return a;
    }
    if (b >= a && b >= c) {
        return b;
    }
    return c;  // remaining case
}

int main() {
    int x, y, z;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);

    int g = greatest(x, y, z);
    printf("Greatest = %d", g);

    return 0;
}

