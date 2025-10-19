/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : memory_manager.c           *****************/
/****************************************************************/

/**
 * @file memory_manager.c
 * @brief Implementation file for the Memory Manager module.
 *
 * This file contains the implementation of functions declared in
 * MemoryManager.h. The Memory Manager module is responsible for managing memory
 * allocation and deallocation, including virtual memory page management, block
 * metadata handling, and allocation algorithms.
 */

//-----------------< Includes section -----------------*/
//---< System includes ---/
#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
//---< Project includes ---/
#include "colors.h"
#include "datatype_size_lookup.h"
#include "memory_manager.h"
#include "memory_manager_api.h"
#include "parse_datatype.h"

//-----------------< Global variable section -----------------*/
/**
 * @brief Size of the system page.
 *
 * This static variable holds the size of the system page. It is initialized to
 * 0 and should be updated to the actual size of the system page during program
 * initialization using a system-specific function or method.
 *
 * @note This variable should be initialized to the size of the system page
 *       before any memory management operations are performed within the
 * program. The actual size of the system page depends on the underlying
 * operating system and hardware architecture.
 */
static size_t SYSTEM_PAGE_SIZE = 0;

/**
 * @brief Pointer to the first virtual memory page for page families.
 *
 * This static pointer variable holds the address of the first virtual memory
 * page used to store page families. It is initialized to NULL, indicating that
 * no virtual memory page is currently allocated for page families. As page
 * families are instantiated, new virtual memory pages may be allocated and
 * linked to this pointer.
 *
 * @note This variable is static and should be accessible only within the scope
 * of the file in which it is declared. It is used to maintain the linked list
 * of virtual memory pages for page families throughout the program.
 */
static vm_page_for_families_t *first_vm_page_for_families = NULL;

//-----------------< MemoryManagement Memory Management -----------------*/

/**
 * @brief Initializes the memory manager.
 *
 * This function initializes the memory manager by setting the system page size.
 * It must be called before any other memory management operations.
 */
void mm_init() { SYSTEM_PAGE_SIZE = getpagesize(); }

/**
 * @brief Allocates new virtual memory pages from the kernel.
 *
 * This function allocates a specified number of virtual memory pages from the
 * kernel using the mmap system call.
 *
 * @param units The number of system pages to allocate.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
static void *mm_get_new_vm_page_from_kernel(int units)
{
  // Use the mmap() system call to allocate memory from the kernel
  char *vm_page =
      mmap(NULL, units * SYSTEM_PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
           MAP_ANON | MAP_PRIVATE, 0, 0);
  // Check if the allocation was successful
  if (vm_page == MAP_FAILED)
  {
    // Print an error message if allocation fails
    printf("Error: VM page allocation failed\n");
    return NULL;
  }

  // Initialize the allocated memory block with zeros
  memset(vm_page, 0, units * SYSTEM_PAGE_SIZE);

  // Return a pointer to the allocated memory block
  return (void *)vm_page;
}

/**
 * @brief Returns virtual memory pages back to the kernel.
 *
 * This function deallocates a specified number of virtual memory pages back to
 * the kernel using the munmap system call.
 *
 * @param vm_page A pointer to the memory to be deallocated.
 * @param units The number of system pages to deallocate.
 */
static void mm_return_vm_page_to_kernel(void *vm_page, int units)
{
  // Use the munmap() system call to return memory to the kernel
  if (munmap(vm_page, units * SYSTEM_PAGE_SIZE) != 0)
  {
    // Print an error message if unmapping fails
    printf("Error: Could not munmap VM page to kernel\n");
  }
}

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
 */
