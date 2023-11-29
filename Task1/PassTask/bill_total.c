#include <stdio.h>

void main()
{
    int appetizer_price;
    int main_price;
    int dessert_price;
    float total_price;

    printf("Enter the appetizer price (in cents)\n");
    scanf("%d", &appetizer_price);

    printf("Enter the main price (in cents)\n");
    scanf("%d", &main_price);

    printf("Enter the dessert price (in cents)\n");
    scanf("%d", &dessert_price);

    total_price = appetizer_price+main_price+dessert_price ;
    total_price =total_price/100;
    printf("$%0.2f",total_price);
}
