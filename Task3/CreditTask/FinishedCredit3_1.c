#include <stdio.h>
#include <string.h>

//! Reduce the main function down to less than 50 lines of code

int question(int number){
    switch (number){
    case 1:
        printf("Welcome to the C brain scan\n");
        printf("I will ask you some questions...\n");
        printf("Select the best answer and type in the corresponding letter.\n");
        printf("1. What does the == operator do?\n");
        printf("(a) calculates an arithmetic solution.\n");
        printf("(b) assigns a value to a variable.\n");
        printf("(c) checks for equality\n(d) draws the '=' character\n");
        printf("Your answer: \n");
        break;
    case 2:
        printf("2. Which is NOT a C keyword?\n");
        printf("(a) when\n");
        printf("(b) const\n");
        printf("(c) unsigned\n(d) do\n");
        printf("Your answer: \n");
        break;
    case 3:
        printf("3. In function call, the actual parameters are separated by\n");
        printf("(a) semicolons\n");
        printf("(b) colons\n");
        printf("(c) commas\n(d) space\n");
        printf("Your answer: \n");
        break;
    case 4:
        printf("4. What is the keyword for a global variable?\n");
        printf("(a) global\n");
        printf("(b) namespace\n");
        printf("(c) external\n(d) there is no keyword. to be global the variable must be declared outside of main()\n");
        printf("Your answer: \n");
        break;
    case 5:
        printf("5. A function prototype always contains:\n");
        printf("(a) a void type\n");
        printf("(b) an integer parameter\n");
        printf("(c) a function name\n(d) a comma\n");
        printf("Your answer: \n");
        break;
    }
}

int scans(char answer[8]){
    do{
        scanf("%s", answer);
    } while (strcmp(answer, "a") != 0 && strcmp(answer, "b") != 0 && strcmp(answer, "c") != 0 && strcmp(answer, "d") != 0);
}
int counter(char correct[], char answer[],int current){
    if (strcmp(answer,correct) == 0){
    current += 1;
    printf("Correct \tYour score is now %d\n", current);
    return current;
    }
    else{
        printf("Wrong \tYour score is still %d\n", current);
        return current;
    }
}

void main(){
    int score = 0;
    char answer[8];
    question(1);
    scans(answer);
    score= counter("c",answer,score);
    question(2);
    scans(answer);
    score= counter("a",answer,score);
    question(3);
    scans(answer);
    score= counter("c",answer,score);
    question(4);
    scans(answer);
    score= counter("d",answer,score);
    question(5);
    scans(answer);
    score= counter("c",answer,score);
}