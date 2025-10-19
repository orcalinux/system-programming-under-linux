.PHONY: clean_all clean_obj clean_doc doc

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# List of Source files
SRC = $(wildcard src/*.c)

# List of header files
HDR = $(wildcard include/*.h)

# List of Source files except the memory_manager_test
LIB_SRC = $(filter-out src/memory_manager_test.c, $(wildcard src/*.c))

# List of object files
OBJ = $(SRC:src/%.c=bin/%.o)

# List of object files for shared build
OBJ_SHARED = $(LIB_SRC:src/%.c=bin/%_shared.o)

# List of object files for static build
OBJ_STATIC = $(LIB_SRC:src/%.c=bin/%_static.o)

# Name of the executable
TARGET = bin/hmm

# Name of the static library
STATIC_LIB = lib/lib$(TARGET).a

# Name of the shared library
SHARED_LIB = lib/lib$(TARGET).so

# Command to remove files
RM = rm -f

# Default target
all: $(TARGET)

# Rules to link object files and create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
	$(RM) $(OBJ)

# Static library target
static: $(OBJ_STATIC)
	ar rcs $(STATIC_LIB) $(OBJ_STATIC)
	$(RM) $(OBJ_STATIC)

# Shared library target
shared: $(OBJ_SHARED)
	$(CC) -shared -o $(SHARED_LIB) $(OBJ_SHARED)
	$(RM) $(OBJ_SHARED)

# Rule to compile C source files into object files
bin/%.o: src/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C source files to object files for shared build
bin/%_shared.o: src/%.c $(HDR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Rule to compile C source files to object files for static build
bin/%_static.o: src/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean_all:
	$(RM) -rf bin/* lib/* html latex man

# Clean object files
clean_obj:
	$(RM) bin/*.o bin/*_shared.o bin/*_static.o

# Generate documentation
doc:
	doxygen Doxyfile

# Clean documentation
clean_doc:
	$(RM) -rf html latex man

