/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : datatype_size_lookup.h     *****************/
/****************************************************************/

/**
 * @file datatype_size_lookup.h
 * @brief Header file for data type size lookup functionality and mappings.
 *
 * This file contains declarations and mappings for functions and structures
 * related to retrieving the size of data types.
 */

#ifndef DATATYPE_SIZE_LOOKUP_H_
#define DATATYPE_SIZE_LOOKUP_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**
 * @def MAX_STRUCT_NAME_LEN
 * @brief Maximum length of a data type name.
 *
 * Defines the maximum length allowed for a data type name.
 */
#define MAX_STRUCT_NAME_LEN 50

/**
 * @brief Gets the size of a data type by its name.
 *
 * This function searches for the given data type name in a pre-defined
 * mapping table and returns the size of the data type if found.
 *
 * @param data_type The name of the data type to get the size of.
 * @return The size of the data type if found, otherwise 0.
 */
size_t get_size_of_datatype(const char *data_type);

#endif /**< DATATYPE_SIZE_LOOKUP_H_ */
