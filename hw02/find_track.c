/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5
#define MAX_MATCHES 1

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};


// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
	if (strstr(tracks[i], search_for)) {
	    printf("Track %i: '%s'\n", i, tracks[i]);
	}
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
                    //char pattern[]
void find_track_regex(regex_t *pexp) {
    // TODO: fill this in
    int i;
    regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
    //Compare the string to the expression
    //regexec() returns 0 on match, otherwise REG_NOMATCH
    for (i=0;i<NUM_TRACKS;i++) {
        if (regexec(pexp, tracks[i], MAX_MATCHES, matches, 0) == 0) {
            printf("Track \"%i\" : \"%s\" \n",i, tracks[i]);
        }
        // } else {
        //     printf("\"%s\" does not match\n", tracks[i]);
        // }
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];
    int rv;
    regex_t exp; //Our compiled expression

    printf("Search with what pattern: ");
    fgets(search_for,80,stdin);
    rstrip(search_for);

    rv = regcomp(&exp, search_for, REG_EXTENDED);
    if (rv != 0) {
        printf("regcomp failed with %d\n", rv);
    }

    /* take input from the user and search */
    find_track_regex(&exp);

    regfree(&exp);
    return 0;
}
