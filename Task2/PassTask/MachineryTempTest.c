#include <stdio.h>
#include <string.h>

int main ()
{
    const int LOW =38;
    int temp, status=1;
    char backupstatustrue[]="Yes", backupstatus[10];
 

    while (status<=1)
    {
        printf("\nPlease enter the current temperature: ");
        scanf("%d", &temp);
        if (temp<LOW)
        {
            temp=LOW;
            printf("\n%d", temp);
        }
        printf("Is backup power on? (Yes/No): ");
        scanf("%s", backupstatus);
        if (temp<50)
        {
            printf("\nNormal mode of operation");
        }
        else
        {
            float comp1=strcmp(backupstatus,backupstatustrue);
            if (temp <= 80 || comp1 == 0)
            {
                printf("\nTurn on circulating fan");
            }
            else
            {
                printf("\nTurn off equipment");
                printf("\nTemp %d", LOW);
                status++;
            }
        }
    }
}