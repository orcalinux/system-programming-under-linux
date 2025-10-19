/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : memory_manager_api.h       *****************/
/****************************************************************/

/**
 * @file memory_manager_api.h
 * @brief Header file for the Memory Manager API.
 *
 * This file contains declarations for the Memory Manager API functions.
 * The Memory Manager API provides functions for initializing the memory
 * manager, managing page families, allocating and freeing memory, and printing
 * memory usage details.
 */

#ifndef UAPI_MM_H_
#define UAPI_MM_H_

//-----------------< Includes section -----------------/
#include <stdint.h>

//-----------------< Public functions interface section -----------------/
/**
 * @brief Initializes the memory manager.
 *
 * This function initializes the memory manager. It sets up necessary
 * configurations and parameters for memory management operations within the
 * program. It specifically determines the system page size using the
 * `getpagesize()` system call and assigns it to the global variable
 * `SYSTEM_PAGE_SIZE`.
 *
 * @note This function should be called before any memory management operations
 * are performed within the program. It is typically called at the beginning of
 * the program execution to ensure proper initialization of memory management
 * functionalities.
 *
 * @warning This function relies on the `getpagesize()` system call to determine
 * the system page size. Therefore, it may not be portable across all platforms.
 * It is primarily intended for use in Unix-like systems where `getpagesize()`
 * is available.
 *
 * @see man getpagesize()
 */
void mm_init();

/**
 * @brief Instantiates a new page family for a memory structure.
 *
 * This function creates a new page family for a memory structure identified by
 * its name and size. It allocates memory for the page family and adds it to the
 * existing virtual memory pages if necessary. Each page family can contain
 * multiple memory structures of the same type.
 *
 * @param struct_name The name of the memory structure.
 * @param struct_size The size of the memory structure.
 *
 * @note If the size of the memory structure exceeds the system page size, an
 * error message is printed, and the function returns without creating the page
 * family.
 *
 * @note This function maintains a linked list of virtual memory pages
 * (`first_vm_page_for_families`) to store the page families. If there are no
 * existing pages, it allocates a new page and initializes it with the first
 * page family. If the existing pages are full, it allocates a new page and adds
 * it to the beginning of the linked list.
 *
 * @note If a page family with the same name already exists, an assertion error
 * is triggered, indicating a conflict in page family instantiation.
 *
 * @warning This function relies on the `mm_get_new_vm_page_from_kernel()`
 * function to allocate memory from the kernel for the page family. Improper use
 * or misuse of this function can lead to memory leaks or system instability.
 *
 * @see mm_get_new_vm_page_from_kernel()
 */
void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size);

/**
 * @brief Allocates and initializes memory for an array of structures.
 *
 * This function allocates memory for an array of structures of the specified
 * type and initializes the memory to zero. It first looks up the page family
 * associated with the specified structure name to determine the size of the
 * structure. Then, it checks if the requested memory size exceeds the maximum
 * allocatable memory per page. If the allocation is successful, it initializes
 * the allocated memory to zero and returns a pointer to the allocated memory.
 *
 * @param struct_name The name of the structure type for which memory is to be
 * allocated.
 * @param units The number of structures to allocate.
 *
 * @return A pointer to the allocated memory if successful, or NULL if the
 * allocation fails.
 *
 * @note This function assumes that the specified structure type has been
 * registered with the Memory Manager using the mm_register_structure function.
 *       It also assumes that the specified structure type has a corresponding
 * page family registered with the Memory Manager.
 */
void *xcalloc(char *struct_name, int units);

/**
 * @brief Frees memory allocated by the memory manager.
 *
 * This function is used to free memory that was previously allocated by the
 * memory manager. It takes a pointer to the memory to be freed as its argument.
 * The pointer is adjusted to point to the block metadata, and then it is passed
 * to the memory manager's free blocks function.
 *
 * @param app_data Pointer to the memory to be freed.
 */
void xfree(void *app_data);

/**
 * @brief Prints all registered page families.
 *
 * This function prints all page families that have been registered with the
 * Linux Memory Manager. It iterates over all virtual memory pages hosting page
 * families and prints information about each page family, including its name
 * and size.
 *
 * @note This function should be invoked after the application has performed
 * registration for all its structures using the `MM_REG_STRUCT` macro. It
 * relies on the `first_vm_page_for_families` global variable, which maintains a
 * linked list of virtual memory pages containing page families.
 *
 * @see MM_REG_STRUCT
 */
void mm_print_registered_page_families();
/**
 * @brief Prints memory usage details related to the memory manager.
 *
 * This function prints information about the memory usage of the memory
 * manager, including details of each virtual memory page family and the total
 * memory being used. Optionally, it can filter the output by a specific
 * structure name.
 *
 * @param struct_name Optional parameter to filter the output by a specific
 * structure name.
 */

void mm_print_memory_usage(char *struct_name);

/**
 * @brief Prints information about the memory block usage.
 *
 * This function iterates through all virtual memory pages and their associated
 * memory block families to print information about the memory block usage,
 * including the total block count, free block count, occupied block count, and
 * application memory usage.
 */
void mm_print_block_usage();

//-----------------< Function-like macro section -----------------/
/**
 * @brief Registers a memory structure for page family instantiation.
 *
 * This macro facilitates the registration of a memory structure for page family
 * instantiation within the memory manager. It takes the name of the structure
 * (`struct_name`) as a parameter and uses the `#` operator to stringify it,
 * which is then passed to the `mm_instantiate_new_page_family()` function along
 * with the size of the structure.
 *
 * @param struct_name The name of the memory structure to be registered.
 *
 * @note This macro should be used to register each memory structure before it
 * is instantiated as a page family within the memory manager. It ensures proper
 * initialization of the memory management system and enables efficient
 * allocation and management of memory pages.
 *
 * @see mm_instantiate_new_page_family()
 */
#define MM_REG_STRUCT(struct_name)                                             \
  (mm_instantiate_new_page_family(#struct_name, sizeof(struct_name)))

/**
 * @brief Macro for allocating memory for multiple instances of a structure and
 * initializing them to zero.
 *
 * This macro simplifies the process of allocating memory for multiple instances
 * of a structure and initializing them to zero. It takes the number of units
 * and the name of the structure as input parameters.
 *
 * @param units The number of instances of the structure to allocate memory for.
 * @param struct_name The name of the structure for which memory is to be
 * allocated.
 *
 * @return A pointer to the allocated memory, initialized to zero, or NULL if
 * allocation fails.
 */
#define XCALLOC(units, struct_name) (xcalloc(#struct_name, units))

/**
 * @brief Macro for freeing memory using a custom deallocation function.
 *
 * This macro is used for freeing memory using a custom deallocation function
 * specified by the user. The macro takes a pointer to the memory to be freed as
 * its argument and passes it to the custom deallocation function xfree().
 *
 * @param ptr Pointer to the memory to be freed.
 */
#define XFREE(ptr) (xfree(ptr))

#endif /**< UAPI_MM_H_ */
