#include <stdio.h>
#include <math.h>
int main ()
{
    //! Formula for interest is I=P(1+i)^n-P
    //! P for Pricinple (inital investment), i is the rate ( in %), n for years
    float principle, years, rate;
    printf("Please enter the principle amount:");
    scanf("%f",&principle);
    printf("Please enter the years:");
    scanf("%f", &years);
    printf("Please enter rate:");
    scanf("%f", &rate);
    rate= rate/100;

    float calc1=pow((1+rate),years);
    float calc2= (principle*calc1)-principle;
    printf("\nYour interest after %0.0f years at the rate %0.2f with the principle amount being %0.0f is %0.3f", years,rate,principle,calc2);
    return 0;
}