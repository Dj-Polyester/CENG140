//
// Created by yusufc on 23.04.2019.
//
#ifndef _EXAM_3_0_
#define _EXAM_3_0_

/****** THESE FUNCTIONS ARE ALREADY IMPLEMENTED ******/

/*
 *	returns number of characters in a string
 *	returns 0 if string is NULL
 */
int get_string_length(char *string);

/*
 *	returns the longest string length
 *	returns 0 if string array is NULL
 */
int get_longest_string_length(char **s, int n_string);

/*
 *  returns nothing
 *	prints combined strings one line for each.
 */
void print_combined_strings(char **s, int n_string);

/*
 *  returns whether given char is a letter
 */
int is_letter(char c);

/*
 *  returns the order of the letter in the alphabet
 *  if given char is not a letter, returns -1
 */
int letter_to_shift(char c);

/****** YOU NEED TO IMPLEMENT BELOW FUNCTIONS ******/
/*
 * if given c is a letter
 *      returns the shifted character with given shift
 * else
 *      returns c without shifting
 * important:   - if c is lowercase, shifted c must be also lowercase. Same for uppercase.
 *                      e.g. 'z'+2 is 'b', whereas 'Z'+2 is 'B'.
 *              - shift variable may be negative for shifting in reverse.
 *              - Be careful for overflows! c may need to be used as int inside the function
 *                to get rid of this problem.
 */
char shift_character(char c, int shift);

/*
 * gets message_to_ecnrypt and shift which is actually int*.
 * you can reach the value inside the shift by dereferencing it.
 * details of the algorithm can be found in the question.
 *
 * returns a new char* which contains encrypted message.
 * important: original message should NOT be changed.
 */
char *caesar_encrypt(char *message_to_encrypt, void *shift);

/*
 * gets message_to_ecnrypt and key_string which is actually char*.
 * you can reach the value inside the shift by dereferencing it.
 * details of the algorithm can be found in the question.
 *
 * returns a new char* which contains encrypted message.
 * important: original message should NOT be changed.
 */
char *polyalphabetic_encrypt(char *message_to_encrypt, void *key_string);

/*
 * gets char** messages which contains n_messages strings.
 * char* salt is used for padding.
 * details of the algorithm can be found in the question.
 *
 * returns a new char** which contains combined messages.
 * important: original messages should NOT be changed.
 */
char **combine_strings(char **messages, int n_messages, int grouping, char *salt);

/*
 * gets char** messages which contains n_messages strings.
 * grouping and salt is used for combining strings.
 * details of the algorithm can be found in the question.
 *
 * void* shift is string if cipher method is polyalphabetic,
 * otherwise int
 *
 * returns a new char** which contains encrypted combined messages.
 * important: original messages should NOT be changed.
 */
char **mycipher_encrypt(char **messages, int n_messages, int grouping, char *salt,
                        char *(*cipher_method)(char *, void *),  void* shift);

#endif
