#ifndef __STRKVM_H_INCLUDED__
#define __STRKVM_H_INCLUDED__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

//! Structure with information
typedef struct st_strkv {
	char* name;									//!< Name
	char* value;								//!< Value
	struct st_strkv* next;			//!< Next node
} st_strkv;

//! Structure to make key/value string
typedef struct {
	uint16_t count; 							//!< Total of nodes
	st_strkv* vars;					//!< List of nodes
} st_strkvm;

/**
 * \brief	Initialize key/value struct.
 * \param	strkvm	Struct that will be initialized.
 * \return	0 if Ok or -1 if param is null.
 */
int strkvm_init(st_strkvm* strkvm);

/**
 * \brief	Convert a formated string into key/value struct.
 * \param	strkvm	Struct key/value
 * \param	buffer		Formated string that will be read.
 * \param	size		Size buffer
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_parse(st_strkvm* strkvm, char* buffer, size_t size, char split);

/**
 * \brief	Frees memory space used to make key/value.
 * \param	strkvm	Struct that will be initialized.
 * \return	0 if Ok or -1 if param is null.
 */
int strkvm_free(st_strkvm* strkvm);

/**
 * \brief	Add a string type variable (name only) into strkvm list.
 * \param	strkvm	Struct that will be added.
 * \param	name		Name of variable
 * \return	0 if Ok or -1 if param is null.
 */
int strkvm_add(st_strkvm* strkvm, const char* name);

/**
 * \brief	Add a string type variable into strkvm list.
 * \param	strkvm	Struct that will be added.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_add_string(st_strkvm* strkvm, const char* name, const char* value);

/**
 * \brief	Add a integer type variable into strkvm list.
 * \param	strkvm	Struct that will be added.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_add_int(st_strkvm* strkvm, const char* name, int value);

/**
 * \brief	Add a float type variable into strkvm list.
 * \param	strkvm	Struct that will be added.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_add_float(st_strkvm* strkvm, const char* name, float value);

/**
 * \brief	Add a boolean type variable into strkvm list.
 * \param	strkvm	Struct that will be added.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_add_bool(st_strkvm* strkvm, const char* name, bool value);

/**
 * \brief	Remove a variable from strkvm list.
 * \param	strkvm	Struct that will be removed.
 * \param	name		Name of variable to remove from strkvm list.
 * \return	0 if Ok or -1 if param is null.
 */
int strkvm_remove(st_strkvm* strkvm, const char* name);

/**
 * \brief	Converts the strkvm struct to its equivalent string representation.
 * \param	strkvm	Struct that will be converted.
 * \param	buffer		Pointer that will be address of the resulting string.
 * \param	length		Size of the resulting string.
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_tostring(st_strkvm* strkvm, char** buffer, size_t* length, char split);

/**
 * \brief	Return count of variables of strkvm list.
 * \param	strkvm	Struct strkvm
 * \return	key/value count if Ok or -1 if param is null.
 */
int strkvm_count(st_strkvm* strkvm);

/**
 * \brief	Get a string type variable into strkvm list.
 * \param	strkvm	Struct with information.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_get_string(st_strkvm* strkvm, const char* name, char** value);

/**
 * \brief	Get a integer type variable into strkvm list.
 * \param	strkvm	Struct with information.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_get_int(st_strkvm* strkvm, const char* name, int* value);

/**
 * \brief	Get a float type variable into strkvm list.
 * \param	strkvm	Struct with information.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_get_float(st_strkvm* strkvm, const char* name, float* value);

/**
 * \brief	Get a boolean type variable into strkvm list.
 * \param	strkvm	Struct with information.
 * \param	name		Name of variable
 * \param	value		Value of variable
 * \return	0 if Ok. Otherwise error code.
 */
int strkvm_get_bool(st_strkvm* strkvm, const char* name, bool* value);

/**
 * \brief	Get a next node into strkvm list.
 * \param	strkvm	Struct with information.
 * \param	var			Current node.
 * \return	A bode if OK. Otherwise NULL.
 */
st_strkv* strkvm_get_next(st_strkvm* strkvm, const st_strkv* var);

#endif /* __STRKVM_H_INCLUDED__ */
