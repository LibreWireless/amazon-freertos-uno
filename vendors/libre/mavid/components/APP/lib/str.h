/**
Libre Wireless Technologies
 **/

#ifndef _STR_H
#define _STR_H

//Dependencies
#include "os_port.h"
#include "error.h"

//String manipulation helper functions
char_t *strDuplicate(const char_t *s);
char_t *strTrimWhitespace(char_t *s);
void strRemoveTrailingSpace(char_t *s);
void strReplaceChar(char_t *s, char_t oldChar, char_t newChar);

#endif
