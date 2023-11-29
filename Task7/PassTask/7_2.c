#include <stdio.h>
#include <stdlib.h>  // malloc() for dynamic array

typedef struct track
{
    char name[256];
    char location[256]; //filepath
} Track;

Track read_track(FILE * fptr){
    Track track;
    fscanf(fptr, "%[^\n]\n", track.name);
    fscanf(fptr, "%[^\n]\n", track.location);
    return track;
}

Track* read_tracks(FILE *fptr, int number_of_tracks){
    Track* tracks = malloc(number_of_tracks * sizeof(Track));
    for(int i=0; i < number_of_tracks; i++)
    {
        tracks[i] = read_track(fptr);
    }   
    return tracks;
}

void print_track (Track track){
    printf("Track title is: %s\n", track.name);
    printf("Track location is: %s\n", track.location);
}

void print_tracks (Track *tracks, int number_of_tracks){
    for(int i = 0; i < number_of_tracks; i++){
        print_track(tracks[i]);
    }
}

int read_number_of_tracks(FILE *fptr){
    int track_num;
    fscanf(fptr, "%d\n", &track_num);
    return track_num;
}
void main()
{
    FILE *fptr;

    if ((fptr = fopen("input.txt", "r")) == NULL)
    {
        printf("Unable to open file.");
        return;
    }else{
        int number_of_tracks = read_number_of_tracks(fptr);
        Track* tracks = read_tracks(fptr, number_of_tracks);
        print_tracks(tracks, number_of_tracks);
        free(tracks);
        fclose(fptr);
    }
}