#include <stdio.h>

int main() {
    int next, terms, a = 0, b = 1;
    printf("\nPlease enter the number of terms: ");
    scanf("%d", &terms);
    printf("\nAmong the first %d terms of Fibonacci series that are also prime numbers:", terms);
    for (int i = 0; i < terms; ++i)
     {
        if (a > 1) {
            int prime = 1; 
            for (int j = 2; j * j <= a; ++j) 
            {
                if (a % j == 0) {
                    prime = 0; 
                    break;
                }
            }
            if (prime) 
            {
                printf("\n%d ", a);
            }
        }
        next = a + b;
        a = b;
        b = next;
    }
    return 0;
}
