# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/max/vladoc/triangle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/max/vladoc/triangle/build

# Include any dependencies generated for this target.
include CMakeFiles/trian.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/trian.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/trian.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/trian.dir/flags.make

CMakeFiles/trian.dir/main.cpp.o: CMakeFiles/trian.dir/flags.make
CMakeFiles/trian.dir/main.cpp.o: /home/max/vladoc/triangle/main.cpp
CMakeFiles/trian.dir/main.cpp.o: CMakeFiles/trian.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/max/vladoc/triangle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/trian.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/trian.dir/main.cpp.o -MF CMakeFiles/trian.dir/main.cpp.o.d -o CMakeFiles/trian.dir/main.cpp.o -c /home/max/vladoc/triangle/main.cpp

CMakeFiles/trian.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/trian.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/max/vladoc/triangle/main.cpp > CMakeFiles/trian.dir/main.cpp.i

CMakeFiles/trian.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/trian.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/max/vladoc/triangle/main.cpp -o CMakeFiles/trian.dir/main.cpp.s

CMakeFiles/trian.dir/debug_utils/error_control.cpp.o: CMakeFiles/trian.dir/flags.make
CMakeFiles/trian.dir/debug_utils/error_control.cpp.o: /home/max/vladoc/triangle/debug_utils/error_control.cpp
CMakeFiles/trian.dir/debug_utils/error_control.cpp.o: CMakeFiles/trian.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/max/vladoc/triangle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/trian.dir/debug_utils/error_control.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/trian.dir/debug_utils/error_control.cpp.o -MF CMakeFiles/trian.dir/debug_utils/error_control.cpp.o.d -o CMakeFiles/trian.dir/debug_utils/error_control.cpp.o -c /home/max/vladoc/triangle/debug_utils/error_control.cpp

CMakeFiles/trian.dir/debug_utils/error_control.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/trian.dir/debug_utils/error_control.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/max/vladoc/triangle/debug_utils/error_control.cpp > CMakeFiles/trian.dir/debug_utils/error_control.cpp.i

CMakeFiles/trian.dir/debug_utils/error_control.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/trian.dir/debug_utils/error_control.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/max/vladoc/triangle/debug_utils/error_control.cpp -o CMakeFiles/trian.dir/debug_utils/error_control.cpp.s

# Object files for target trian
trian_OBJECTS = \
"CMakeFiles/trian.dir/main.cpp.o" \
"CMakeFiles/trian.dir/debug_utils/error_control.cpp.o"

# External object files for target trian
trian_EXTERNAL_OBJECTS =

trian: CMakeFiles/trian.dir/main.cpp.o
trian: CMakeFiles/trian.dir/debug_utils/error_control.cpp.o
trian: CMakeFiles/trian.dir/build.make
trian: CMakeFiles/trian.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/max/vladoc/triangle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable trian"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/trian.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/trian.dir/build: trian
.PHONY : CMakeFiles/trian.dir/build

CMakeFiles/trian.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/trian.dir/cmake_clean.cmake
.PHONY : CMakeFiles/trian.dir/clean

CMakeFiles/trian.dir/depend:
	cd /home/max/vladoc/triangle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/vladoc/triangle /home/max/vladoc/triangle /home/max/vladoc/triangle/build /home/max/vladoc/triangle/build /home/max/vladoc/triangle/build/CMakeFiles/trian.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/trian.dir/depend

