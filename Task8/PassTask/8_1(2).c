#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "input_functions.c"

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
    char location[256];
} Track;

typedef struct album
{
    char title[256];
    char artist[256];
    char cover[256];
    Genre genre; 
    int number_of_tracks;
    Track *tracks;
} Album;

Track read_track(FILE * fptr){
    Track track;

    fscanf(fptr, "%[^\n]\n", track.name); 
    fscanf(fptr, "%[^\n]\n", track.location);

    return track;
}

Track *read_tracks(FILE *fptr, int number_of_tracks){

    Track *tracks = malloc(number_of_tracks * sizeof(Track));

    for(int i = 0; i < number_of_tracks; i++)
    {
        tracks[i] = read_track(fptr);
    }   

    return tracks;
}


void print_track(Track track)
{
    printf("Track title is : %s\n", track.name);
    printf("Track location is : %s\n", track.location);
}

void print_tracks(Track *tracks, int number_of_tracks)
{
    for(int i = 0; i < number_of_tracks; i++)
    {
        print_track(tracks[i]);
    }
}


Album read_album(FILE *fptr)
{
    Album new_album;

    fscanf(fptr, "%[^\n]\n", new_album.title);
    fscanf(fptr, "%[^\n]\n", new_album.artist);
    fscanf(fptr, "%[^\n]\n", new_album.cover);
    fscanf(fptr, "%d\n", &new_album.genre); 
    fscanf(fptr, "%d\n", &new_album.number_of_tracks);

    new_album.tracks = read_tracks(fptr, new_album.number_of_tracks);

    return new_album;
}

void print_album(Album album)
{
    printf("Album title %s \n", album.title);
    printf("Album artist %s \n", album.artist);
    printf("Album cover %s \n", album.cover);

    switch (album.genre){
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
    
    print_tracks(album.tracks, album.number_of_tracks);
}

void main()
{
    char targetfile[256];
    FILE *fptr;
    int number_of_albums = 0 ;
    Album *albums;
    int album_num= -1;

    bool should_quit = false;

    while (should_quit == false)
    {
        int response = read_integer_in_range("\nOptions \n[1]Read in album \n[2]Display albums \n[3]Update an album \n[4]Save and Exit \nYour Choice: ", 1, 4);

        switch (response)
        {
        case 1:
            printf("\nRead in Albums");
            read_string("\nPlease enter the album file name: ",targetfile);

            if ((fptr = fopen(targetfile, "r")) == NULL)
            {
                printf("Unable to open file.");
            }
            else
            {
                fscanf(fptr,"%d\n", &number_of_albums);
                albums = malloc(number_of_albums * sizeof(Album));
                for (int i = 0; i < number_of_albums; i++)
                {
                    albums[i] = read_album(fptr);
                }
                printf("\nRead album successfully!");
            }
            break;
        case 2:
            printf("\nPrint Albums");
            for (int i = 0; i < number_of_albums; i++)
            {
                printf("\nAlbum number %d\n", i+1);
                print_album(albums[i]);
                printf("\n---------\n");
            }     
            break;
        case 3:
            printf("\nUpdate Albums\n");
            album_num = read_integer_in_range("\nEnter the album number: ", 1, number_of_albums);
            read_string("\nEnter the new album title: ",albums[album_num-1].title);
            printf("\n\n-------\n");
            print_album(albums[album_num-1]);
            printf("\n\n-------\n");
            break;
        case 4:
            printf("\nExit Program");
            fclose(fptr);
            if ((fptr = fopen(targetfile, "w")) != NULL)
            {
                fprintf(fptr, "%d\n", number_of_albums);

                for (int i = 0; i < number_of_albums; i++)
                {
                    fprintf(fptr, "%s\n", albums[i].title);
                    fprintf(fptr, "%s\n", albums[i].artist);
                    fprintf(fptr, "%s\n", albums[i].cover);
                    fprintf(fptr, "%d\n", albums[i].genre);
                    fprintf(fptr, "%d\n", albums[i].number_of_tracks);
                    for (int j = 0; j < albums[i].number_of_tracks; j++)
                    {
                        fprintf(fptr, "%s\n", albums[i].tracks[j].name);
                        fprintf(fptr, "%s\n", albums[i].tracks[j].location);
                    }
                    
                }
                printf("\nAny Changes made have been saved\n");

                for (int i = 0; i < number_of_albums; i++)
                {
                    free(albums[i].tracks);
                }
                free(albums);
            }
            
            should_quit=true;
            break;
        default:
            break;
        }
    }
    

    // if ((fptr = fopen("albums.txt", "r")) == NULL)
    // {
    //     printf("Unable to open file.");
    //     return;
    // }
    // else
    // {
    //     int number_of_albums = 0;
    //     fscanf(fptr,"%d\n",&number_of_albums);
    //     for (int i = 0; i < number_of_albums; i++)
    //     {
    //         Album newAlbum = read_album(fptr);
    //         print_album(newAlbum);
    //     }
    //     fclose(fptr);
    // }
}