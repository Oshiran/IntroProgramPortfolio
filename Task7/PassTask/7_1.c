#include <stdio.h>
#include "input_functions.c"

typedef enum genre
{
    POP = 1,
    CLASSIC = 2,
    JAZZ = 3,
    ROCK = 4
} Genre;

typedef struct album
{
    char title[256];
    char artist[256];
    Genre genre;
} Album;

Album read_album()
{
    Album new_album;
    read_string("\nEnter the title: ",new_album.title);
    read_string("\nEnter the artist: ",new_album.artist);
    new_album.genre = read_integer_in_range("\nEnter the genre (Pop = 1, Classic = 2, Jazz = 3, Rock = 4)",1,4);
    return new_album;
}

void print_album(Album album)
{
    printf("Album information is: \n");
    printf("The title is %s \n", album.title);
    printf("The title is %s \n", album.artist);

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
}

void main()
{
    Album album = read_album();
    print_album(album);
}