void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size)
{
  vm_page_family_t *vm_page_family_curr = NULL;
  vm_page_for_families_t *new_vm_page_for_families = NULL;

  // Check if the size of the memory structure exceeds the system page size
  if (struct_size > SYSTEM_PAGE_SIZE)
  {
    printf("Error: %s() structure %s size exceeds system page size\n",
           __FUNCTION__, struct_name);
    return;
  }

  // If there are no existing virtual memory pages, allocate a new page and
  // initialize it with the first page family
  if (!first_vm_page_for_families)
  {
    first_vm_page_for_families =
        (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
    first_vm_page_for_families->next = NULL;
    strncpy(first_vm_page_for_families->vm_page_family[0].struct_name,
            struct_name, MM_MAX_STRUCT_NAME);
    first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
    init_glthread(&first_vm_page_for_families->vm_page_family[0]
                       .free_block_priority_list_head);
    return;
  }

  vm_page_family_curr = lookup_page_family_by_name(struct_name);

  // Trigger an assertion error if a page family with the same name already
  // exists
  if (vm_page_family_curr)
  {
    assert(0);
  }

  uint32_t count = 0;

  // Iterate over existing page families to check if a page family with the same
  // name already exists
  ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr)
  {
    if (strncmp(vm_page_family_curr->struct_name, struct_name,
                MM_MAX_STRUCT_NAME) != 0)
    {
      count++;
    }
  }
  ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families, vm_page_family_curr);

  // If the existing page is full, allocate a new page and add it to the
  // beginning of the linked list
  if (count == (uint32_t)MAX_FAMILIES_PER_VM_PAGE)
  {
    new_vm_page_for_families =
        (vm_page_for_families_t *)mm_get_new_vm_page_from_kernel(1);
    new_vm_page_for_families->next = first_vm_page_for_families;
    first_vm_page_for_families = new_vm_page_for_families;
    vm_page_family_curr = &first_vm_page_for_families->vm_page_family[0];
  }

  // Initialize the new page family with the specified name and size
  strncpy(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME);
  vm_page_family_curr->struct_size = struct_size;

  // Set the 'first_page' pointer of the current page family to NULL
  // This indicates that there are no associated virtual memory pages with this
  // page family yet
  vm_page_family_curr->first_page = NULL;

  // Initialize the glthread_t structure within the first virtual memory page
  init_glthread(&first_vm_page_for_families->vm_page_family[0]
                     .free_block_priority_list_head);
}

vm_page_family_t *lookup_page_family_by_name(char *struct_name)
{
  // Pointer to iterate over VM pages
  vm_page_for_families_t *current_page = first_vm_page_for_families;

  // Iterate over all VM pages containing page families
  while (current_page != NULL)
  {
    // Pointer to iterate over page families within the current VM page
    vm_page_family_t *vm_page_family_curr = NULL;

    // Iterate over page families within the current VM page
    ITERATE_PAGE_FAMILIES_BEGIN(current_page, vm_page_family_curr)
    {
      // Check if the name of the current page family matches the provided
      // struct_name
      if (strncmp(vm_page_family_curr->struct_name, struct_name,
                  MM_MAX_STRUCT_NAME) == 0)
      {
        // If a match is found, return the pointer to the page family object
        return vm_page_family_curr;
      }
    }
    ITERATE_PAGE_FAMILIES_END(current_page, vm_page_family_curr);

    // Move to the next VM page
    current_page = current_page->next;
  }

  // If no matching page family is found, return NULL
  return NULL;
}

/**
 * @brief Adds a new page to a page family.
 *
 * This function allocates a new virtual memory page and adds it to the specified
 * page family.
 *
 * @param vm_page_family The page family to which the new page will be added.
 * @return A pointer to the newly allocated page, or NULL if allocation fails.
 */
static vm_page_t *mm_family_new_page_add(vm_page_family_t *vm_page_family)
{

  // Allocate a new virtual memory page for the page family
  vm_page_t *vm_page = allocate_vm_page(vm_page_family);

  // Check if page allocation is successful
  if (!vm_page)
  {
    return NULL;
  }

  // Add the new page to the free block list of the page family
  mm_add_free_block_meta_data_to_free_block_list(vm_page_family,
                                                 &vm_page->block_meta_data);

  return vm_page;
}

