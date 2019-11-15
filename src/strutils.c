#include "strutils.h"
#include <ctype.h>

/*****************************************************************************/
/* Functions to manipulate strings											 */
/*****************************************************************************/

/* Copy each non-token argument into its own allocated space. */
static int strutils_split_copy(const char * string, char token, char ** array, uint32_t count);

int strutils_trim(char* str)
{
  char *p1, *p2;
  int i;

  if (str == NULL)
    return -1;

  p2 = str;
  while (isspace(*p2))
    if (*p2++ == 0)
      return -1;

  p1 = strdup(p2);
  if (p1 == NULL)
    return -1;

  for (i = strlen(p1); i > 0; i--)
    if (!isspace(p1[i-1]))
      break;

  p1[i] = 0;
  strcpy(str, p1);
  free(p1);

  return 0;
}

int strutils_one_space(char* str)
{
  char *p1, *p2;
  unsigned int i, len;
  int just_one;

  if (str == NULL)
    return -1;

  len = strlen(str);
  p1 = (char*)malloc(len+1);
  if (p1 == NULL)
    return -1;

  just_one = 0;
  p2 = p1;

  for (i = 0; i < len; i++) {
    if (isspace(str[i])) {
      if (just_one)
        continue;

      just_one = 1;
      *p2++ = ' ';
    } else {
      just_one = 0;
      *p2++ = str[i];
    }
  }
  *p2 = 0;
  strcpy(str, p1);
  free(p1);

  return 0;
}

int strutils_no_space(char* str)
{
  char *p1, *p2;
  unsigned int i, len;

  if (str == NULL)
    return -1;

  len = strlen(str);
  p1 = (char*)malloc(len+1);
  if (p1 == NULL)
    return -1;

  p2 = p1;

  for (i = 0; i < len; i++) {
    if (!isblank(str[i])) {
      *p2++ = str[i];
    }
  }
  *p2 = 0;
  strcpy(str, p1);
  free(p1);

  return 0;
}

int strutils_str_tostr(const char* str, char** value)
{
  if (str == NULL || value == NULL)
    return -1;

  *value = strdup(str);
  return 0;
}

int strutils_str_toint(const char* str, int* value)
{
  if (str == NULL || value == NULL)
    return -1;

  *value = atoi(str);
  return 0;
}

int strutils_str_tofloat(const char* str, float* value)
{
  if (str == NULL || value == NULL)
    return -1;

  *value = atof(str);
  return 0;
}

int strutils_str_tobool(const char* str, bool* value)
{
  if (str == NULL || value == NULL)
    return -1;

  *value = (strcmp(str, "true") == 0) ? true : false;
  return 0;
}

int strutils_count_matches(char *s, char c)
{
  char *actual, *last;
  int count = 0;

  actual = strchr(s, c);
  last = strrchr(s, c);

  if (actual == NULL)
    return count;

  count++;

  while(actual != last && actual != NULL){
    actual = strchr(actual + 1, c);
    count++;
  }			
  return count;
}

/* Count the number of arguments. */
static int strutils_split_count(const char * string, char token)
{
  const char * p = NULL;
  int count = 0;

  if(string == NULL || token == 0)
    return -1;

  p = string;
  while(*p) 
  {
    //skip
    while(*p && *p == token) p++;

    //want
    if(*p && *p != token)
    {
      count++;
      //want
      while (*p && *p != token)
        p++;
    }
  }
  return count;
}

int strutils_split (const char* string, char token, char *** array, uint32_t* count)
{
  int c;
  char** a;

  if(string == NULL || token == 0 || array == NULL || count == NULL)
    return -1;

  c = strutils_split_count(string, token);
  if (c == 0)
    return -1;

  a = malloc (sizeof (char *) * c);
  if (a == NULL)
    return -1;

  if (strutils_split_copy(string, token, a, c) == -1)
  {
    free(a);
    return -1;
  }

  *count = c;
  *array = a;

  return 0;
}

static int strutils_split_copy(const char * string, char token, char ** array, uint32_t count)
{
  int i = 0;
  const char *p;

  if(string == NULL || token == 0 || array == NULL || count == 0)
    return -1;

  p = string;
  while (*p)
  {
    //skip
    while(*p && *p == token) p++;

    //want
    if(*p && *p != token)
    {
      const char * end = p;
      char * copy;

      //want
      while (*end && *end != token)
        end++;

      copy = array[i] = malloc (end - p + 1);

      if (! array[i])
        return -1;

      //want
      while (*p && *p != token)
        *copy++ = *p++;

      *copy = 0;
      i++;
    }
  }

  if (i != count) 
    return -1;

  return 0;
}

