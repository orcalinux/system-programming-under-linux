/*******************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud    *****************/
/******* Date      : 13 Apr 2023                   *****************/
/******* Version   : 0.1                           *****************/
/******* File Name : glthread.h                    *****************/
/*******************************************************************/

/**
 * @file glthread.h
 * @brief Header file for the Generic Linked List Thread library.
 *
 * This header file contains the interface for the Generic Linked List Thread
 * library, which provides functionality for managing generic linked lists using
 * threaded linking.
 */

#ifndef GLUETHREAD_H_
#define GLUETHREAD_H_

//-----------------< user defined data type section -----------------/
/**
 * @brief Structure representing a generic linked list node for threaded
 * linking.
 *
 * This structure defines a generic linked list node for threaded linking.
 * It consists of left and right pointers for threading the nodes together.
 */
typedef struct glthread_
{
  struct glthread_ *left;  /**< Pointer to the left node in the linked list. */
  struct glthread_ *right; /**< Pointer to the right node in the linked list. */
} glthread_t;

//-----------------< Public functions interface -----------------/
/**
 * @brief Initialize a glthread_t structure.
 *
 * @param glthread Pointer to the glthread_t structure to be initialized.
 */
void init_glthread(glthread_t *glthread);

/**
 * @brief Adds a new node after the specified current node in the threaded
 * linked list.
 *
 * This function adds a new node after the specified current node in the
 * threaded linked list.
 *
 * @param curr_glthread Pointer to the current node in the threaded linked list.
 * @param new_glthread Pointer to the new node to be added.
 */
void glthread_add_next(glthread_t *base_glthread, glthread_t *new_glthread);

/**
 * @brief Adds a new node before the specified current node in the threaded
 * linked list.
 *
 * This function adds a new node before the specified current node in the
 * threaded linked list.
 *
 * @param curr_glthread Pointer to the current node in the threaded linked list.
 * @param new_glthread Pointer to the new node to be added.
 */
void glthread_add_before(glthread_t *base_glthread, glthread_t *new_glthread);

/**
 * @brief Removes the specified node from the threaded linked list.
 *
 * This function removes the specified node from the threaded linked list.
 *
 * @param curr_glthread Pointer to the node to be removed.
 */
void remove_glthread(glthread_t *glthread);

/**
 * @brief Add a new glthread_t structure at the last position of a linked list.
 *
 * @param base_glthread Pointer to the base glthread_t structure (head of the
 * linked list).
 * @param new_glthread Pointer to the new glthread_t structure to be added.
 */
void glthread_add_last(glthread_t *base_glthread, glthread_t *new_glthread);

/**
 * @brief Delete all glthread_t structures in a linked list.
 *
 * @param base_glthread Pointer to the base glthread_t structure (head of the
 * linked list).
 */
void delete_glthread_list(glthread_t *base_glthread);

/**
 * @brief Get the count of glthread_t structures in a linked list.
 *
 * @param base_glthread Pointer to the base glthread_t structure (head of the
 * linked list).
 * @return unsigned int The count of glthread_t structures in the linked list.
 */
unsigned int get_glthread_list_count(glthread_t *base_glthread);

/**
 * @brief Insert a glthread_t structure into a sorted linked list based on
 * priority.
 *
 * @param base_glthread Pointer to the base glthread_t structure (head of the
 * linked list).
 * @param glthread Pointer to the glthread_t structure to be inserted.
 * @param comp_fn Pointer to the comparison function used to determine priority.
 * @param offset Offset to access the user data within the glthread_t structure.
 */
void glthread_priority_insert(glthread_t *base_glthread, glthread_t *glthread,
                              int (*comp_fn)(void *, void *), int offset);

/**
 * @brief Search for a specific glthread_t structure in the linked list.
 *
 * @param base_glthread Pointer to the base glthread_t structure (head of the
 * linked list).
 * @param thread_to_struct_fn Function pointer to convert a glthread_t structure
 * to the corresponding user-defined structure.
 * @param key Pointer to the key used for comparison.
 * @param comparison_fn Function pointer to the comparison function used to
 * compare keys.
 * @return void* Pointer to the user-defined structure corresponding to the
 * found glthread_t structure, or NULL if not found.
 */
void *glthread_search(glthread_t *base_glthread,
                      void *(*thread_to_struct_fn)(glthread_t *), void *key,
                      int (*comparison_fn)(void *, void *));
