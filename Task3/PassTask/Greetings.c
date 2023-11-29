#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int messagesstart (int duration)
{
    if (duration == 1 || duration ==0)
    {
        printf("\nDear valued customer:\n");
        printf("We would like to share our genuine appreciation for having you as our exclusive club member.\n");
        printf("********************************************************************************************\n");
    }
    else
    {
        printf("\nDear valued customer:\n");
        printf("We truely value your continuing support.\n");
        printf("********************************************************************************************\n");
    }
}

void messagesend ()
{
    printf("Please feel free to call our customer care line : 1-800-1234567 for more information.\n");
    printf("Thank you for being a wonderful and supportive customer, we look forward to serving you a again soon.\n\n");
}

int discount (int duration)
{
    switch (duration)
    {
    case 0:
        printf("We are offering you 30%% one off discount during your next visit to our club!\n");
        break;
    case 1:
        printf("We are offering you 20%% one off discount during your next visit to our club!\n");
        break;
    case 2:
        printf("We are offering you 10%% one off discount during your next visit to our club!\n");
        break;
    }
}

void main()
{
    bool repeat = true;

    do
    {
        int duration;
        printf("\nMembership Duration (0.First Month, 1.First Year, 2.Two Years or more):\n");
        scanf("%d", &duration);

        if (duration == 0)
        {
            messagesstart(duration);
            printf("Congratulation for completing your first month journey as our club member!\n");
            printf("To help you explore other services and facilities provides by our club...\n");
            discount(duration);
            messagesend();
        }
        else if (duration == 1)
        {
            messagesstart(duration);
            printf("Congratulation for your first anniversary as our club member!\n");
            printf("value our relationship and look forward to the opportunity to continue serving you.\n");
            discount(duration);
            messagesend();
            
        }
        else
        {
            messagesstart(duration);
            printf("We look forward to continue serving you for many more wonder years to comes.\n");
            printf("To celeberate your anniversary as our loyal club member...\n");
            discount(duration);
            messagesend();
        }

        printf("Continue with next message?(Yes/No)\n");
        char answer[32];
        scanf("%s", answer);

        int cmp= strcmp(answer,"No");
        if (cmp == 0 )
        {
            repeat = false;
        }
    } while (repeat);
}