//-----------------< VMPage VM Page -----------------*/
vm_bool_t mm_is_vm_page_empty(vm_page_t *vm_page)
{
  if (vm_page != NULL)
  {
    // Check if all conditions for an empty page are met
    if (vm_page->block_meta_data.next_block == NULL &&
        vm_page->block_meta_data.prev_block == NULL &&
        vm_page->block_meta_data.is_free == MM_TRUE)
    {
      return MM_TRUE;
    }
  }
  return MM_FALSE;
}

/**
 * @brief Calculates the maximum allocatable memory in a page.
 *
 * This function calculates the maximum amount of memory that can be allocated
 * within a virtual memory page, accounting for the overhead of the page structure.
 *
 * @param units The number of system pages.
 * @return The maximum allocatable memory size in bytes.
 */
static inline uint32_t mm_max_page_allocatable_memory(int units)
{
  return (uint32_t)((SYSTEM_PAGE_SIZE * units) -
                    offset_of(vm_page_t, page_memory));
}

vm_page_t *allocate_vm_page(vm_page_family_t *vm_page_family)
{
  // Allocate memory for the new virtual memory page
  vm_page_t *vm_page = mm_get_new_vm_page_from_kernel(1);

  // If the virtual memory page is NULL, return NULL
  if (!vm_page)
  {
    return NULL;
  }

  // Initialize the lowermost metadata block of the VM page
  MARK_VM_PAGE_EMPTY(vm_page);

  // Set the block size and offset of the metadata block
  vm_page->block_meta_data.block_size = mm_max_page_allocatable_memory(1);
  vm_page->block_meta_data.offset = offset_of(vm_page_t, block_meta_data);

  // Initialize the priority thread glue
  init_glthread(&vm_page->block_meta_data.priority_thread_glue);

  // Initialize next and prev pointers of the page
  vm_page->next = NULL;
  vm_page->prev = NULL;

  // Set the back pointer to page family
  vm_page->pg_family = vm_page_family;

  // If it is the first VM data page for a given page family
  if (!vm_page_family->first_page)
  {
    vm_page_family->first_page = vm_page;
    return vm_page;
  }

  // Insert the new VM page to the head of the linked list
  vm_page->next = vm_page_family->first_page;
  vm_page_family->first_page->prev = vm_page;
  vm_page_family->first_page = vm_page;
  return vm_page;
}

/**
 * @brief Deletes and frees a virtual memory page.
 *
 * This function removes a virtual memory page from its page family and returns
 * the memory back to the kernel.
 *
 * @param vm_page The virtual memory page to delete and free.
 */
void mm_vm_page_delete_and_free(vm_page_t *vm_page)
{
  // Retrieve the page family of the virtual memory page
  vm_page_family_t *vm_page_family = vm_page->pg_family;

  // If the page being deleted is the head of the linked list
  if (vm_page_family->first_page == vm_page)
  {
    vm_page_family->first_page = vm_page->next;
    if (vm_page->next)
    {
      vm_page->next->prev = NULL;
    }
    vm_page->next = NULL;
    vm_page->prev = NULL;
    mm_return_vm_page_to_kernel((void *)vm_page, 1);
    return;
  }

  // If we are deleting the page from the middle or end of the linked list
  if (vm_page->next)
    vm_page->next->prev = vm_page->prev;
  vm_page->prev->next = vm_page->next;
  mm_return_vm_page_to_kernel((void *)vm_page, 1);
}

//-----------------< FreeVMPageBlock Free VM Page/Block -----------------/

/**
 * @brief Unions two adjacent free blocks into one.
 *
 * This function merges two adjacent free memory blocks into a single larger
 * free block to reduce fragmentation.
 *
 * @param first The first free block.
 * @param second The second free block adjacent to the first.
 */
static void mm_union_free_blocks(block_meta_data_t *first,
                                 block_meta_data_t *second)
{
  // Ensure that both blocks are free
  assert(first->is_free == MM_TRUE && second->is_free == MM_TRUE);

  // Check if the two blocks are contiguous
  if (first->next_block == second && second->prev_block == first)
  {
    // Merge the blocks by updating the size and pointers
    first->block_size += sizeof(block_meta_data_t) + second->block_size;
    first->next_block = second->next_block;

    // Update the previous block pointer of the next block if it exists
    if (second->next_block != NULL)
    {
      second->next_block->prev_block = first;
    }
  }
  else
  {
    // Error message if blocks are not contiguous
    printf("Error: mm_union_free_blocks - Attempting to merge non-contiguous "
           "free blocks\n");
  }
}

