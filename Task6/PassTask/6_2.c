#include <stdio.h>
#include <stdlib.h>
#include "input_functions.c"

#define PLAYERS 4

void input(int** array, int number_of_teams, int number_of_players){
    for (int i = 0; i < number_of_teams; i++)
    {
        for (int p = 0; p < number_of_players; p++)
        {
            printf("\nFor Team %d, Player %d", i,p);
            array[i][p] = read_integer("\nHe/She has a score of:");
        }
        
    }
    
}

void disp_array(int ** array,int number_of_teams, int number_of_players){
    for (int i = 0; i < number_of_teams; i++)
    {
        printf("\nTeam %d: ",i);
        for (int j = 0; j < number_of_players; j++)
        {
            printf("%d, ", array[i][j]);
        }
        
    }
    
}

int teamscore(int * array, int number_players){
    int score=0;
    for (int i = 0; i < number_players; i++)
    {
        score += array[i];
        
    }
    return score;
}

int** create2DArray(int teams, int players){
    int **temp;
    temp =malloc(teams * sizeof(int *));

    for (int i = 0; i < teams; i++)
    {
        temp[i] = malloc(players * sizeof(int));
        //each player score stroed as int
    }
    

    return temp;
}

void free2DArray(int** array, int teams){
    for(int i = 0 ; i < teams; i++){
        free(array[i]);
    }

    free(array);
}

void main(){
    //  prompt user to enter total number of teams
    int number_of_teams = read_integer("Number of teams:");

    // Call "create2DArray" array of teams and players
    int ** teams = create2DArray(number_of_teams, PLAYERS);

    // Call "input" to populate team score
    input(teams,number_of_teams,PLAYERS);
    
    // Call "disp_array" to display team score
    disp_array(teams,number_of_teams,PLAYERS);

    // Print sum of team score her
    for (int i = 0; i < number_of_teams; i++)
    {
        int team_Score= teamscore(teams[i],PLAYERS);
        printf("\nTeam %d has a score of %d", i, team_Score);
    }

    free2DArray(teams, number_of_teams);
}