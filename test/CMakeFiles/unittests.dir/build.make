# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.4.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.4.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/brian/Dropbox/projects/cpp/aetee

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/brian/Dropbox/projects/cpp/aetee

# Utility rule file for unittests.

# Include the progress variables for this target.
include test/CMakeFiles/unittests.dir/progress.make

test/CMakeFiles/unittests: bin/aetee-unittests
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/brian/Dropbox/projects/cpp/aetee/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Executing unit tests..."
	cd /Users/brian/Dropbox/projects/cpp/aetee/test && ../bin/aetee-unittests

unittests: test/CMakeFiles/unittests
unittests: test/CMakeFiles/unittests.dir/build.make

.PHONY : unittests

# Rule to build all files generated by this target.
test/CMakeFiles/unittests.dir/build: unittests

.PHONY : test/CMakeFiles/unittests.dir/build

test/CMakeFiles/unittests.dir/clean:
	cd /Users/brian/Dropbox/projects/cpp/aetee/test && $(CMAKE_COMMAND) -P CMakeFiles/unittests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/unittests.dir/clean

test/CMakeFiles/unittests.dir/depend:
	cd /Users/brian/Dropbox/projects/cpp/aetee && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/brian/Dropbox/projects/cpp/aetee /Users/brian/Dropbox/projects/cpp/aetee/test /Users/brian/Dropbox/projects/cpp/aetee /Users/brian/Dropbox/projects/cpp/aetee/test /Users/brian/Dropbox/projects/cpp/aetee/test/CMakeFiles/unittests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/unittests.dir/depend

