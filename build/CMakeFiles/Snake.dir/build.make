# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stanleya1293/Desktop/Projects/Snake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stanleya1293/Desktop/Projects/Snake/build

# Include any dependencies generated for this target.
include CMakeFiles/Snake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Snake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Snake.dir/flags.make

CMakeFiles/Snake.dir/snake.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/snake.o: ../snake.cpp
CMakeFiles/Snake.dir/snake.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stanleya1293/Desktop/Projects/Snake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Snake.dir/snake.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/snake.o -MF CMakeFiles/Snake.dir/snake.o.d -o CMakeFiles/Snake.dir/snake.o -c /home/stanleya1293/Desktop/Projects/Snake/snake.cpp

CMakeFiles/Snake.dir/snake.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Snake.dir/snake.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stanleya1293/Desktop/Projects/Snake/snake.cpp > CMakeFiles/Snake.dir/snake.i

CMakeFiles/Snake.dir/snake.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/snake.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stanleya1293/Desktop/Projects/Snake/snake.cpp -o CMakeFiles/Snake.dir/snake.s

# Object files for target Snake
Snake_OBJECTS = \
"CMakeFiles/Snake.dir/snake.o"

# External object files for target Snake
Snake_EXTERNAL_OBJECTS =

Snake: CMakeFiles/Snake.dir/snake.o
Snake: CMakeFiles/Snake.dir/build.make
Snake: lib/glfw-3.4/src/libglfw3.a
Snake: /usr/lib/x86_64-linux-gnu/libGL.so
Snake: /usr/lib/x86_64-linux-gnu/librt.a
Snake: /usr/lib/x86_64-linux-gnu/libm.so
Snake: CMakeFiles/Snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stanleya1293/Desktop/Projects/Snake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Snake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Snake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Snake.dir/build: Snake
.PHONY : CMakeFiles/Snake.dir/build

CMakeFiles/Snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Snake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Snake.dir/clean

CMakeFiles/Snake.dir/depend:
	cd /home/stanleya1293/Desktop/Projects/Snake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stanleya1293/Desktop/Projects/Snake /home/stanleya1293/Desktop/Projects/Snake /home/stanleya1293/Desktop/Projects/Snake/build /home/stanleya1293/Desktop/Projects/Snake/build /home/stanleya1293/Desktop/Projects/Snake/build/CMakeFiles/Snake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Snake.dir/depend
