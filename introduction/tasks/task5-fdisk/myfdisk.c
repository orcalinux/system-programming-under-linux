/*****************************************************************************************/
/******************* Author    : Mahmoud Abdelraouf Mahmoud ******************************/
/******************* Date      : 19 Feb 2024                ******************************/
/******************* Version   : 0.1                        ******************************/
/******************* File Name : myfdisk.c                  ******************************/
/*****************************************************************************************/

/***********************************< Include Section ***********************************/
#include "myfdisk.h"

/***********************************< Main Function ***********************************/
int main(int argc, char **argv) {
    /**< Check if the number of arguments is correct */
    if (argc != 2) {
        printf("Usage: %s <device_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    read_partition_table(argv[1]);

    return EXIT_SUCCESS;
}

/***********************************< Function Definitions ***********************************/
void process_partition_table(char *device, uint8_t partition_number, PartitionEntry *table_entry_ptr) {
    /**< Print the details of each partition entry */ 
    printf("%-8s%-4d  %-4c %-10u %-10u %-10u %06.2fG %5X\n",
           device,                                                       /**< Device name */ 
           partition_number + 1,                                         /**< Partition number */ 
           table_entry_ptr->status == 0x80 ? '*' : ' ',                  /**< Boot flag */ 
           table_entry_ptr->lba,                                         /**< Start sector */ 
           table_entry_ptr->lba + table_entry_ptr->sector_count - 1,     /**< End sector */ 
           table_entry_ptr->sector_count,                                /**< Number of sectors */ 
           (double)table_entry_ptr->sector_count * SECTOR_SIZE / (1024 * 1024 * 1024), /**< Size in GB */ 
           table_entry_ptr->partition_type);                             /**< Partition type */ 
}

void read_ebr_partition_table(char *device, uint32_t ebr_lba, uint32_t original_ebr_lba, int ebr_number) {
    char buf[SECTOR_SIZE];  /**< Buffer to store the read data from the disk */ 

    /**< Open the disk device file for reading */ 
    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    /**< Read the EBR from the disk into the buffer */ 
    off64_t file_offset = ((off64_t)(ebr_lba)) * SECTOR_SIZE; /**< Calculate the offset for lseek64 */ 
    off64_t current_offset = lseek64(fd, file_offset, SEEK_SET); /**< Move to the position of the EBR */ 
    if (current_offset != file_offset) {
        perror("Error seeking file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    
    ssize_t bytes_read = read(fd, buf, SECTOR_SIZE);
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /**< Pointer to the partition table entries within the buffer */ 
    PartitionEntry *table_entry_ptr = ((PartitionEntry *) &buf[446]);
    table_entry_ptr[0].lba += ebr_lba;

    /**< Process the first partition entry in the EBR */
    process_partition_table(device, ebr_number, &table_entry_ptr[0]);
    
    /**< Close the file descriptor */ 
    close(fd);
    
    /**< Check if there are additional EBRs to process */
    if (table_entry_ptr[1].sector_count > 0) {
        /**< Calculate the offset for the next EBR */
        uint32_t next_ebr_lba = original_ebr_lba + table_entry_ptr[1].lba;
        read_ebr_partition_table(device, next_ebr_lba, original_ebr_lba, ebr_number + 1);
    }

}

void read_partition_table(char *device) {
    char buf[SECTOR_SIZE];  /**< Buffer to store the read data from the disk */ 

    /**< Open the disk device file for reading */ 
    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    /**< Read the first 512 bytes (MBR) from the disk into the buffer */ 
    ssize_t bytes_read = read(fd, buf, SECTOR_SIZE);
    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /**< Pointer to the partition table entries within the buffer */ 
    PartitionEntry *table_entry_ptr = ((PartitionEntry *) &buf[446]);

    /**< Print the header for the partition table information with bold text */ 
    printf("\033[1m%-10s %5s   %-10s %-10s %-10s %-10s %-5s %-5s\033[0m\n", "Device",
           "Boot", "Start", "End", "Sectors", "Size", "Id", "Type");

    /**< Iterate over each partition entry in the partition table */ 
    for (int i = 0; i < 4; i++) {
        /**< Print the details of each partition entry */ 
        process_partition_table(device, i, &table_entry_ptr[i]);
        if (table_entry_ptr[i].partition_type == 0x05 && table_entry_ptr[i].sector_count > 0) {
            /**< If the partition type is 0x05 (Extended Partition), read the EBR partition table */ 
            read_ebr_partition_table(device, table_entry_ptr[i].lba, table_entry_ptr[i].lba, 4);
        }
    }

    /**< Close the file descriptor */ 
    close(fd);
}
