/*****************************************************************************************/
/******************* Author    : Mahmoud Abdelraouf Mahmoud ******************************/
/******************* Date      : 19 Feb 2024                ******************************/
/******************* Version   : 0.1                        ******************************/
/******************* File Name : myfdisk.h                  ******************************/
/*****************************************************************************************/
#ifndef MYFDISK_H_
#define MYFDISK_H_

/***********************************< Includes ***********************************/
#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

/***********************************< Definitions ***********************************/
#define SECTOR_SIZE 512

/***********************************< Structures ***********************************/
/**
 * @brief Structure representing a partition entry.
 */
typedef struct {
    uint8_t status;             /**< Status of the partition (e.g., active or inactive) */
    uint8_t first_chs[3];       /**< CHS (Cylinder-Head-Sector) address of the first sector in the partition */
    uint8_t partition_type;     /**< Type of the partition (e.g., FAT32, NTFS) */
    uint8_t last_chs[3];        /**< CHS address of the last sector in the partition */
    uint32_t lba;               /**< Logical block address of the first sector in the partition */
    uint32_t sector_count;      /**< Number of sectors in the partition */
} PartitionEntry;

/***********************************< Function Prototypes ***********************************/
/**
 * @brief Process and print the details of a partition entry.
 *
 * @param device The name of the device.
 * @param partition_number The partition number.
 * @param table_entry_ptr Pointer to the partition entry.
 * @private This function is private and should not be used externally.
 */
static void process_partition_table(char *device, uint8_t partition_number, PartitionEntry *table_entry_ptr);

/**
 * @brief Read and process the extended boot record (EBR) partition table recursively.
 *
 * @param device The name of the device.
 * @param ebr_lba Logical block address of the EBR.
 * @param original_ebr_lba Original logical block address of the EBR.
 * @param ebr_number The EBR number.
 * @private This function is private and should not be used externally.
 */
static void read_ebr_partition_table(char *device, uint32_t ebr_lba, uint32_t original_ebr_lba, int ebr_number);

/**
 * @brief Read and process the partition table.
 *
 * @param device The name of the device.
 * @public This function is public and can be used externally.
 */
void read_partition_table(char *device);

#endif /**< MYFDISK_H_ */

