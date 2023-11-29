#include <stdio.h>
#include <stdbool.h>

const char* mymarks(int marks)
{
    if (marks < 50){
        return "Fail";
    } else if (marks >=50 && marks <60){
        return "Pass";
    } else if (marks >=60 && marks <70){
        return "Credit";
    } else if (marks >=70 && marks <80){
        return "Distinction";
    } else if (marks >=80){
        return "High Distinction";
    }
    else {
        return "Invalid marks entered";
    }
}

void main () 
{
    int score;
    bool isrunning=true;
    do
    {
        printf("Enter marks for this unit:  \n");
        scanf("%d", &score);
        if (score<50){
            printf("Your final grade for this unit is: Fail\n");
        }
        else{
            printf("Your final grade for this unit is, %s \n", mymarks(score));
            isrunning=false;
        }
    } while (isrunning);
}
