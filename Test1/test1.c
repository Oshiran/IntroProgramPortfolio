#include <stdio.h>


char* mygrade(int score)
{
    // Return "Fail" if grade is less than 50
    if (score < 50) {
        return "Fail";
    }
    // Return "Pass" if grade is between 50 and less than 60
    else if (score < 60) {
        return "Pass";
    }
    // Return "Credit" if grade is between 60 and less than 70
    else if (score < 70) {
        return "Credit";
        }
    // Return "Distinction" if grade is between 70 and less than 80
    else if (score < 80) {
        return "Distinction";
    }
    // Return "High Distinction" if grade is greater than or equal to 80
    else {
        return "High Distinction";
    }
}

void main()
{
    int score;

    printf("Enter your score for this unit: ");
    scanf("%d", &score);

    // Check if the score is less than 0 or greater than 100
    if (score < 0 || score > 100) {
        printf("Invalid score. Please enter a score between 0 and 100.\n");
        return 1; // Exit with an error code
    } // Call the mygrade function to get the corresponding grade
    char* grade = mygrade(score);

    // Display the grade of the user
    printf("Your grade for this unit is: %s\n", grade);

    // Repeat the program if the score is less than 50
    while (score < 50) 
    {
        printf("You need to retake the unit. Enter your new score: ");
        scanf("%d", &score);
        grade = mygrade(score);
        printf("Your grade for this unit is: %s\n", grade);
    }
}