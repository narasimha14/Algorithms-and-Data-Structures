/**
        strfunc.h
        Purpose: Contains all the necessary helper APIs required to play around with char pointers or an array of chars
        
        @author Narasimha Murthy
        @version 1.0 2/19/2015
*/


#include <stdio.h>
#include <stdlib.h>

/* A function to concatenate two char arrays */
char * concatenation(char *first, int len1, char *second, int len2)
{
	char * toReturn = (char *)malloc((len1+len2)*sizeof(char));
	int i = -1;
	int j = -1;
	while(++i < len1)
		toReturn [i] = first[i];
	while(++j < len2)
		toReturn[len1 + j] = second[j];

	return toReturn;
}

/* A function to suffix a char to a char array */
char * suffix(char *first, int len1, char second)
{
        char * toReturn = (char *)malloc((len1+1)*sizeof(char));
        int i = -1;
        while(++i < len1)
                toReturn [i] = first[i];

        toReturn[len1] = second;
        return toReturn;
}

/* A function that prefixes a char to a char array */
char * prefix(char *first, int len1, char second)
{
        char * toReturn = (char *)malloc((len1+1)*sizeof(char));
	toReturn[0] = second;
        int i = -1;
        while(++i < len1)
                toReturn [i+1] = first[i];

        return toReturn;
}

/* A function similar to strcpy that copies one char array to another */
char * copystr(char * char1, int len)
{
	char *toReturn = (char *)malloc((len)*sizeof(char));
	int i = -1;
	while(++i < len)
		toReturn[i] = char1 [i];

	return toReturn;
}

/* A function to print the char array*/
void printString(char *str, int len)
{
	int i = -1;
	while(++i < len)
		printf("%c", str[i]);
}

/* A function that compares two char arrays and return 0 if they match. 1 otherwise */
int compareString(char *str1, int len1, char *str2, int len2)
{
	if(len1 != len2)
		return 1;
	int i = -1;
	while(++i < len1)
	{
		if(str1[i] != str2[i])
			return 1;
	}
	return 0;
}

/* A function that returns 0 if str1 starts with str2. Returns 1 otherwise */
int startsWith(char *str1, int len1, char *str2, int len2)
{
	if(len2 > len1)
		return 1;
	int i = -1;
	while(++i < len2)
	{
		if(str1[i] != str2[i])
			return 1;
	}
	return 0;
}

/* A function that prints a char in its binary form */
void print_bin_char(unsigned char ch)
{
        int i = -1;
        while(++i < 8)
        {
                printf("%d", (ch & (1 << (7-i))) >> (7-i) );
        }
        printf("\n");
}

/* A function that prints an integer in its binary form */
void printbinint(int i)
{
        char *output;
        output = (char *)malloc(8 * sizeof(char));
        int len = 0;
        while(1)
        {
                output[len] = i%2;
                ++len;
                i /= 2;
                if(i < 2)
                {
                        output[len] = i;
                        ++len;
                        break;
                }
        }
        while(--len >= 0)
                printf("%d", output[len]);
        printf("\n");
        free(output);
}

	
