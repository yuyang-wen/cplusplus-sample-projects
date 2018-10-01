//
// This is a program written to maintain a personal music library,
// using a linked list to hold the songs in the library.
//
// Author: Yuyang Wen
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MAX_LENGTH 1024
#define MAX_LIBRARY_SIZE 100

// A node in the linked list
typedef struct song {
    char songName[MAX_LENGTH] ;
    char artist[MAX_LENGTH] ;
} Song ;

// Declarations of support functions
void getStringFromUserInput(char s[], int arraySize);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);
void printMusicLibrary(Song * Library, int inputNumber);
void cocktailSort(Song * Library, int inputNumber);


int main(void) {

    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), S (sort by artist), P (print), Q (quit).\n");
    
    char response;
    char input[MAX_LENGTH + 1], song[MAX_LENGTH + 1], artist[MAX_LENGTH + 1];
    Song Library[MAX_LIBRARY_SIZE] ;
    int inputNumber = -1;

    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH+1);
        
        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);
        
        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            inputNumber++;
            printf("Song name: ");
            getStringFromUserInput(song, MAX_LENGTH+1);
            printf("Artist: ");
            getStringFromUserInput(artist, MAX_LENGTH+1);
            
            strcpy(Library[inputNumber].artist, artist);
            strcpy(Library[inputNumber].songName, song);
            
        }
        else if (response == 'S') {
            // Search for a song by its name.
            cocktailSort(Library, inputNumber);
            printMusicLibrary(Library, inputNumber);
        }
        else if (response == 'P') {
            // Print the music library.
            printMusicLibrary(Library, inputNumber);
        }
        else if (response == 'Q') {
            ; // do nothing
        }
        else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');   
    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void getStringFromUserInput(char s[], int maxStrLength) {
    int i = 0;
    char c;
    
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    
    s[i] = '\0';
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void)
{
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void)
{
    printf("\nMy Personal Music Library: \n");
}

void printMusicLibrary(Song * Library, int inputNumber)
{
    if (inputNumber == -1) //empty condition
        printMusicLibraryEmpty();
    else {
        printMusicLibraryTitle();//printing the title
        //the following for loop prints the array terms one by one
        for(int i = 0; i <= inputNumber; i++){
            printf("\n%s\n",Library[i].songName);
            printf("%s\n",Library[i].artist);
        }
    }
}

void cocktailSort(Song * Library, int inputNumber)
{
    Song temp;
    int bot = 0,top = inputNumber;
    bool sort = false;
    
    // The following while loop searches the array alternating between top to bottom and bottom to top
    while (bot < inputNumber / 2 && top > inputNumber / 2 && !sort){
        sort = true;
        // Searching from bottom to top, swap terms if term i+1 is "smaller" than term i
        for (int i = bot; i < top; i++){
            // Check and swapping by artist
            if (strcmp(Library[i].artist, Library[i+1].artist)>0){
                strcpy(temp.artist, Library[i+1].artist);
                strcpy(temp.songName, Library[i+1].songName);
                strcpy(Library[i+1].artist, Library[i].artist);
                strcpy(Library[i+1].songName, Library[i].songName);
                strcpy(Library[i].artist, temp.artist);
                strcpy(Library[i].songName, temp.songName);
                sort = false;
            }
            // Check and swapping by song name if artist is the same
            else if (strcmp(Library[i].artist, Library[i+1].artist) == 0 && strcmp(Library[i].songName, Library[i+1].songName) > 0){
                strcpy(temp.songName, Library[i+1].songName);
                strcpy(Library[i+1].songName, Library[i].songName);
                strcpy(Library[i].songName, temp.songName);
                sort = false;
            }
        }
        top--;
        // Searching from top to bottom, swap terms if term j-1 is "bigger" than term j
        for (int j = top; j > bot; j--){
            // Check and swapping by artist
            if (strcmp(Library[j].artist, Library[j-1].artist)<0){
                strcpy(temp.artist, Library[j].artist);
                strcpy(temp.songName, Library[j].songName);
                strcpy(Library[j].artist, Library[j-1].artist);
                strcpy(Library[j].songName, Library[j-1].songName);
                strcpy(Library[j-1].artist, temp.artist);
                strcpy(Library[j-1].songName, temp.songName);
                sort = false;
            }
            // Check and swapping by song name if artist is the same
            else if (strcmp(Library[j].artist, Library[j-1].artist) == 0 && strcmp(Library[j].songName, Library[j-1].songName) < 0){
                strcpy(temp.songName, Library[j].songName);
                strcpy(Library[j].songName, Library[j-1].songName);
                strcpy(Library[j-1].songName, temp.songName);
                sort = false;
            }

        }
        bot++;
    }
}
