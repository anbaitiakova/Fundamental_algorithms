# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/an_baitiakova/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/an_baitiakova/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/an_baitiakova/CLionProjects/Course_Work

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Course_Work.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Course_Work.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Course_Work.dir/flags.make

CMakeFiles/Course_Work.dir/main.cpp.o: CMakeFiles/Course_Work.dir/flags.make
CMakeFiles/Course_Work.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Course_Work.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_Work.dir/main.cpp.o -c /home/an_baitiakova/CLionProjects/Course_Work/main.cpp

CMakeFiles/Course_Work.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_Work.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/an_baitiakova/CLionProjects/Course_Work/main.cpp > CMakeFiles/Course_Work.dir/main.cpp.i

CMakeFiles/Course_Work.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_Work.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/an_baitiakova/CLionProjects/Course_Work/main.cpp -o CMakeFiles/Course_Work.dir/main.cpp.s

# Object files for target Course_Work
Course_Work_OBJECTS = \
"CMakeFiles/Course_Work.dir/main.cpp.o"

# External object files for target Course_Work
Course_Work_EXTERNAL_OBJECTS =

Course_Work: CMakeFiles/Course_Work.dir/main.cpp.o
Course_Work: CMakeFiles/Course_Work.dir/build.make
Course_Work: CMakeFiles/Course_Work.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Course_Work"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Course_Work.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Course_Work.dir/build: Course_Work

.PHONY : CMakeFiles/Course_Work.dir/build

CMakeFiles/Course_Work.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Course_Work.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Course_Work.dir/clean

CMakeFiles/Course_Work.dir/depend:
	cd /home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/an_baitiakova/CLionProjects/Course_Work /home/an_baitiakova/CLionProjects/Course_Work /home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug /home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug /home/an_baitiakova/CLionProjects/Course_Work/cmake-build-debug/CMakeFiles/Course_Work.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Course_Work.dir/depend
