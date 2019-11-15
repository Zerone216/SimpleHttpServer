#include <stdio.h>

#include "strkvm.h"
#include "strutils.h"

/*****************************************************************************/
/* Prototypes of Static Functions
*/
/*****************************************************************************/

/**
 * \brief	Clean node.
 * \param	var		Current node
 */
static void strkvm_var_clear(st_strkv *var);

/**
 * \brief	Add node into key/value struct.
 * \param	strkvm	Struct key/value
 * \param	var			Current node
 * \return	0 if Ok. Otherwise error code.
 */
static int strkvm_var_add(st_strkvm *strkvm, st_strkv *var);

/**
 * \brief	Auxiliar in adding string into key/value struct.
 * \param	strkvm	Struct key/value
 * \param	string		String with information.
 * \return	0 if Ok. Otherwise error code.
 */
static int strkvm_string_add(st_strkvm *strkvm, char *string);

/*****************************************************************************/
/* Functions to key/value
*/
/*****************************************************************************/

int strkvm_init(st_strkvm *strkvm)
{
  if (strkvm == NULL)
    return -1;

  memset(strkvm, 0, sizeof(st_strkvm));
  return 0;
}
/*****************************************************************************/

int strkvm_parse(st_strkvm *strkvm, char *buffer, size_t size, char split)
{
  char *buf = NULL;
  char *end, *begin;
  int result = 0;

  if (strkvm == NULL || buffer == NULL || size == 0)
    return -1;

  buf = strndup(buffer, size);

  if (buf == NULL) {
    result = -1;
    goto parse_end;
  }

  begin = buf;
  while ((end = strchr(begin, split))) {
    *end = 0;

    result = strkvm_string_add(strkvm, begin);
    if (result != 0)
      goto parse_end;

    begin = ++end;
  }

  if (strlen(begin) > 0) {
    result = strkvm_string_add(strkvm, begin);
    if (result != 0)
      goto parse_end;
  }

parse_end:
  if (buf)
    free(buf);
  return result;
}
/*****************************************************************************/

int strkvm_free(st_strkvm *strkvm)
{
  if (strkvm == NULL)
    return -1;

  strkvm_var_clear(strkvm->vars);
  memset(strkvm, 0, sizeof(st_strkvm));
  return 0;
}
/*****************************************************************************/

int strkvm_add(st_strkvm *strkvm, const char *name)
{
  int result;
  st_strkv *var;

  if (strkvm == NULL || name == NULL)
    return -1;

  var = (st_strkv *)malloc(sizeof(st_strkv));
  if (var == NULL)
    return -1;

  memset(var, 0, sizeof(st_strkv));
  var->name = strdup(name);

  result = strkvm_var_add(strkvm, var);
  if (result != 0) {
    free(var->name);
    free(var);
    return result;
  }
  return 0;
}
/*****************************************************************************/

int strkvm_add_string(st_strkvm *strkvm, const char *name, const char *value)
{
  int result;
  st_strkv *var;

  if (strkvm == NULL || name == NULL || value == NULL)
    return -1;

  var = (st_strkv *)malloc(sizeof(st_strkv));
  if (var == NULL)
    return -1;

  memset(var, 0, sizeof(st_strkv));
  var->name = strdup(name);
  var->value = strdup(value);

  result = strkvm_var_add(strkvm, var);
  if (result != 0) {
    free(var->name);
    free(var->value);
    free(var);
    return result;
  }
  return 0;
}
/*****************************************************************************/

int strkvm_add_int(st_strkvm *strkvm, const char *name, int value)
{
  char v[50];

  if (strkvm == NULL || name == NULL)
    return -1;

  snprintf(v, sizeof(v), "%d", value);
  return strkvm_add_string(strkvm, name, v);
}
/*****************************************************************************/

int strkvm_add_float(st_strkvm *strkvm, const char *name, float value)
{
  char v[50];

  if (strkvm == NULL || name == NULL)
    return -1;

  snprintf(v, sizeof(v), "%f", value);
  return strkvm_add_string(strkvm, name, v);
}
/*****************************************************************************/

int strkvm_add_bool(st_strkvm *strkvm, const char *name, bool value)
{
  char v[6];

  if (strkvm == NULL || name == NULL)
    return -1;

  snprintf(v, sizeof(v), "%s", (value == true ? "true" : "false"));
  return strkvm_add_string(strkvm, name, v);
}
/*****************************************************************************/

int strkvm_remove(st_strkvm *strkvm, const char *name)
{
  st_strkv *var = NULL;
  st_strkv *prev = NULL;

  if (strkvm == NULL || name == NULL)
    return -1;

  for (var = strkvm->vars; var; var = var->next) {
    if (strcmp(var->name, name) == 0) {
      if (prev == NULL)
        strkvm->vars = var->next;
      else
        prev->next = var->next;

      free(var->name);
      free(var->value);
      free(var);

      strkvm->count--;
      break;
    }
    prev = var;
  }
  return 0;
}
/*****************************************************************************/

