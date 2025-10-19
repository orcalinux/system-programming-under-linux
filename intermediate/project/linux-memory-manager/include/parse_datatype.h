/*****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud ******************/
/******* Date      : 8 Apr 2023                 ******************/
/******* Version   : 0.1                        ******************/
/******* File Name : parse_datatype.h           ******************/
/*****************************************************************/

/**
 * @file parse_datatype.h
 * @brief Header file for parsing data type names.
 *
 * This file contains declarations for functions related to parsing data type
 * names from strings.
 */

#ifndef PARSE_DATATYPE_H_
#define PARSE_DATATYPE_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def MAX_STRUCT_NAME_LEN
 * @brief Maximum length of the data type name.
 *
 * Defines the maximum length allowed for a data type name.
 */
#define MAX_STRUCT_NAME_LEN 50

//-----------------< Public functions interfacce -----------------/
/**
 * @brief Parses the name of a struct from a string.
 *
 * This function extracts the name of a struct from a string formatted as
 * "sizeof(datatype)" and stores it in the provided buffer. If the string does
 * not match this format, it checks if the string represents a number and sets
 * the error flag accordingly.
 *
 * @param struct_name The string containing the sizeof expression.
 * @param buffer Pointer to a buffer where the extracted struct name or integer
 * value will be stored. If the struct name is extracted successfully, it will
 * be stored in this buffer. If the struct name is a number, the integer value
 * will be stored in this buffer.
 * @param error_flag Pointer to a uint8_t variable to indicate the status of the
 * struct name. It can have the following values:
 *                   - 0: No error, struct name extracted successfully.
 *                   - 1: Error in the format of the struct name, not in the
 * form "sizeof(datatype)".
 *                   - 2: The struct name is actually a number, and the integer
 * value is stored in the buffer.
 * @return If the struct name is extracted successfully or it's a number,
 * returns "int". If an error occurs, returns NULL.
 */
char *parse_struct_name(char *struct_name, char *buffer, uint8_t *error_flag);

#endif /**< PARSE_DATATYPE_H_ */
