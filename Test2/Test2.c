#include <stdio.h>
#include <string.h>

typedef struct membership{
    char name[64];
    int age;
} Membership;

void dispmember(Membership member){
    printf("\nName: %s", member.name);
    printf("\nAge: %d \n", member.age);
}

Membership inputmember(){
    Membership newMember;

    printf("\nEnter name: ");
    scanf("%s", newMember.name);

    printf("\nEnter age: ");
    scanf("%d", &newMember.age);

    return newMember;
}

void main(){
    Membership members[10];
    int numMembers = 0;
    char choice[3];

    while (numMembers < 10){
        members[numMembers] = inputmember();
        numMembers++;
        if (numMembers < 10){
            printf("\nCreate another new membership? (Yes/No): ");
            scanf("%s", choice);
            if (strcmp(choice, "No") == 0){
                break;
            }
        }
        else{
            printf("\nMembership full.\n");
        }
    }
    for (int i = 0; i < numMembers; i++){
        printf("\nMembership %d:", i+1);
        dispmember(members[i]);
    }
}
