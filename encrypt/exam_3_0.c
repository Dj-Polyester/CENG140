//
// Created by yusufc on 23.04.2019.
//

#include "exam_3_0.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
	returns number of characters in a string
	returns 0 if string is NULL
*/
int get_string_length(char *string) {
    int i = 0;
    if (string != NULL) {
        while (string[i] != '\0') i++;
    }
    return i;
}

/*
	returns the longest string length
	returns 0 if string array is NULL
*/
int get_longest_string_length(char **s, int n_string) {
    int maxLength = 0, tempLength = 0;
    int i;

    if (s == NULL) {
        return 0;
    }

    for (i = 0; i < n_string; i++) {
        if (s[i] != NULL) {
            tempLength = get_string_length(s[i]);
            if (tempLength > maxLength) {
                maxLength = tempLength;
            }
        }
    }
    return maxLength;
}

/*
 *  returns nothing
 *	prints combined strings one line for each.
 */
void print_combined_strings(char **s, int n_string) {
    int i;
    for (i = 0; i < n_string; i++) {
        if (s[i] != NULL) {
            printf("%s\n", s[i]);
        }
    }
}


/*
 *  returns whether given char is a letter
 */
int is_letter(char c) {
    return (c < 91 && c > 64) || (c < 123 && c > 96);
}

/*
 *  returns the order of the letter in the alphabet
 *  if given char is not a letter, returns -1
 */
int letter_to_shift(char c) {
    if (c < 91 && c > 64) {
        return c - 64;
    } else if (c < 123 && c > 96) {
        return c - 96;
    }

    return -1;
}

/* DON'T TOUCH THE CODE ABOVE, INCLUDING THIS LINE. YOUR IMPLEMENTATIONS MAY START BELOW THIS LINE. */




