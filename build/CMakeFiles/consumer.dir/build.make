# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/chauzz/Desktop/DACK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chauzz/Desktop/DACK/build

# Include any dependencies generated for this target.
include CMakeFiles/consumer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/consumer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/consumer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/consumer.dir/flags.make

CMakeFiles/consumer.dir/consumer.c.o: CMakeFiles/consumer.dir/flags.make
CMakeFiles/consumer.dir/consumer.c.o: /home/chauzz/Desktop/DACK/consumer.c
CMakeFiles/consumer.dir/consumer.c.o: CMakeFiles/consumer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chauzz/Desktop/DACK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/consumer.dir/consumer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/consumer.dir/consumer.c.o -MF CMakeFiles/consumer.dir/consumer.c.o.d -o CMakeFiles/consumer.dir/consumer.c.o -c /home/chauzz/Desktop/DACK/consumer.c

CMakeFiles/consumer.dir/consumer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/consumer.dir/consumer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chauzz/Desktop/DACK/consumer.c > CMakeFiles/consumer.dir/consumer.c.i

CMakeFiles/consumer.dir/consumer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/consumer.dir/consumer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chauzz/Desktop/DACK/consumer.c -o CMakeFiles/consumer.dir/consumer.c.s

CMakeFiles/consumer.dir/fifo_ipc.c.o: CMakeFiles/consumer.dir/flags.make
CMakeFiles/consumer.dir/fifo_ipc.c.o: /home/chauzz/Desktop/DACK/fifo_ipc.c
CMakeFiles/consumer.dir/fifo_ipc.c.o: CMakeFiles/consumer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chauzz/Desktop/DACK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/consumer.dir/fifo_ipc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/consumer.dir/fifo_ipc.c.o -MF CMakeFiles/consumer.dir/fifo_ipc.c.o.d -o CMakeFiles/consumer.dir/fifo_ipc.c.o -c /home/chauzz/Desktop/DACK/fifo_ipc.c

CMakeFiles/consumer.dir/fifo_ipc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/consumer.dir/fifo_ipc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chauzz/Desktop/DACK/fifo_ipc.c > CMakeFiles/consumer.dir/fifo_ipc.c.i

CMakeFiles/consumer.dir/fifo_ipc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/consumer.dir/fifo_ipc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chauzz/Desktop/DACK/fifo_ipc.c -o CMakeFiles/consumer.dir/fifo_ipc.c.s

CMakeFiles/consumer.dir/sync_control.c.o: CMakeFiles/consumer.dir/flags.make
CMakeFiles/consumer.dir/sync_control.c.o: /home/chauzz/Desktop/DACK/sync_control.c
CMakeFiles/consumer.dir/sync_control.c.o: CMakeFiles/consumer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chauzz/Desktop/DACK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/consumer.dir/sync_control.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/consumer.dir/sync_control.c.o -MF CMakeFiles/consumer.dir/sync_control.c.o.d -o CMakeFiles/consumer.dir/sync_control.c.o -c /home/chauzz/Desktop/DACK/sync_control.c

CMakeFiles/consumer.dir/sync_control.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/consumer.dir/sync_control.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chauzz/Desktop/DACK/sync_control.c > CMakeFiles/consumer.dir/sync_control.c.i

CMakeFiles/consumer.dir/sync_control.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/consumer.dir/sync_control.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chauzz/Desktop/DACK/sync_control.c -o CMakeFiles/consumer.dir/sync_control.c.s

CMakeFiles/consumer.dir/statistics.c.o: CMakeFiles/consumer.dir/flags.make
CMakeFiles/consumer.dir/statistics.c.o: /home/chauzz/Desktop/DACK/statistics.c
CMakeFiles/consumer.dir/statistics.c.o: CMakeFiles/consumer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/chauzz/Desktop/DACK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/consumer.dir/statistics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/consumer.dir/statistics.c.o -MF CMakeFiles/consumer.dir/statistics.c.o.d -o CMakeFiles/consumer.dir/statistics.c.o -c /home/chauzz/Desktop/DACK/statistics.c

CMakeFiles/consumer.dir/statistics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/consumer.dir/statistics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chauzz/Desktop/DACK/statistics.c > CMakeFiles/consumer.dir/statistics.c.i

CMakeFiles/consumer.dir/statistics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/consumer.dir/statistics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chauzz/Desktop/DACK/statistics.c -o CMakeFiles/consumer.dir/statistics.c.s

# Object files for target consumer
consumer_OBJECTS = \
"CMakeFiles/consumer.dir/consumer.c.o" \
"CMakeFiles/consumer.dir/fifo_ipc.c.o" \
"CMakeFiles/consumer.dir/sync_control.c.o" \
"CMakeFiles/consumer.dir/statistics.c.o"

# External object files for target consumer
consumer_EXTERNAL_OBJECTS =

consumer: CMakeFiles/consumer.dir/consumer.c.o
consumer: CMakeFiles/consumer.dir/fifo_ipc.c.o
consumer: CMakeFiles/consumer.dir/sync_control.c.o
consumer: CMakeFiles/consumer.dir/statistics.c.o
consumer: CMakeFiles/consumer.dir/build.make
consumer: CMakeFiles/consumer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/chauzz/Desktop/DACK/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable consumer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/consumer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/consumer.dir/build: consumer
.PHONY : CMakeFiles/consumer.dir/build

CMakeFiles/consumer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/consumer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/consumer.dir/clean

CMakeFiles/consumer.dir/depend:
	cd /home/chauzz/Desktop/DACK/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chauzz/Desktop/DACK /home/chauzz/Desktop/DACK /home/chauzz/Desktop/DACK/build /home/chauzz/Desktop/DACK/build /home/chauzz/Desktop/DACK/build/CMakeFiles/consumer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/consumer.dir/depend

