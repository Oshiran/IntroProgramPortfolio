#include <stdio.h>
#include <stdbool.h>

const char* mygrade(int grade)
{
    if (grade < 50) 
    {
        return "Fail";
    } else if (grade >= 50 && grade < 60) 
    {
        return "Pass";
    } else if (grade >= 60 && grade < 70) 
    {
        return "Credit";
    } else if (grade >= 70 && grade < 80) 
    {
        return "Distinction";
    } else if (grade >= 80 && grade <= 100) 
    {
        return "High Distinction";
    }
    else 
    {
        return "Invalid score";
    }
    
}


void main () 
{
    int score;
    bool status=true;
    while (status)
    {
        printf("\nEnter you score for this unit: ");
        scanf("%d", &score);
        if (score < 50)
        {
            printf("\nYour grade for this unit is: Fail");
        }
        else
        {
            printf("\nYour grade for this unit is, %s", mygrade(score));
            status=false;
        }
    }
    
}
