/**
 Libre Wireless Technologies
 **/

//Dependencies
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "str.h"


/**
 * @brief Duplicate a string
 * @param[in] s Pointer to a constant NULL-terminated character string
 * @return Address of the string that was copied, or NULL if the string cannot be copied
 **/

char_t *strDuplicate(const char_t *s)
{
    uint_t n;
    char_t *p;

    //Calculate the length occupied by the input string
    n = strlen(s) + 1;

    //Allocate memory to hold the new string
    p = osAllocMem(n);
    //Failed to allocate memory?
    if(!p)
        return NULL;

    //Make a copy of the input string
    memcpy(p, s, n);

    //Return a pointer to the newly created string
    return p;
}


/**
 * @brief Removes all leading and trailing whitespace from a string
 * @param[in] s The string that will be trimmed
 * @return String with whitespace stripped from the beginning and end
 **/

char_t *strTrimWhitespace(char_t *s)
{
    char_t *end;
    char_t *result;

    //Trim whitespace from the beginning
    while(isspace((uint8_t) *s)) s++;
    //Save the current position
    result = s;

    //Search for the first whitespace to remove
    //at the end of the string
    for(end = NULL; *s != '\0'; s++)
    {
        if(!isspace((uint8_t) *s))
            end = NULL;
        else if(!end)
            end = s;
    }

    //Trim whitespace from the end
    if(end) *end = '\0';

    //Return the string with leading and
    //trailing whitespace omitted
    return result;
}


/**
 * @brief Removes all trailing whitespace from a string
 * @param[in,out] s Pointer to a NULL-terminated character string
 **/

void strRemoveTrailingSpace(char_t *s)
{
    char_t *end;

    //Search for the first whitespace to remove
    //at the end of the string
    for(end = NULL; *s != '\0'; s++)
    {
        if(!isspace((uint8_t) *s))
            end = NULL;
        else if(!end)
            end = s;
    }

    //Trim whitespace from the end
    if(end) *end = '\0';
}


/**
 * @brief Replace all occurrences of the specified character
 * @param[in,out] s Pointer to a NULL-terminated character string
 * @param[in] oldChar The character to be replaced
 * @param[in] newChar The character that will replace all occurrences of oldChar
 **/

void strReplaceChar(char_t *s, char_t oldChar, char_t newChar)
{
    //Parse the specified string
    while(*s != '\0')
    {
        //Remplace all occurrences of the specified character
        if(*s == oldChar)
            *s = newChar;
    }
}

