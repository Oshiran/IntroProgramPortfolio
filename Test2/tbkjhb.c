#include <stdio.h>
#include <string.h>

typedef struct membership
{
    char name[64];
    int age;
} Membership;

// Defining Display member
void dispmember(Membership members[], int count)
{
    printf("Members:\n");
    for (int i = 0; i < count; i++)
    {
        printf("Name: %s\n", members[i].name);
        printf("Age: %d\n", members[i].age);
        printf("-----------------\n");
    }
}

// Defining Input member
Membership inputmember()
{
    Membership member;
    printf("Enter name: ");
    scanf(" %[^\n]", member.name);
    printf("Enter age: ");
    scanf("%d", &member.age);
    getchar(); 
    return member;
}

// Defining main function
int main()
{
    Membership members[10];
    int count = 0;

    char choice[4];
    do
    {
        if (count >= 10)
        {
            printf("Membership full\n");
            break;
        }

        members[count] = inputmember();
        count++;

        printf("Create another new membership? (Yes/No) ");
        scanf(" %[^\n]", choice);
        getchar(); 
    } while (strcmp(choice, "Yes") == 0);

    dispmember(members, count);
}