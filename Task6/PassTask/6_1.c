#include <stdio.h>
#include <limits.h> //! Provides constant of the min/max of data type
#include "input_functions.c"

void display(int *arr)
{
    printf("\nArray values are:");
    for (int i = 0; i < 10; i++)
    {
        printf("\n%d", arr[i]);
    }
    
}

void main ()
{
    int i,array1 [10],startval=5;

    for (i = 0; i < 10; i++)
    {
        array1 [i] = startval;
        startval--;
        if (startval==0)
        {
            startval--;
        }
    }
    display(array1);
    int index=read_integer("\nWhat index do you want to edit? ");
    printf("\nThe chosen index value is  %d", index);
    int addvalue=read_integer("\nWhat is the new value? ");
    printf("\n%d",addvalue);
    array1[index]=addvalue;
    display(array1);
    int psum=0;
    int max=INT_MIN;

    for (int j = 0; j < 10; j++)
    {
        if (array1[j]>0)
        {
            psum+=1;
        }
        if (array1[j]>max)
        {
            max= array1[j];
        }      
    }
    printf("\nPositive count is %d, and max is %d",psum,max);
    

}