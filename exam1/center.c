/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{
    // FILL THIS IN
    //    return NULL;
    int i;
    int len = strlen(s);
    int num = n-len;
    int beg = num/2;
    int end = num - beg;
    char a[n+1];
    char sent[] = s;

    printf("%i",beg);
    printf("%i",end);

    s = (char *)malloc(n+1 * sizeof(char));

    for (i=0;i<beg;i++){
        a[i]=fillchar;
    }

    strcat(a,sent);

    for(i=len+beg-1;i<n;i++) {
        a[i]=fillchar;
    }

    printf("%s",a);
    strcpy(s, a);

    // for (i=0;i<n;i++) {

    // }
    return s;
}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    return 0;
}