//-----------------< Function-like macro section -----------------/
/**
 * @brief Macro to check if a linked list of glthread_t structures is empty.
 *
 * This macro checks if a linked list of glthread_t structures is empty.
 * It evaluates to true if both the right and left pointers of the provided
 * glthread_t structure are NULL, indicating an empty list.
 *
 * @param glthreadptr Pointer to the glthread_t structure representing the
 * linked list.
 * @return int Returns 1 if the linked list is empty, 0 otherwise.
 */
#define IS_GLTHREAD_LIST_EMPTY(glthreadptr) \
  ((glthreadptr)->right == 0 && (glthreadptr)->left == 0)

/**
 * @brief Macro to convert a glthread_t structure to a user-defined structure.
 *
 * This macro provides a convenient way to convert a glthread_t structure to a
 * user-defined structure. It creates a conversion function that takes a
 * glthread_t pointer and returns a pointer to the user-defined structure.
 * This is particularly useful when you have a glthread_t structure embedded
 * within a user-defined structure and need to access the user-defined data.
 *
 * @param fn_name The name of the conversion function to be created.
 * @param struct_type The type of the user-defined structure.
 * @param glthread_member The name of the glthread_t member within the
 * user-defined structure.
 * @param glthread_ptr The name of the glthread_t pointer variable.
 *
 * Example usage:
 * Suppose we have a user-defined structure named `block_meta_data_t` that
 * contains a `glthread_t` member named `priority_thread_glue`. We want to
 * create a conversion function named `glthread_to_block_meta_data` to convert
 * a `glthread_t` pointer to a `block_meta_data_t` pointer:
 *
 * GLTHREAD_TO_STRUCT(glthread_to_block_meta_data, block_meta_data_t,
 *                    priority_thread_glue, glthread_ptr);
 *
 * Now, we can use `glthread_to_block_meta_data` to convert `glthread_t`
 * pointers to `block_meta_data_t` pointers and access the metadata associated
 * with memory blocks.
 */
#define GLTHREAD_TO_STRUCT(fn_name, structure_name, field_name, glthreadptr) \
  static inline structure_name *fn_name(glthread_t *glthreadptr)             \
  {                                                                          \
    return (structure_name *)((char *)(glthreadptr) -                        \
                              (char *)&(((structure_name *)0)->field_name)); \
  }

/**
 * @brief Macro to retrieve the base of a linked list.
 *
 * This macro retrieves the base of a linked list given a pointer to a
 * glthread_t structure. It returns the pointer to the right child of the
 * provided glthread_t structure, which is typically the base of the linked
 * list.
 *
 * @param glthreadptr Pointer to the glthread_t structure from which to retrieve
 * the base.
 * @return glthread_t* Pointer to the base of the linked list.
 */
#define BASE(glthreadptr) ((glthreadptr)->right)

/**
 * @brief Macro to begin iterating over a linked list of glthread_t structures.
 *
 * This macro sets up a loop to iterate over a linked list of glthread_t
 * structures. It initializes necessary variables and pointers for the
 * iteration.
 *
 * @param glthreadptrstart Pointer to the starting glthread_t structure for
 * iteration.
 * @param glthreadptr Pointer to the current glthread_t structure being
 * iterated.
 */
#define ITERATE_GLTHREAD_BEGIN(glthreadptrstart, glthreadptr) \
  {                                                           \
    glthread_t *_glthread_ptr = NULL;                         \
    glthreadptr = BASE(glthreadptrstart);                     \
    for (; glthreadptr != NULL; glthreadptr = _glthread_ptr)  \
    {                                                         \
      _glthread_ptr = (glthreadptr)->right;

/**
 * @brief Macro to end iteration over a linked list of glthread_t structures.
 *
 * This macro marks the end of the loop initiated by ITERATE_GLTHREAD_BEGIN.
 * It closes the loop block.
 *
 * @param glthreadptrstart Pointer to the starting glthread_t structure for
 * iteration.
 * @param glthreadptr Pointer to the current glthread_t structure being
 * iterated.
 */
#define ITERATE_GLTHREAD_END(glthreadptrstart, glthreadptr) \
  }                                                         \
  }

/**
 * @brief Macro to get a pointer to user-defined data from a glthread_t pointer
 * and offset.
 *
 * This macro calculates a pointer to user-defined data from a given glthread_t
 * pointer and an offset. It's useful when you have a glthread_t pointer
 * embedded within a user-defined structure and you want to access the
 * user-defined data based on a known offset.
 *
 * @param glthreadptr Pointer to the glthread_t structure.
 * @param offset Offset of the glthread_t member within the user-defined
 * structure.
 * @return Pointer to the user-defined data.
 */
#define GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthreadptr, offset) \
  (void *)((char *)(glthreadptr) - offset)

#endif /**< GLUETHREAD_H_ */
