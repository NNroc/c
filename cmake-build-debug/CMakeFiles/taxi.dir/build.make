# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = G:\need\c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = G:\need\c\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/taxi.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/taxi.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/taxi.dir/flags.make

CMakeFiles/taxi.dir/taxi.cpp.obj: CMakeFiles/taxi.dir/flags.make
CMakeFiles/taxi.dir/taxi.cpp.obj: ../taxi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=G:\need\c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/taxi.dir/taxi.cpp.obj"
	F:\MinGW64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\taxi.dir\taxi.cpp.obj -c G:\need\c\taxi.cpp

CMakeFiles/taxi.dir/taxi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taxi.dir/taxi.cpp.i"
	F:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E G:\need\c\taxi.cpp > CMakeFiles\taxi.dir\taxi.cpp.i

CMakeFiles/taxi.dir/taxi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taxi.dir/taxi.cpp.s"
	F:\MinGW64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S G:\need\c\taxi.cpp -o CMakeFiles\taxi.dir\taxi.cpp.s

# Object files for target taxi
taxi_OBJECTS = \
"CMakeFiles/taxi.dir/taxi.cpp.obj"

# External object files for target taxi
taxi_EXTERNAL_OBJECTS =

taxi.exe: CMakeFiles/taxi.dir/taxi.cpp.obj
taxi.exe: CMakeFiles/taxi.dir/build.make
taxi.exe: CMakeFiles/taxi.dir/linklibs.rsp
taxi.exe: CMakeFiles/taxi.dir/objects1.rsp
taxi.exe: CMakeFiles/taxi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=G:\need\c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable taxi.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\taxi.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/taxi.dir/build: taxi.exe

.PHONY : CMakeFiles/taxi.dir/build

CMakeFiles/taxi.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\taxi.dir\cmake_clean.cmake
.PHONY : CMakeFiles/taxi.dir/clean

CMakeFiles/taxi.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" G:\need\c G:\need\c G:\need\c\cmake-build-debug G:\need\c\cmake-build-debug G:\need\c\cmake-build-debug\CMakeFiles\taxi.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/taxi.dir/depend

