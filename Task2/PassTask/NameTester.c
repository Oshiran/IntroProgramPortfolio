#include <stdio.h>
#include <string.h>

int main ()
{
    char name0[255], name1[]= "Alison", name2[]="Carmen";
    printf("please enter your name:");
    scanf("%s", &name0);
    float comparison1= strcmp(name0,name1), comparison2= strcmp(name0,name2);
    if (comparison1 == 0 || comparison2 == 0)
    {
        printf("\n%s is an awesome name", name0);
    }
    else
    {
        printf("\n%s is a", name0);
        int i;
        for (i = 0; i < 60; i++)
        {
            printf(" silly");
        }
        printf("\nname");
    }
    return 0; 
}