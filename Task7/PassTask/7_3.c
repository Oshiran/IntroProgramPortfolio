#include <stdio.h>
#include <stdlib.h>

typedef enum genre
{
    POP = 1,
    CLASSIC = 2,
    JAZZ = 3,
    ROCK = 4
} Genre;

typedef struct track
{
    char name[256];
    char location[256]; //filepath
} Track;

typedef struct album
{
    char title[256];
    char artist[256];
    Genre genre;
    int number_of_tracks;
    Track *tracks;
} Album;

Track read_track(FILE *fptr)
{
    Track track;
    fscanf(fptr, "%[^\n]\n", track.name);
    fscanf(fptr, "%[^\n]\n", track.location);
    return track;
}

Track *read_tracks(FILE *fptr, int number_of_tracks)
{
    Track* tracks = malloc(number_of_tracks * sizeof(Track));
    for(int i=0; i < number_of_tracks; i++)
    {
        tracks[i] = read_track(fptr);
    }   
    return tracks;
}

void print_track(Track track)
{
    printf("Track title is: %s\n", track.name);
    printf("Track location is: %s\n", track.location);
}

void print_tracks(Track *tracks, int number_of_tracks)
{
    for(int i = 0; i < number_of_tracks; i++){
        print_track(tracks[i]);
    }
}

Album read_album(FILE *fptr)
{
    Album new_album;

    fscanf(fptr, "%[^\n]\n",new_album.title);
    fscanf(fptr, "%[^\n]\n",new_album.artist);
    fscanf(fptr, "%d\n", &new_album.genre);
    fscanf(fptr, "%d\n", &new_album.number_of_tracks);

    new_album.tracks = read_tracks(fptr,new_album.number_of_tracks);
    
    return new_album;
}

// Takes a single album and prints it to the terminal along with all its tracks
void print_album(Album album)
{
    printf("Album title %s \n", album.title);
    printf("Album artist %s \n", album.artist);

    switch (album.genre)
    {
    case POP:
        printf("Genre is Pop\n");
        break;
    case CLASSIC:
        printf("Genre is Classic\n");
        break;
    case JAZZ:
        printf("Genre is Jazz\n");
        break;
    case ROCK:
        printf("Genre is Rock\n");
        break;
    }

    print_tracks(album.tracks,album.number_of_tracks);
}

void main()
{
    FILE *fptr;

    if ((fptr = fopen("album.txt", "r")) == NULL)
    {
        printf("Unable to open file.");
        return;
    }
    else
    {
        Album newAlbum = read_album(fptr);
        print_album(newAlbum);
        fclose(fptr);
    }
}
