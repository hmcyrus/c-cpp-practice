#include <stdio.h>

#define SQUARE(x) ((x) * (x))

int square(int x) {
    return x * x;
}

int main() {
    printf("Hello, World!\n");

    int x = 2;

    printf("x = %d \n", x);
    int result = SQUARE(x++);

    printf("x = %d, result using macro = %d \n", x, result);

    x = 2;	
    printf("x = %d \n", x);
    result = square(x++);
    printf("x = %d, result using function = %d \n", x, result);

    return 0;

}



