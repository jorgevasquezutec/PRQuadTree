# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images

# Include any dependencies generated for this target.
include CMakeFiles/validation_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/validation_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/validation_test.dir/flags.make

CMakeFiles/validation_test.dir/validation_test.o: CMakeFiles/validation_test.dir/flags.make
CMakeFiles/validation_test.dir/validation_test.o: ../validation_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/validation_test.dir/validation_test.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/validation_test.dir/validation_test.o -c /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/validation_test.cpp

CMakeFiles/validation_test.dir/validation_test.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/validation_test.dir/validation_test.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/validation_test.cpp > CMakeFiles/validation_test.dir/validation_test.i

CMakeFiles/validation_test.dir/validation_test.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/validation_test.dir/validation_test.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/validation_test.cpp -o CMakeFiles/validation_test.dir/validation_test.s

# Object files for target validation_test
validation_test_OBJECTS = \
"CMakeFiles/validation_test.dir/validation_test.o"

# External object files for target validation_test
validation_test_EXTERNAL_OBJECTS =

validation_test: CMakeFiles/validation_test.dir/validation_test.o
validation_test: CMakeFiles/validation_test.dir/build.make
validation_test: CMakeFiles/validation_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable validation_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/validation_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/validation_test.dir/build: validation_test

.PHONY : CMakeFiles/validation_test.dir/build

CMakeFiles/validation_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/validation_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/validation_test.dir/clean

CMakeFiles/validation_test.dir/depend:
	cd /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images /mnt/c/Users/jorge/Documents/utec/eda/lab4/PRQuadTree/tests/images/CMakeFiles/validation_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/validation_test.dir/depend
