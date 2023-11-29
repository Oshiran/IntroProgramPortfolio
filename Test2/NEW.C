#include <stdio.h>
#include <string.h>

typedef struct membership
{
    char name[64];
    int age;
} Membership;

void dispmember(Membership member)
{
    printf("\nName: %s", member.name);
    printf("\nAge: %d \n", member.age);
}

Membership inputmember()
{
    Membership newMember;

    printf("Enter name: ");
    scanf("%s", newMember.name);

    printf("Enter age: ");
    scanf("%d", &newMember.age);

    return newMember;
}

void main()
{
    Membership members[10];
    int numMembers = 0;
    int choice;

    while (numMembers < 10)
    {

        members[numMembers] = inputmember();
        numMembers++;

        if (numMembers < 10)
        {
            printf("\nCreate another new membership? \n[1]Yes \n[2]No");
            scanf("%d", choice);

            if (choice == 2)
            {
                break;
            }
        }
        else
        {
            printf("Membership full.\n");
        }
    }

    for (int i = 0; i < numMembers; i++)
    {
        printf("\nMembership %d:\n", i + 1);
        dispmember(members[i]);
    }
}
