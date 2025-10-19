/*****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud ******************/
/******* Date      : 8 Apr 2023                 ******************/
/******* Version   : 0.1                        ******************/
/******* File Name : parse_datatype.c           ******************/
/*****************************************************************/

/**
 * @file parse_datatype.c
 * @brief Extracts a data type name from a string containing the sizeof
 * operator.
 *
 * This program demonstrates how to extract a data type name from a string
 * containing the sizeof operator using the sscanf function in C.
 */

#include "parse_datatype.h"

//-----------------< Private functions declaration -----------------/
/**
 * @brief Checks if a string represents a number.
 *
 * This function checks if the provided string represents a number.
 * It allows for digits (0-9) and an optional decimal point.
 * It ignores leading and trailing whitespace.
 *
 * @param str The string to check.
 * @return true if the string represents a number, false otherwise.
 */
static bool is_number(const char *str);

//-----------------< Functions implementation/Definition -----------------/

/**
 * @brief Parses a structure name from a string.
 *
 * This function parses a structure name from a string, typically in the form
 * of sizeof(struct_name).
 *
 * @param struct_name The input string containing the structure name.
 * @param buffer The buffer to store the parsed structure name.
 * @param error_flag Pointer to an error flag.
 * @return Pointer to the buffer containing the parsed structure name.
 */
char *parse_struct_name(char *struct_name, char *buffer, uint8_t *error_flag)
{
  // Extract data type from struct_name
  if (sscanf(struct_name, "sizeof(%49[^)])", buffer) != 1)
  {
    // Check if the struct name is a number
    if (is_number(struct_name))
    {
      // Reset the error flag
      *error_flag = 2;
      // Copy the string "int" into the buffer
      strncpy(buffer, "int", MAX_STRUCT_NAME_LEN);
      // Return "int" directly
      return buffer;
    }
    else
    {
      // Set the error flag to indicate the struct isn't in the form of
      // sizeof(datatype)
      *error_flag = 1;
      return NULL;
    }
  }
  else
  {
    // Reset the error flag
    *error_flag = 0;
    // Return a pointer to the extracted data type string
    return buffer;
  }
}

/**
 * @brief Checks if a string represents a number.
 *
 * This function checks if the given string is a valid number (integer or float).
 *
 * @param str The string to check.
 * @return true if the string is a number, false otherwise.
 */
static bool is_number(const char *str)
{
  int i = 0;
  bool has_dot = false;
  bool has_suffix = false;

  // Check if the string is empty
  if (str[0] == '\0')
  {
    return false;
  }

  // Check each character in the string
  while (str[i] != '\0')
  {
    if (!isdigit(str[i]))
    {
      if (str[i] == '.' && !has_dot)
      {
        has_dot = true;
      }
      else if ((str[i] == 'f' || str[i] == 'F') && !has_suffix)
      {
        has_suffix = true;
      }
      else
      {
        return false;
      }
    }
    i++;
  }

  return true;
}