/**
 * @brief Comparison function for free blocks.
 *
 * This function compares two free blocks based on their sizes for priority
 * insertion.
 *
 * @param _block_meta_data1 Pointer to the first block metadata.
 * @param _block_meta_data2 Pointer to the second block metadata.
 * @return -1 if first is larger, 1 if second is larger, 0 if equal.
 */
static int free_blocks_comparison_function(void *_block_meta_data1,
                                           void *_block_meta_data2)
{
  block_meta_data_t *block_meta_data1 = (block_meta_data_t *)_block_meta_data1;
  block_meta_data_t *block_meta_data2 = (block_meta_data_t *)_block_meta_data2;

  if (block_meta_data1->block_size > block_meta_data2->block_size)
  {
    return -1;
  }
  else if (block_meta_data1->block_size < block_meta_data2->block_size)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief Adds free block metadata to the free block list.
 *
 * This function adds a free block's metadata to the priority list of free
 * blocks in the page family.
 *
 * @param vm_page_family The page family.
 * @param free_block The free block metadata to add.
 */
static void mm_add_free_block_meta_data_to_free_block_list(vm_page_family_t *vm_page_family,
                                                           block_meta_data_t *free_block)
{

  // Assert that the free_block is indeed marked as free
  assert(free_block->is_free == MM_TRUE);

  // Insert the free block metadata into the free block list of the virtual
  // memory page family
  glthread_priority_insert(&vm_page_family->free_block_priority_list_head,
                           &free_block->priority_thread_glue,
                           free_blocks_comparison_function,
                           offset_of(block_meta_data_t, priority_thread_glue));
}

/**
 * @brief Calculates hard internal memory fragmentation size.
 *
 * This function calculates the size of hard internal memory fragmentation
 * between two blocks.
 *
 * @param first The first block.
 * @param second The second block.
 * @return The fragmentation size.
 */
static int mm_get_hard_internal_memory_frag_size(block_meta_data_t *first,
                                                 block_meta_data_t *second)
{
  // Get the next block after the first block
  block_meta_data_t *next_block = NEXT_META_BLOCK_BY_SIZE(first);

  // Calculate the size of hard internal memory fragmentation
  return (int)((unsigned long)second - (unsigned long)(next_block));
}

/**
 * @brief Frees a block of memory.
 *
 * This function marks a block as free and attempts to merge it with adjacent
 * free blocks.
 *
 * @param to_be_free_block The block to be freed.
 * @return Pointer to the freed block.
 */
static block_meta_data_t *mm_free_blocks(block_meta_data_t *to_be_free_block)
{
  block_meta_data_t *return_block = NULL; /// 1 Pointer to the freed block
  assert(to_be_free_block->is_free == MM_FALSE);

  // Retrieving hosting page and page family
  vm_page_t *hosting_page = MM_GET_PAGE_FROM_META_BLOCK(to_be_free_block);

  // Setting return_block to the block being freed
  return_block = to_be_free_block;
  to_be_free_block->is_free = MM_TRUE; /// 2 Marking the block as free

  block_meta_data_t *next_block =
      NEXT_META_BLOCK(to_be_free_block); /// 3 Next block pointer

  // Handling Hard IF memory
  if (next_block)
  {
    // Scenario 1: When data block to be freed is not the last uppermost meta
    // block in a VM data page
    to_be_free_block->block_size +=
        mm_get_hard_internal_memory_frag_size(to_be_free_block, next_block);
  }
  else
  {
    // Scenario 2: Page Boundary condition
    // Block being freed is the uppermost free data block in a VM data page,
    // checking for hard internal fragmented memory and merge
    char *end_address_of_vm_page =
        (char *)((char *)hosting_page + SYSTEM_PAGE_SIZE);
    char *end_address_of_free_data_block =
        (char *)(to_be_free_block + 1) + to_be_free_block->block_size;
    int internal_mem_fragmentation =
        (int)((unsigned long)end_address_of_vm_page -
              (unsigned long)end_address_of_free_data_block);
    to_be_free_block->block_size += internal_mem_fragmentation;
  }

  // Performing merging with next block if it's free
  if (next_block && next_block->is_free == MM_TRUE)
  {
    mm_union_free_blocks(to_be_free_block,
                         next_block); /// 4 Union two free blocks
    return_block = to_be_free_block;
  }

  // Checking the previous block if it was free and merging if necessary
  block_meta_data_t *prev_block = PREV_META_BLOCK(to_be_free_block);
  if (prev_block && prev_block->is_free)
  {
    mm_union_free_blocks(prev_block, to_be_free_block);
    return_block = prev_block;
  }

  // Checking if the hosting page becomes empty after freeing this block
  if (mm_is_vm_page_empty(hosting_page))
  {
    mm_vm_page_delete_and_free(
        hosting_page); /// 5 Delete and free the hosting page
    return NULL;
  }

  // Adding the freed block metadata to the free block list
  mm_add_free_block_meta_data_to_free_block_list(hosting_page->pg_family,
                                                 return_block);

  return return_block;
}

/**
 * @brief Frees allocated memory.
 *
 * This function frees memory previously allocated by xmalloc or xcalloc.
 *
 * @param app_data Pointer to the memory to be freed.
 */
void xfree(void *app_data)
{
  // Adjust the pointer to point to the block metadata
  block_meta_data_t *block_meta_data =
      (block_meta_data_t *)((char *)app_data - sizeof(block_meta_data_t));

  // Ensure that the block is not already free
  assert(block_meta_data->is_free == MM_FALSE);

  // Call the memory manager's free blocks function
  mm_free_blocks(block_meta_data);
}

//-----------------<  Memory allocation section -----------------/
static block_meta_data_t *
mm_allocate_free_data_block(vm_page_family_t *vm_page_family,
                            uint32_t req_size)
{

  vm_bool_t status;
  vm_page_t *vm_page = NULL;

  // Get the biggest free block in the page family
  block_meta_data_t *biggest_block_meta_data =
      mm_get_biggest_free_block_page_family(vm_page_family);

  // Check if there is no available block or if the available block is too small
  if (!biggest_block_meta_data ||
      biggest_block_meta_data->block_size < req_size)
  {

    // Add a new page to the page family
    vm_page = mm_family_new_page_add(vm_page_family);

    // Allocate the free block from the new page
    status = mm_split_free_data_block_for_allocation(
        vm_page_family, &vm_page->block_meta_data, req_size);

    // Return the allocated block's metadata if successful
    if (status)
    {
      return &vm_page->block_meta_data;
    }
    return NULL;
  }

  // Attempt to split the biggest free block to satisfy the allocation request
  status = mm_split_free_data_block_for_allocation(
      vm_page_family, biggest_block_meta_data, req_size);

  // Return the allocated block's metadata if successful
  if (status)
  {
    return biggest_block_meta_data;
  }

  return NULL;
}

static inline block_meta_data_t *
mm_get_biggest_free_block_page_family(vm_page_family_t *vm_page_family)
{
  // Retrieve the right pointer of the free_block_priority_list_head in the
  // vm_page_family
  glthread_t *biggest_free_block_glue =
      vm_page_family->free_block_priority_list_head.right;

  // If a block exists in the priority list, return its metadata
  if (biggest_free_block_glue)
  {
    return glthread_to_block_meta_data(biggest_free_block_glue);
  }

  // If the priority list is empty, return NULL
  return NULL;
}

static vm_bool_t
mm_split_free_data_block_for_allocation(vm_page_family_t *vm_page_family,
                                        block_meta_data_t *block_meta_data,
                                        uint32_t size)
{

  block_meta_data_t *next_block_meta_data = NULL;

  // Assert that the provided block is free
  assert(block_meta_data->is_free == MM_TRUE);

  // Check if the block size is sufficient for allocation
  if (block_meta_data->block_size < size)
  {
    return MM_FALSE;
  }

  // Calculate the remaining size after allocation
  uint32_t remaining_size = block_meta_data->block_size - size;

  // Update metadata for the allocated portion
  block_meta_data->is_free = MM_FALSE;
  block_meta_data->block_size = size;
  remove_glthread(&block_meta_data->priority_thread_glue);

  // Case 1: No Split
  if (!remaining_size)
  {
    return MM_TRUE;
  }

  // Case 3-1: Partial Split - Soft Internal Fragmentation
  else if (sizeof(block_meta_data_t) < remaining_size &&
           remaining_size <
               (sizeof(block_meta_data_t) + vm_page_family->struct_size))
  {
    // Create a new metadata block for the remaining space
    next_block_meta_data = NEXT_META_BLOCK_BY_SIZE(block_meta_data);
    next_block_meta_data->is_free = MM_TRUE;
    next_block_meta_data->block_size =
        remaining_size - sizeof(block_meta_data_t);
    next_block_meta_data->offset = block_meta_data->offset +
                                   sizeof(block_meta_data_t) +
                                   block_meta_data->block_size;
    init_glthread(&next_block_meta_data->priority_thread_glue);
    mm_add_free_block_meta_data_to_free_block_list(vm_page_family,
                                                   next_block_meta_data);
    mm_bind_blocks_for_allocation(block_meta_data, next_block_meta_data);
  }

  // Case 3-2: Partial Split - Hard Internal Fragmentation
  else if (remaining_size < sizeof(block_meta_data_t))
  {
    // No need to do anything
  }

  // Case 2: Full Split - New Metadata Block Created
  else
  {
    // Create a new metadata block for the remaining space
    next_block_meta_data = NEXT_META_BLOCK_BY_SIZE(block_meta_data);
    next_block_meta_data->is_free = MM_TRUE;
    next_block_meta_data->block_size =
        remaining_size - sizeof(block_meta_data_t);
    next_block_meta_data->offset = block_meta_data->offset +
                                   sizeof(block_meta_data_t) +
                                   block_meta_data->block_size;
    init_glthread(&next_block_meta_data->priority_thread_glue);
    mm_add_free_block_meta_data_to_free_block_list(vm_page_family,
                                                   next_block_meta_data);
    mm_bind_blocks_for_allocation(block_meta_data, next_block_meta_data);
  }

  return MM_TRUE;
}

/**
 * @brief Allocates and initializes memory for an array.
 *
 * This function allocates memory for an array of structures and initializes
 * it to zero.
 *
 * @param struct_name The name of the structure type.
 * @param units The number of units to allocate.
 * @return Pointer to the allocated memory, or NULL if allocation fails.
 */
void *xcalloc(char *struct_name, int units)
{
  // Initialize variables
  char data_type[MAX_STRUCT_NAME_LEN];
  uint8_t data_type_error_flag = 0;
  vm_page_family_t *pg_family = NULL;

  // Parse the struct name and set the data type error
  parse_struct_name(struct_name, data_type, &data_type_error_flag);

  // Check if there was an error parsing the struct name
  if (data_type_error_flag == 1)
  {
    // Step 1: Look up the page family associated with the structure name
    pg_family = lookup_page_family_by_name(struct_name);
  }
  else
  {
    // Step 1: Look up the page family associated with the data type
    pg_family = lookup_page_family_by_name(data_type);
  }

  // If the page family is not registered, register it
  if (!pg_family && (!data_type_error_flag || data_type_error_flag == 2))
  {
    mm_instantiate_new_page_family(data_type, get_size_of_datatype(data_type));
    pg_family = lookup_page_family_by_name(data_type);
  }
  else if (!pg_family)
  {
    printf("Error: Structure %s not registered with Memory Manager\n",
           struct_name);
    return NULL;
  }

  if (data_type_error_flag == 2)
  {
    pg_family->struct_size = atoi(struct_name);
  }
  else
  {
    pg_family->struct_size = get_size_of_datatype(data_type);
  }

  // Check if the requested memory size exceeds the maximum allocatable memory
  // per page
  if (units * pg_family->struct_size > MAX_PAGE_ALLOCATABLE_MEMORY(1))
  {
    printf("Error: Memory requested exceeds page size\n");
    return NULL;
  }

  // Find a free block in the page family to satisfy the allocation request
  block_meta_data_t *free_block_meta_data =
      mm_allocate_free_data_block(pg_family, units * pg_family->struct_size);

  // Check if the allocation was successful
  if (free_block_meta_data)
  {
    // Initialize the allocated memory to zero
    memset((char *)(free_block_meta_data + 1), 0,
           free_block_meta_data->block_size);
    // Return a pointer to the allocated memory
    return (void *)(free_block_meta_data + 1);
  }

  // Return NULL if the allocation failed
  return NULL;
}

//-----------------< Printing information section -----------------/

/**
 * @brief Prints registered page families.
 *
 * This function prints information about all registered page families.
 */
void mm_print_registered_page_families()
{
  vm_page_family_t *vm_page_family_curr =
      NULL;                             // Pointer to the current page family
  char struct_name[MM_MAX_STRUCT_NAME]; // Buffer to store the name of the
  // structure
  uint32_t struct_size; // Size of the structure

  // Check if there are no registered page families
  if (first_vm_page_for_families == NULL)
  {
    printf("No page families registered for printing.\n");
  }
  else
  {
    // Pointer to iterate over virtual memory pages
    vm_page_for_families_t *current_page = first_vm_page_for_families;

    // Iterate over all virtual memory pages containing page families
    do
    {
      ITERATE_PAGE_FAMILIES_BEGIN(current_page, vm_page_family_curr)
      {
        // Copy the name and size of the structure from the current page family
        strncpy(struct_name, vm_page_family_curr->struct_name,
                MM_MAX_STRUCT_NAME);
        struct_size = vm_page_family_curr->struct_size;

        // Print information about the page family
        printf("Page Family: %s, Size: %d\n", struct_name, struct_size);
      }
      ITERATE_PAGE_FAMILIES_END(current_page, vm_page_family_curr);

      // Move to the next virtual memory page
      current_page = current_page->next;
    } while (current_page != NULL);
  }
}

/**
 * @brief Prints block usage information.
 *
 * This function prints detailed information about memory block usage across
 * all page families.
 */
void mm_print_block_usage()
{
  vm_page_t *vm_page_curr;
  vm_page_family_t *vm_page_family_curr;
  block_meta_data_t *block_meta_data_curr;
  uint32_t total_block_count, free_block_count, occupied_block_count;
  uint32_t application_memory_usage;

  // Iterate over page families
  ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr)
  {
    // Initialize counters
    total_block_count = 0;
    free_block_count = 0;
    application_memory_usage = 0;
    occupied_block_count = 0;

    // Iterate over virtual memory pages
    ITERATE_VM_PAGE_BEGIN(vm_page_family_curr, vm_page_curr)
    {
      // Iterate over all blocks within the page
      ITERATE_VM_PAGE_ALL_BLOCKS_BEGIN(vm_page_curr, block_meta_data_curr)
      {
        // Increment total block count
        total_block_count++;

        // Perform sanity checks
        if (block_meta_data_curr->is_free == MM_FALSE)
        {
          assert(IS_GLTHREAD_LIST_EMPTY(
              &block_meta_data_curr->priority_thread_glue));
        }
        if (block_meta_data_curr->is_free == MM_TRUE)
        {
          assert(!IS_GLTHREAD_LIST_EMPTY(
              &block_meta_data_curr->priority_thread_glue));
        }

        // Update counts based on block status
        if (block_meta_data_curr->is_free == MM_TRUE)
        {
          free_block_count++;
        }
        else
        {
          application_memory_usage +=
              block_meta_data_curr->block_size + sizeof(block_meta_data_t);
          occupied_block_count++;
        }
      }
      ITERATE_VM_PAGE_ALL_BLOCKS_END(vm_page_curr, block_meta_data_curr);
    }
    ITERATE_VM_PAGE_END(vm_page_family_curr, vm_page_curr);

    // Print block usage information for the current page family
    printf("%-20s   TBC : %-4u    FBC : %-4u    OBC : %-4u AppMemUsage : %u\n",
           vm_page_family_curr->struct_name, total_block_count,
           free_block_count, occupied_block_count, application_memory_usage);
  }
  ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families, vm_page_family_curr);
}

