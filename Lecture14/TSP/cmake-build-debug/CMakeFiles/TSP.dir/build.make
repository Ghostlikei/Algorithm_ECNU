# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\temp\TSP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\temp\TSP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TSP.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/TSP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TSP.dir/flags.make

CMakeFiles/TSP.dir/main.cpp.obj: CMakeFiles/TSP.dir/flags.make
CMakeFiles/TSP.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\temp\TSP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TSP.dir/main.cpp.obj"
	D:\download\CCCCCC\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TSP.dir\main.cpp.obj -c D:\temp\TSP\main.cpp

CMakeFiles/TSP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TSP.dir/main.cpp.i"
	D:\download\CCCCCC\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\temp\TSP\main.cpp > CMakeFiles\TSP.dir\main.cpp.i

CMakeFiles/TSP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TSP.dir/main.cpp.s"
	D:\download\CCCCCC\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\temp\TSP\main.cpp -o CMakeFiles\TSP.dir\main.cpp.s

# Object files for target TSP
TSP_OBJECTS = \
"CMakeFiles/TSP.dir/main.cpp.obj"

# External object files for target TSP
TSP_EXTERNAL_OBJECTS =

TSP.exe: CMakeFiles/TSP.dir/main.cpp.obj
TSP.exe: CMakeFiles/TSP.dir/build.make
TSP.exe: CMakeFiles/TSP.dir/linklibs.rsp
TSP.exe: CMakeFiles/TSP.dir/objects1.rsp
TSP.exe: CMakeFiles/TSP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\temp\TSP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TSP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TSP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TSP.dir/build: TSP.exe
.PHONY : CMakeFiles/TSP.dir/build

CMakeFiles/TSP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TSP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TSP.dir/clean

CMakeFiles/TSP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\temp\TSP D:\temp\TSP D:\temp\TSP\cmake-build-debug D:\temp\TSP\cmake-build-debug D:\temp\TSP\cmake-build-debug\CMakeFiles\TSP.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TSP.dir/depend

