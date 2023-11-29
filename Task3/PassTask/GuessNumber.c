#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "input_functions.c"

int RNG (){
    srand(time(NULL));
    int RNG= rand();
    RNG=(rand()%100);
    RNG++;
    return RNG;
}

int check(int random, int guess){
    if (guess == random){
        printf("\nYou are correct");
        return 0;
    }else if (guess > random){
        printf("\nYour guess is greater");
        return 1;
    }else{
        printf("\nYour guess is lower");
        return 2;
    }
}
void main (){
    char ans[32];
    bool status=true;
    bool status2=true;
    while (status){
        int random=RNG();
        printf("%d",random);
        while (status2){
            int guess=read_integer("\nWhat is the number?  ");
            int ck=check(random,guess);
            if (ck == 0){
                status2=false;
            }
        }
        status=read_boolean("\nContinue?(Yes/No)  ");
        status2=true;
    }
}