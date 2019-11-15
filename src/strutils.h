#ifndef __STRUTILS_H_INCLUDED__
#define __STRUTILS_H_INCLUDED__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * \brief	Removes any space from beginning and end of string
 * \param	str 	The string that will be trimmed
 * \return	0 if OK or -1 if param is null.
 */
int strutils_trim(char* str);

/**
 * \brief	Replace multiple spaces with a single space of string
 * \param	str 	The string that will be replaced
 * \return	0 if OK or -1 if param is null.
 */
int strutils_one_space(char* str);

/**
 * \brief	Remove all space of string
 * \param	str 	The string that will be removed
 * \return	0 if OK or -1 if param is null.
 */
int strutils_no_space(char* str);

/**
 * \brief 	Convert string to string.
 * \param	str		String that will be converted
 * \param	value	Value converted
 * \return	0 if Ok or -1 if param is null.
 */
int strutils_str_tostr(const char* str, char** value);
/**
 * \brief	Convert string to int
 * \param	str		String that will be converted
 * \param	value	Value converted
 * \return	0 if Ok or -1 if param is null.
 */
int strutils_str_toint(const char* str, int* value);
/**
 * \brief	Convert string to float
 * \param	str		String that will be converted
 * \param	value	Value converted
 * \return	0 if Ok or -1 if param is null.
 */
int strutils_str_tofloat(const char* str, float* value);
/**
 * \brief	Convert string to bool
 * \param	str		String that will be converted
 * \param	value	Value converted
 * \return	0 if Ok or -1 if param is null.
 */
int strutils_str_tobool(const char* str, bool* value);

/*
* \brief	Count the occurrences of a char in a string
* \param	s		Pointer to char, the string
* \param	c		char with will be sought
* \return	0 if OK or -1 if param is null.
*/
int strutils_count_matches(char *s, char c);

/*
* \brief It splits "string" into pieces at "token", and returns the number of pieces in "count", and the pieces themselves in "array".
* \return	0 if OK or ERROR 
*/
int strutils_split(const char* string, char token, char *** array, uint32_t* count);

#endif /* __STRUTILS_H_INCLUDED__ */

