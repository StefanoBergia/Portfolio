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
CMAKE_SOURCE_DIR = /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/E03G.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/E03G.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/E03G.dir/flags.make

CMakeFiles/E03G.dir/main.c.o: CMakeFiles/E03G.dir/flags.make
CMakeFiles/E03G.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/E03G.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/E03G.dir/main.c.o   -c /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/main.c

CMakeFiles/E03G.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/E03G.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/main.c > CMakeFiles/E03G.dir/main.c.i

CMakeFiles/E03G.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/E03G.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/main.c -o CMakeFiles/E03G.dir/main.c.s

CMakeFiles/E03G.dir/main.c.o.requires:

.PHONY : CMakeFiles/E03G.dir/main.c.o.requires

CMakeFiles/E03G.dir/main.c.o.provides: CMakeFiles/E03G.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/E03G.dir/build.make CMakeFiles/E03G.dir/main.c.o.provides.build
.PHONY : CMakeFiles/E03G.dir/main.c.o.provides

CMakeFiles/E03G.dir/main.c.o.provides.build: CMakeFiles/E03G.dir/main.c.o


# Object files for target E03G
E03G_OBJECTS = \
"CMakeFiles/E03G.dir/main.c.o"

# External object files for target E03G
E03G_EXTERNAL_OBJECTS =

E03G: CMakeFiles/E03G.dir/main.c.o
E03G: CMakeFiles/E03G.dir/build.make
E03G: CMakeFiles/E03G.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable E03G"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/E03G.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/E03G.dir/build: E03G

.PHONY : CMakeFiles/E03G.dir/build

CMakeFiles/E03G.dir/requires: CMakeFiles/E03G.dir/main.c.o.requires

.PHONY : CMakeFiles/E03G.dir/requires

CMakeFiles/E03G.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/E03G.dir/cmake_clean.cmake
.PHONY : CMakeFiles/E03G.dir/clean

CMakeFiles/E03G.dir/depend:
	cd /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug /home/stefano/Documenti/Algoritmi/Lab/L09/E03/E03G/cmake-build-debug/CMakeFiles/E03G.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/E03G.dir/depend

