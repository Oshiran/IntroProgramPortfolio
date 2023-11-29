#include <stdio.h>
#include <string.h>
int main ()
{
    int year, loopstatus=0;
    while (loopstatus ==0)
    {
    printf("\nPlease enter a year:");
    scanf("%i", &year);
    int calc1=year%4,calc2=year%100,calc3=year%400;
    if (calc1 == 0 && (calc2 !=0 || calc3 ==0 ))
    {
        printf("\nThe number entered is a leap year");
    }
    else
    {
        printf("\nThe number entered is NOT a leap year");
    }
    char status[255],status_true[]="Yes";
    printf("\nRepeat for another value? (Yes/No):");
    scanf("%s", &status);
    int comparison= strcmp(status,status_true);
    if (comparison != 0)
    {
        loopstatus++;
    }
    }
    return 0;
}