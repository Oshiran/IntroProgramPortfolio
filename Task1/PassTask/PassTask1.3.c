#include <stdio.h>
int main()
{
    int appetizer_price, main_price, dessert_price;
    printf("Price of appetizer: ");
    scanf("%d", &appetizer_price);
    printf("Price of main: ");
    scanf("%d", &main_price);    
    printf("Price of dessert: ");
    scanf("%d", &dessert_price);
    float total_price=appetizer_price+main_price+dessert_price;
    total_price= total_price/100; //? Turning cents into dollars
    printf("\nValues entered are as follows: %d, %d, %d, and your total is $%0.2f", appetizer_price,main_price,dessert_price,total_price);
    return 0;
}