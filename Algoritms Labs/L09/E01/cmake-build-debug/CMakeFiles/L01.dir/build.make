# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/stefano/clion-2017.2.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/stefano/clion-2017.2.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stefano/Documenti/Algoritmi/Lab/L09/L01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/L01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/L01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/L01.dir/flags.make

CMakeFiles/L01.dir/main.c.o: CMakeFiles/L01.dir/flags.make
CMakeFiles/L01.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/L01.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/L01.dir/main.c.o   -c /home/stefano/Documenti/Algoritmi/Lab/L09/L01/main.c

CMakeFiles/L01.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/L01.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stefano/Documenti/Algoritmi/Lab/L09/L01/main.c > CMakeFiles/L01.dir/main.c.i

CMakeFiles/L01.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/L01.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stefano/Documenti/Algoritmi/Lab/L09/L01/main.c -o CMakeFiles/L01.dir/main.c.s

CMakeFiles/L01.dir/main.c.o.requires:

.PHONY : CMakeFiles/L01.dir/main.c.o.requires

CMakeFiles/L01.dir/main.c.o.provides: CMakeFiles/L01.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/L01.dir/build.make CMakeFiles/L01.dir/main.c.o.provides.build
.PHONY : CMakeFiles/L01.dir/main.c.o.provides

CMakeFiles/L01.dir/main.c.o.provides.build: CMakeFiles/L01.dir/main.c.o


CMakeFiles/L01.dir/BST.c.o: CMakeFiles/L01.dir/flags.make
CMakeFiles/L01.dir/BST.c.o: ../BST.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/L01.dir/BST.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/L01.dir/BST.c.o   -c /home/stefano/Documenti/Algoritmi/Lab/L09/L01/BST.c

CMakeFiles/L01.dir/BST.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/L01.dir/BST.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stefano/Documenti/Algoritmi/Lab/L09/L01/BST.c > CMakeFiles/L01.dir/BST.c.i

CMakeFiles/L01.dir/BST.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/L01.dir/BST.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stefano/Documenti/Algoritmi/Lab/L09/L01/BST.c -o CMakeFiles/L01.dir/BST.c.s

CMakeFiles/L01.dir/BST.c.o.requires:

.PHONY : CMakeFiles/L01.dir/BST.c.o.requires

CMakeFiles/L01.dir/BST.c.o.provides: CMakeFiles/L01.dir/BST.c.o.requires
	$(MAKE) -f CMakeFiles/L01.dir/build.make CMakeFiles/L01.dir/BST.c.o.provides.build
.PHONY : CMakeFiles/L01.dir/BST.c.o.provides

CMakeFiles/L01.dir/BST.c.o.provides.build: CMakeFiles/L01.dir/BST.c.o


CMakeFiles/L01.dir/Item.c.o: CMakeFiles/L01.dir/flags.make
CMakeFiles/L01.dir/Item.c.o: ../Item.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/L01.dir/Item.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/L01.dir/Item.c.o   -c /home/stefano/Documenti/Algoritmi/Lab/L09/L01/Item.c

CMakeFiles/L01.dir/Item.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/L01.dir/Item.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stefano/Documenti/Algoritmi/Lab/L09/L01/Item.c > CMakeFiles/L01.dir/Item.c.i

CMakeFiles/L01.dir/Item.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/L01.dir/Item.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stefano/Documenti/Algoritmi/Lab/L09/L01/Item.c -o CMakeFiles/L01.dir/Item.c.s

CMakeFiles/L01.dir/Item.c.o.requires:

.PHONY : CMakeFiles/L01.dir/Item.c.o.requires

CMakeFiles/L01.dir/Item.c.o.provides: CMakeFiles/L01.dir/Item.c.o.requires
	$(MAKE) -f CMakeFiles/L01.dir/build.make CMakeFiles/L01.dir/Item.c.o.provides.build
.PHONY : CMakeFiles/L01.dir/Item.c.o.provides

CMakeFiles/L01.dir/Item.c.o.provides.build: CMakeFiles/L01.dir/Item.c.o


# Object files for target L01
L01_OBJECTS = \
"CMakeFiles/L01.dir/main.c.o" \
"CMakeFiles/L01.dir/BST.c.o" \
"CMakeFiles/L01.dir/Item.c.o"

# External object files for target L01
L01_EXTERNAL_OBJECTS =

L01: CMakeFiles/L01.dir/main.c.o
L01: CMakeFiles/L01.dir/BST.c.o
L01: CMakeFiles/L01.dir/Item.c.o
L01: CMakeFiles/L01.dir/build.make
L01: CMakeFiles/L01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable L01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/L01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/L01.dir/build: L01

.PHONY : CMakeFiles/L01.dir/build

CMakeFiles/L01.dir/requires: CMakeFiles/L01.dir/main.c.o.requires
CMakeFiles/L01.dir/requires: CMakeFiles/L01.dir/BST.c.o.requires
CMakeFiles/L01.dir/requires: CMakeFiles/L01.dir/Item.c.o.requires

.PHONY : CMakeFiles/L01.dir/requires

CMakeFiles/L01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/L01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/L01.dir/clean

CMakeFiles/L01.dir/depend:
	cd /home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stefano/Documenti/Algoritmi/Lab/L09/L01 /home/stefano/Documenti/Algoritmi/Lab/L09/L01 /home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug /home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug /home/stefano/Documenti/Algoritmi/Lab/L09/L01/cmake-build-debug/CMakeFiles/L01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/L01.dir/depend