int strkvm_tostring(st_strkvm *strkvm, char **buffer, size_t *length, char split)
{
  FILE *out = NULL;
  st_strkv *var = NULL;

  if (strkvm == NULL)
    return -1;

  if (!(out = open_memstream(buffer, length)))
    return -1;

  for (var = strkvm->vars; var; var = var->next) {
    if (var->value != NULL)
      fprintf(out, "%s=%s%c", var->name, var->value, split);
    else
      fprintf(out, "%s;", var->name);
  }

  fclose(out);
  return 0;
}
/*****************************************************************************/

int strkvm_count(st_strkvm *strkvm)
{
  if (strkvm == NULL)
    return -1;

  return (int)strkvm->count;
}
/*****************************************************************************/

int strkvm_get_string(st_strkvm *strkvm, const char *name, char **value)
{
  st_strkv *var;

  if (strkvm == NULL || name == NULL || value == NULL)
    return -1;

  for (var = strkvm->vars; var; var = var->next)
    if (strcmp(var->name, name) == 0)
      break;

  if (var == NULL)
    return -1;

  *value = NULL;
  if (var->value != NULL)
    *value = strdup(var->value);

  return 0;
}
/*****************************************************************************/

int strkvm_get_int(st_strkvm *strkvm, const char *name, int *value)
{
  st_strkv *var;

  if (strkvm == NULL || name == NULL || value == NULL)
    return -1;

  for (var = strkvm->vars; var; var = var->next)
    if (strcmp(var->name, name) == 0)
      break;

  if (var == NULL)
    return -1;

  *value = atoi(var->value);
  return 0;
}
/*****************************************************************************/

int strkvm_get_float(st_strkvm *strkvm, const char *name, float *value)
{
  st_strkv *var;

  if (strkvm == NULL || name == NULL || value == NULL)
    return -1;

  for (var = strkvm->vars; var; var = var->next)
    if (strcmp(var->name, name) == 0)
      break;

  if (var == NULL)
    return -1;

  *value = atof(var->value);
  return 0;
}
/*****************************************************************************/

int strkvm_get_bool(st_strkvm *strkvm, const char *name, bool *value)
{
  st_strkv *var;

  if (strkvm == NULL || name == NULL || value == NULL)
    return -1;

  for (var = strkvm->vars; var; var = var->next)
    if (strcmp(var->name, name) == 0)
      break;

  if (var == NULL)
    return -1;

  *value = (strcmp(var->value, "true") == 0) ? true : false;
  return 0;
}
/*****************************************************************************/

st_strkv *strkvm_get_next(st_strkvm *strkvm, const st_strkv *var)
{
  st_strkv *v;

  if (strkvm == NULL)
    return NULL;

  if (var == NULL)
    return strkvm->vars;

  for (v = strkvm->vars; v; v = v->next)
    if (var == v)
      return v->next;

  return NULL;
}

/*****************************************************************************/
/* Static Functions
*/
/*****************************************************************************/

static void strkvm_var_clear(st_strkv *var)
{
  if (var == NULL)
    return;

  if (var->next != NULL)
    strkvm_var_clear(var->next);

  if (var->name != NULL)
    free(var->name);
  if (var->value != NULL)
    free(var->value);

  free(var);
}
/*****************************************************************************/

static int strkvm_var_add(st_strkvm *strkvm, st_strkv *var)
{
  if (strkvm == NULL || var == NULL)
    return -1;

  var->next = strkvm->vars;
  strkvm->vars = var;
  strkvm->count++;

  return 0;
}
/*****************************************************************************/

static int strkvm_string_add(st_strkvm *strkvm, char *string)
{
  char *n, *v;
  st_strkv *var;
  int result = 0;

  if (strkvm == NULL || string == NULL)
    return -1;

  n = strdup(string);
  v = strchr(n, '=');
  if (v != NULL) {
    *v++ = 0;
    strutils_trim(v);
  }

  strutils_trim(n);

  var = (st_strkv *)malloc(sizeof(st_strkv));
  if (var == NULL) {
    result = -1;
    goto string_add_end;
  }

  memset(var, 0, sizeof(st_strkv));
  var->name = strdup(n);

  if (v != NULL)
    var->value = strdup(v);

  result = strkvm_var_add(strkvm, var);

string_add_end:
  if (n)
    free(n);
  if (result != 0 && var) {
    if (var->name)
      free(var->name);
    if (var->value)
      free(var->value);
    free(var);
  }
  return result;
}
/*****************************************************************************/
