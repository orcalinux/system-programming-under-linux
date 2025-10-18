# VariadicCommandProcessor

**VariadicCommandProcessor** is a C project that demonstrates the use of variadic functions to implement a dynamic command processor and a multi-threaded logging system. This project showcases advanced usage of variadic functions, including dynamic logging, command registration, and execution in a flexible and modular system.

## Table of Contents

- [VariadicCommandProcessor](#variadiccommandprocessor)
  - [Table of Contents](#table-of-contents)
  - [Project Overview](#project-overview)
  - [Project Structure](#project-structure)
  - [Features](#features)
  - [Build and Run](#build-and-run)
    - [Prerequisites](#prerequisites)
    - [Build](#build)
    - [Run](#run)
    - [Clean](#clean)
  - [Usage](#usage)
  - [Configuration](#configuration)
  - [Contributing](#contributing)
  - [License](#license)

## Project Overview

The **VariadicCommandProcessor** project demonstrates how to effectively use variadic functions in a C application. It includes:

- **Dynamic Logging System**: A multi-threaded logging system that uses variadic functions to handle variable-length log messages.
- **Command Processor**: A flexible command processor that allows dynamic registration and execution of commands, each accepting a variable number of arguments.
- **Utilities**: A set of utility functions that can be registered as commands, including sum, maximum, and minimum calculations.

## Project Structure

The project is organized into several directories to separate source code, headers, and configuration files.

```plaintext
VariadicCommandProcessor/
│
├── src/
│   ├── main.c                 # Main entry point of the application
│   ├── command_processor.c     # Implementation of the command processor
│   ├── dynamic_logger.c        # Implementation of the dynamic logging system
│   └── utils.c                 # Implementation of utility functions
│
├── include/
│   ├── command_processor.h     # Header for the command processor
│   ├── dynamic_logger.h        # Header for the dynamic logging system
│   └── utils.h                 # Header for the utility functions
│
├── config/
│   └── project_config.h        # Project configuration file
│
├── README_Complex_Variadic_Functions_in_C.md  # This README file
└── Makefile                    # Makefile for building the project
```

## Features

- **Thread-Safe Logging**: The project includes a thread-safe logging mechanism that ensures safe logging operations in multi-threaded environments.
- **Command Registration**: Commands can be dynamically registered at runtime, allowing for a flexible and extensible command set.
- **Utility Functions**: The project includes basic utility functions such as calculating the sum, maximum, and minimum of a list of numbers.

## Build and Run

### Prerequisites

- **GCC**: Ensure that GCC is installed on your system.
- **Make**: The project uses a `Makefile` to simplify the build process.

### Build

1. **Navigate to the Project Directory:**

   ```sh
   cd VariadicCommandProcessor
   ```

2. **Build the Project:**

   Run the following command to compile the project using the `Makefile`:

   ```sh
   make
   ```

   This command compiles the source files and links them into an executable named `VariadicCommandProcessor`.

### Run

After building the project, you can run the executable:

```sh
./variadic-command-processor
```

### Clean

To remove the compiled object files and executable, run:

```sh
make clean
```

## Usage

After running the executable, the program will:

1. Initialize the logging system.
2. Register a set of commands (`sum`, `max`, and `min`).
3. Execute these commands with different sets of arguments.
4. List all registered commands.
5. Cleanup the logging system before exiting.

The results of the commands and the logging output will be displayed in the terminal and written to the `project_log.txt` file.

## Configuration

The project’s behavior can be adjusted by modifying the configuration file located in `config/project_config.h`. Key configuration options include:

- **`LOG_BUFFER_SIZE`**: Controls the size of the buffer used for log messages.
- **`MAX_COMMANDS`**: Limits the number of commands that can be registered.
- **`LOG_FILE_NAME`**: Specifies the name of the log file.
- **`ENABLE_THREAD_SAFE_LOGGING`**: Enables or disables thread-safe logging.
- **`DEFAULT_COMMAND_NAME_LENGTH`**: Sets the maximum length for command names.

These configurations allow you to tailor the project to your specific needs and environment.

## Contributing

If you'd like to contribute to the project, please fork the repository, create a new branch, and submit a pull request. Contributions are welcome, especially for new features, bug fixes, and improvements to existing code.

## License

This project is open-source and available under the GPL-3.0 License. See the `LICENSE` file for more details.
