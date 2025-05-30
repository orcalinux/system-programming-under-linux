# myfdisk

## Overview
`myfdisk` is a simple yet powerful tool designed for reading and displaying partition table information of a disk device on UNIX-like systems. It supports parsing both Master Boot Record (MBR) and Extended Boot Record (EBR) partition tables, providing detailed insights into each partition.

## Features
- Parses and displays partition table details, including device name, boot flag, start and end sectors, number of sectors, size, ID, and type.
- Supports printing partition sizes in various units, including megabytes (MB) and gigabytes (GB).
- Recursively reads and processes EBR partition tables for logical partitions within extended partitions.
- Provides a clean and user-friendly output format suitable for both casual users and system administrators.

## Files
- `myfdisk.c`: The main source code file containing the implementation of `myfdisk`.
- `myfdisk.h`: The header file containing function prototypes and structure definitions used in `myfdisk.c`.

## Functionality
- `process_partition_table`: Function to process and print the details of a partition entry.
- `read_ebr_partition_table`: Function to recursively read and process the extended boot record (EBR) partition table.
- `read_partition_table`: Function to read and process the partition table of a disk device.

## How to Use
1. Clone or download the `myfdisk` repository to your local machine.
2. Compile the `myfdisk` source code using a C compiler. For example:
    ```bash
    gcc -o myfdisk myfdisk.c
    ```
3. Run `myfdisk` with the disk device file as an argument. For example:
    ```bash
    ./myfdisk /dev/sda
    ```

## Example Output
```
Device    Boot   Start      End        Sectors    Size      Id    Type
/dev/sda1 *      2048       1026047    1024000    500.00M   07    NTFS
/dev/sda2        1026048    82180095   81154048   38.74G    83    Linux
/dev/sda3        82180096   200488703  118308608  56.43G    05    Extended
/dev/sda5        82182144   100888575  18606432   8.88G     83    Linux
/dev/sda6        100890624  200488703  99648080   47.51G    83    Linux
```

## Notes
- Ensure you have the necessary permissions to read the disk device file (usually requires root privileges).
- This tool is for informational purposes only and does not modify the disk or its partitions.
- Contributions and feedback are welcome. Feel free to submit issues or pull requests on the project repository.

## Author
- Mahmoud Abdelraouf Mahmoud

## Version
- 1.0.0

## License
This project is licensed under the MIT License - see the [LICENSE](../../LICENSE) file for details.
