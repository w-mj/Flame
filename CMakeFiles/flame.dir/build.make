# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /home/wmj/Projects/flame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wmj/Projects/flame

# Include any dependencies generated for this target.
include CMakeFiles/flame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/flame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/flame.dir/flags.make

CMakeFiles/flame.dir/main.cpp.o: CMakeFiles/flame.dir/flags.make
CMakeFiles/flame.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wmj/Projects/flame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/flame.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/flame.dir/main.cpp.o -c /home/wmj/Projects/flame/main.cpp

CMakeFiles/flame.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flame.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wmj/Projects/flame/main.cpp > CMakeFiles/flame.dir/main.cpp.i

CMakeFiles/flame.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flame.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wmj/Projects/flame/main.cpp -o CMakeFiles/flame.dir/main.cpp.s

CMakeFiles/flame.dir/Flame.cpp.o: CMakeFiles/flame.dir/flags.make
CMakeFiles/flame.dir/Flame.cpp.o: Flame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wmj/Projects/flame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/flame.dir/Flame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/flame.dir/Flame.cpp.o -c /home/wmj/Projects/flame/Flame.cpp

CMakeFiles/flame.dir/Flame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flame.dir/Flame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wmj/Projects/flame/Flame.cpp > CMakeFiles/flame.dir/Flame.cpp.i

CMakeFiles/flame.dir/Flame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flame.dir/Flame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wmj/Projects/flame/Flame.cpp -o CMakeFiles/flame.dir/Flame.cpp.s

# Object files for target flame
flame_OBJECTS = \
"CMakeFiles/flame.dir/main.cpp.o" \
"CMakeFiles/flame.dir/Flame.cpp.o"

# External object files for target flame
flame_EXTERNAL_OBJECTS =

flame: CMakeFiles/flame.dir/main.cpp.o
flame: CMakeFiles/flame.dir/Flame.cpp.o
flame: CMakeFiles/flame.dir/build.make
flame: CMakeFiles/flame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wmj/Projects/flame/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable flame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/flame.dir/build: flame

.PHONY : CMakeFiles/flame.dir/build

CMakeFiles/flame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flame.dir/clean

CMakeFiles/flame.dir/depend:
	cd /home/wmj/Projects/flame && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wmj/Projects/flame /home/wmj/Projects/flame /home/wmj/Projects/flame /home/wmj/Projects/flame /home/wmj/Projects/flame/CMakeFiles/flame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flame.dir/depend