/**
 * @brief Prints details of a virtual memory page.
 *
 * This function prints detailed information about a specific virtual memory
 * page, including its blocks.
 *
 * @param vm_page The virtual memory page to print details for.
 */
void mm_print_vm_page_details(vm_page_t *vm_page)
{
  printf("\t\t next = %p, prev = %p\n", vm_page->next, vm_page->prev);
  printf("\t\t page family = %s\n", vm_page->pg_family->struct_name);

  uint32_t j = 0;
  block_meta_data_t *curr;

  // Iterate over all blocks within the virtual memory page
  ITERATE_VM_PAGE_ALL_BLOCKS_BEGIN(vm_page, curr)
  {
    printf("\t\t\t%-14p Block %-3u %s  block_size = %-6u  "
           "offset = %-6u  prev = %-14p  next = %p\n",
           curr, j++, curr->is_free ? "F R E E D" : "ALLOCATED",
           curr->block_size, curr->offset, curr->prev_block, curr->next_block);
  }
  ITERATE_VM_PAGE_ALL_BLOCKS_END(vm_page, curr);
}

/**
 * @brief Prints memory usage for a structure type.
 *
 * This function prints memory usage statistics for a specific structure type.
 *
 * @param struct_name The name of the structure type.
 */
void mm_print_memory_usage(char *struct_name)
{
  vm_page_t *vm_page = NULL;
  vm_page_family_t *vm_page_family_curr;
  uint32_t number_of_struct_families = 0;
  uint32_t cumulative_vm_pages_claimed_from_kernel = 0;

  // Print page size
  printf("\nPage Size = %zu Bytes\n", SYSTEM_PAGE_SIZE);

  // Iterate over each virtual memory page family
  ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr)
  {
    if (struct_name)
    {
      // Filter output by structure name if specified
      if (strncmp(struct_name, vm_page_family_curr->struct_name,
                  strlen(vm_page_family_curr->struct_name)) != 0)
      {
        continue;
      }
    }

    // Increment number of structure families processed
    number_of_struct_families++;

    // Print details of each virtual memory page family
    printf(ANSI_COLOR_GREEN
           "vm_page_family : %s, struct size = %u\n" ANSI_COLOR_RESET,
           vm_page_family_curr->struct_name, vm_page_family_curr->struct_size);

    // Iterate over each virtual memory page within the family
    ITERATE_VM_PAGE_BEGIN(vm_page_family_curr, vm_page)
    {
      cumulative_vm_pages_claimed_from_kernel++;
      mm_print_vm_page_details(vm_page);
    }
    ITERATE_VM_PAGE_END(vm_page_family_curr, vm_page);
    printf("\n");
  }
  ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families, vm_page_family_curr);

  // Print total number of VM pages in use and their total memory usage
  printf(ANSI_COLOR_MAGENTA
         "# Of VM Pages in Use : %u (%lu Bytes)\n" ANSI_COLOR_RESET,
         cumulative_vm_pages_claimed_from_kernel,
         SYSTEM_PAGE_SIZE * cumulative_vm_pages_claimed_from_kernel);

  // Print total memory being used by the Memory Manager
  printf("Total Memory being used by Memory Manager = %lu Bytes\n",
         cumulative_vm_pages_claimed_from_kernel * SYSTEM_PAGE_SIZE);
}
