/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : memory_manager_test.c      *****************/
/****************************************************************/

/**
 * @file memory_manager_test.c
 * @brief Test file for Memory Manager functionality.
 *
 * This file is used to test the Memory Manager module on a Linux system.
 * It includes the main function to initialize necessary components, register
 * structure types, and print registered page families. Additionally, it
 * contains sample allocations to test memory management operations.
 */

#include "memory_manager_api.h"
#include <stdint.h>
#include <stdio.h>

//-----------------< UserDefinedDataTypes User defined data types
//-----------------/
/**
 * @brief Structure representing an employee.
 *
 * This structure defines the attributes of an employee, including their name
 * and employee ID.
 */
typedef struct emp_
{
  char name[32];   /**< The name of the employee. */
  uint32_t emp_id; /**< The employee ID. */
} emp_t;

/**
 * @brief Structure representing a student.
 *
 * This structure defines the attributes of a student, including their name,
 * roll number, and subject marks. Additionally, it contains a pointer to the
 * next student in a linked list.
 */
typedef struct student_
{
  char name[32];         /**< The name of the student. */
  uint32_t roll_no;      /**< The roll number of the student. */
  uint32_t marks_phys;   /**< The marks obtained in Physics. */
  uint32_t marks_chem;   /**< The marks obtained in Chemistry. */
  uint32_t marks_maths;  /**< The marks obtained in Mathematics. */
  struct student_ *next; /**< Pointer to the next student in the linked list. */
} student_t;

/**
 * @brief The main function.
 *
 * This function serves as the entry point to the program. It initializes
 * necessary components, registers structure types, and prints registered
 * page families.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @brief Main function for testing the memory manager.
 *
 * This function initializes the memory manager, registers structures, performs
 * allocations, and prints usage information.
 *
 * @return An integer indicating the exit status of the program.
 */

int main(void)
{

  int wait;
  mm_init();
  MM_REG_STRUCT(emp_t);
  MM_REG_STRUCT(student_t);
  mm_print_registered_page_families();

  emp_t *emp1 = XCALLOC(20, 100.05f);
  emp_t *emp2 = XCALLOC(10, 50);
  emp_t *emp3 = XCALLOC(10, sizeof(int));
  emp_t *emp4 = XCALLOC(30, sizeof(double));
  emp_t *emp5 = XCALLOC(30, sizeof(float));
  emp_t *emp6 = XCALLOC(30, 12);
  emp_t *emp7 = XCALLOC(60, emp_t);

  student_t *stud1 = XCALLOC(1, student_t);
  student_t *stud2 = XCALLOC(1, student_t);

  printf(" \nSCENARIO 1 : *********** \n");
  mm_print_memory_usage(0);
  mm_print_block_usage();

  scanf("%d", &wait);

  XFREE(emp1);
  XFREE(emp3);
  XFREE(emp5);
  XFREE(emp7);
  XFREE(stud2);
  printf(" \nSCENARIO 2 : *********** \n");
  mm_print_memory_usage(0);
  mm_print_block_usage();

  scanf("%d", &wait);

  XFREE(emp2);
  XFREE(emp4);
  XFREE(emp6);
  XFREE(stud1);
  printf(" \nSCENARIO 3 : *********** \n");
  mm_print_memory_usage(0);
  mm_print_block_usage();
  return 0;
}
