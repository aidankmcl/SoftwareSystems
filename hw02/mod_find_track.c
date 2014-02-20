/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

Modified by Aidan McLaughlin

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
// Prints track number and title.
void find_track_regex(char search_for) {
    // TODO: fill this in
    int i;
    int empty = 0;

    int rv;
    regex_t exp; //Our compiled expression

    rv = regcomp(&exp, search_for, REG_EXTENDED);
    if (rv != 0) {
        printf("regcomp failed with %d\n", rv);
    }

    regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
    //Compare the string to the expression
    //regexec() returns 0 on match, otherwise REG_NOMATCH
    for (i=0;i<NUM_TRACKS;i++) {
        if (regexec(pexp, tracks[i], MAX_MATCHES, matches, 0) == 0) {
            printf("Track %i : \"%s\" \n",i, tracks[i]);
        } else {
            empty++;
        }

        // Taking out else statement because we don't care to see that.
        // However, outside the for loop is some edge case handling for
        // no matches.

        // } else {
        //     printf("\"%s\" does not match\n", tracks[i]);
        // }
    }
    // Edge case mentioned a moment ago
    if (empty == NUM_TRACKS) {
        puts("Pattern matches none of our tracks");
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');  // Important for functional input into regex
    if (ptr) {                    // pattern.
	*ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    printf("Search with what pattern: ");
    fgets(search_for,80,stdin);
    rstrip(search_for);


    /* take input from the user and search */
    find_track_regex(&search_for);

    regfree(&exp);
    return 0;
}
