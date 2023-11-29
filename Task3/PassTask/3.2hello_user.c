#include <stdio.h>
#include <time.h>
#include "input_functions.c"
#include "functions.h"
#define INCHES 0.393701 // This is a global constant

void main()
{
    char name[256];
    char family_name[256];
    int year_born;

    read_string("\nwhat is your name?",name);
    printf("Your name is %s !\n", name);

    read_string("\nWhat is your family name?",family_name);
    printf("Your family name is %s !\n", family_name);

    year_born= read_integer("\nWhat year were you born?");
    
    // Calculate age
    printf("\nSo you are %d years old\n",get_age_from_year_born(year_born));

    // Calculate height in inches
    float height_cm;
    printf("Enter your height in cms (i.e as a float) \n");
    scanf("%f", &height_cm);
    printf("Your height in inches is: %0.2f\n", height_cm * INCHES );
    printf("Finihsed\n");
}
