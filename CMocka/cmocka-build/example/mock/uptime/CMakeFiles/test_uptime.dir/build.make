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
CMAKE_SOURCE_DIR = /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build

# Include any dependencies generated for this target.
include example/mock/uptime/CMakeFiles/test_uptime.dir/depend.make

# Include the progress variables for this target.
include example/mock/uptime/CMakeFiles/test_uptime.dir/progress.make

# Include the compile flags for this target's objects.
include example/mock/uptime/CMakeFiles/test_uptime.dir/flags.make

example/mock/uptime/CMakeFiles/test_uptime.dir/test_uptime.c.o: example/mock/uptime/CMakeFiles/test_uptime.dir/flags.make
example/mock/uptime/CMakeFiles/test_uptime.dir/test_uptime.c.o: /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5/example/mock/uptime/test_uptime.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object example/mock/uptime/CMakeFiles/test_uptime.dir/test_uptime.c.o"
	cd /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_uptime.dir/test_uptime.c.o   -c /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5/example/mock/uptime/test_uptime.c

example/mock/uptime/CMakeFiles/test_uptime.dir/test_uptime.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_uptime.dir/test_uptime.c.i"
	cd /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5/example/mock/uptime/test_uptime.c > CMakeFiles/test_uptime.dir/test_uptime.c.i

example/mock/uptime/CMakeFiles/test_uptime.dir/test_uptime.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_uptime.dir/test_uptime.c.s"
	cd /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5/example/mock/uptime/test_uptime.c -o CMakeFiles/test_uptime.dir/test_uptime.c.s

# Object files for target test_uptime
test_uptime_OBJECTS = \
"CMakeFiles/test_uptime.dir/test_uptime.c.o"

# External object files for target test_uptime
test_uptime_EXTERNAL_OBJECTS =

example/mock/uptime/test_uptime: example/mock/uptime/CMakeFiles/test_uptime.dir/test_uptime.c.o
example/mock/uptime/test_uptime: example/mock/uptime/CMakeFiles/test_uptime.dir/build.make
example/mock/uptime/test_uptime: src/libcmocka.so.0.7.0
example/mock/uptime/test_uptime: /usr/lib/x86_64-linux-gnu/librt.so
example/mock/uptime/test_uptime: example/mock/uptime/CMakeFiles/test_uptime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_uptime"
	cd /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_uptime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/mock/uptime/CMakeFiles/test_uptime.dir/build: example/mock/uptime/test_uptime

.PHONY : example/mock/uptime/CMakeFiles/test_uptime.dir/build

example/mock/uptime/CMakeFiles/test_uptime.dir/clean:
	cd /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime && $(CMAKE_COMMAND) -P CMakeFiles/test_uptime.dir/cmake_clean.cmake
.PHONY : example/mock/uptime/CMakeFiles/test_uptime.dir/clean

example/mock/uptime/CMakeFiles/test_uptime.dir/depend:
	cd /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5 /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-1.1.5/example/mock/uptime /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime /home/eii/Bureau/Escape_game/escapegameproject/CMocka/cmocka-build/example/mock/uptime/CMakeFiles/test_uptime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/mock/uptime/CMakeFiles/test_uptime.dir/depend

