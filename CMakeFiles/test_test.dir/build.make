# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/zabulskyy/UCU/OperatingSystems/myshell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zabulskyy/UCU/OperatingSystems/myshell

# Include any dependencies generated for this target.
include CMakeFiles/test_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_test.dir/flags.make

CMakeFiles/test_test.dir/src/mycat.cpp.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/src/mycat.cpp.o: src/mycat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_test.dir/src/mycat.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/src/mycat.cpp.o -c /home/zabulskyy/UCU/OperatingSystems/myshell/src/mycat.cpp

CMakeFiles/test_test.dir/src/mycat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/src/mycat.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/UCU/OperatingSystems/myshell/src/mycat.cpp > CMakeFiles/test_test.dir/src/mycat.cpp.i

CMakeFiles/test_test.dir/src/mycat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/src/mycat.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/UCU/OperatingSystems/myshell/src/mycat.cpp -o CMakeFiles/test_test.dir/src/mycat.cpp.s

CMakeFiles/test_test.dir/src/mycat.cpp.o.requires:

.PHONY : CMakeFiles/test_test.dir/src/mycat.cpp.o.requires

CMakeFiles/test_test.dir/src/mycat.cpp.o.provides: CMakeFiles/test_test.dir/src/mycat.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/src/mycat.cpp.o.provides.build
.PHONY : CMakeFiles/test_test.dir/src/mycat.cpp.o.provides

CMakeFiles/test_test.dir/src/mycat.cpp.o.provides.build: CMakeFiles/test_test.dir/src/mycat.cpp.o


CMakeFiles/test_test.dir/src/myls.cpp.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/src/myls.cpp.o: src/myls.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_test.dir/src/myls.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/src/myls.cpp.o -c /home/zabulskyy/UCU/OperatingSystems/myshell/src/myls.cpp

CMakeFiles/test_test.dir/src/myls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/src/myls.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/UCU/OperatingSystems/myshell/src/myls.cpp > CMakeFiles/test_test.dir/src/myls.cpp.i

CMakeFiles/test_test.dir/src/myls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/src/myls.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/UCU/OperatingSystems/myshell/src/myls.cpp -o CMakeFiles/test_test.dir/src/myls.cpp.s

CMakeFiles/test_test.dir/src/myls.cpp.o.requires:

.PHONY : CMakeFiles/test_test.dir/src/myls.cpp.o.requires

CMakeFiles/test_test.dir/src/myls.cpp.o.provides: CMakeFiles/test_test.dir/src/myls.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/src/myls.cpp.o.provides.build
.PHONY : CMakeFiles/test_test.dir/src/myls.cpp.o.provides

CMakeFiles/test_test.dir/src/myls.cpp.o.provides.build: CMakeFiles/test_test.dir/src/myls.cpp.o


CMakeFiles/test_test.dir/src/main.cpp.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_test.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/src/main.cpp.o -c /home/zabulskyy/UCU/OperatingSystems/myshell/src/main.cpp

CMakeFiles/test_test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/UCU/OperatingSystems/myshell/src/main.cpp > CMakeFiles/test_test.dir/src/main.cpp.i

CMakeFiles/test_test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/UCU/OperatingSystems/myshell/src/main.cpp -o CMakeFiles/test_test.dir/src/main.cpp.s

CMakeFiles/test_test.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/test_test.dir/src/main.cpp.o.requires

CMakeFiles/test_test.dir/src/main.cpp.o.provides: CMakeFiles/test_test.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/test_test.dir/src/main.cpp.o.provides

CMakeFiles/test_test.dir/src/main.cpp.o.provides.build: CMakeFiles/test_test.dir/src/main.cpp.o


CMakeFiles/test_test.dir/src/myhello.cpp.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/src/myhello.cpp.o: src/myhello.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test_test.dir/src/myhello.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/src/myhello.cpp.o -c /home/zabulskyy/UCU/OperatingSystems/myshell/src/myhello.cpp

CMakeFiles/test_test.dir/src/myhello.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/src/myhello.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/UCU/OperatingSystems/myshell/src/myhello.cpp > CMakeFiles/test_test.dir/src/myhello.cpp.i

CMakeFiles/test_test.dir/src/myhello.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/src/myhello.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/UCU/OperatingSystems/myshell/src/myhello.cpp -o CMakeFiles/test_test.dir/src/myhello.cpp.s

CMakeFiles/test_test.dir/src/myhello.cpp.o.requires:

.PHONY : CMakeFiles/test_test.dir/src/myhello.cpp.o.requires

CMakeFiles/test_test.dir/src/myhello.cpp.o.provides: CMakeFiles/test_test.dir/src/myhello.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/src/myhello.cpp.o.provides.build
.PHONY : CMakeFiles/test_test.dir/src/myhello.cpp.o.provides

CMakeFiles/test_test.dir/src/myhello.cpp.o.provides.build: CMakeFiles/test_test.dir/src/myhello.cpp.o


CMakeFiles/test_test.dir/src/myrm.cpp.o: CMakeFiles/test_test.dir/flags.make
CMakeFiles/test_test.dir/src/myrm.cpp.o: src/myrm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test_test.dir/src/myrm.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_test.dir/src/myrm.cpp.o -c /home/zabulskyy/UCU/OperatingSystems/myshell/src/myrm.cpp

CMakeFiles/test_test.dir/src/myrm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_test.dir/src/myrm.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/UCU/OperatingSystems/myshell/src/myrm.cpp > CMakeFiles/test_test.dir/src/myrm.cpp.i

CMakeFiles/test_test.dir/src/myrm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_test.dir/src/myrm.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/UCU/OperatingSystems/myshell/src/myrm.cpp -o CMakeFiles/test_test.dir/src/myrm.cpp.s

CMakeFiles/test_test.dir/src/myrm.cpp.o.requires:

.PHONY : CMakeFiles/test_test.dir/src/myrm.cpp.o.requires

CMakeFiles/test_test.dir/src/myrm.cpp.o.provides: CMakeFiles/test_test.dir/src/myrm.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_test.dir/build.make CMakeFiles/test_test.dir/src/myrm.cpp.o.provides.build
.PHONY : CMakeFiles/test_test.dir/src/myrm.cpp.o.provides

CMakeFiles/test_test.dir/src/myrm.cpp.o.provides.build: CMakeFiles/test_test.dir/src/myrm.cpp.o


# Object files for target test_test
test_test_OBJECTS = \
"CMakeFiles/test_test.dir/src/mycat.cpp.o" \
"CMakeFiles/test_test.dir/src/myls.cpp.o" \
"CMakeFiles/test_test.dir/src/main.cpp.o" \
"CMakeFiles/test_test.dir/src/myhello.cpp.o" \
"CMakeFiles/test_test.dir/src/myrm.cpp.o"

# External object files for target test_test
test_test_EXTERNAL_OBJECTS =

test_test: CMakeFiles/test_test.dir/src/mycat.cpp.o
test_test: CMakeFiles/test_test.dir/src/myls.cpp.o
test_test: CMakeFiles/test_test.dir/src/main.cpp.o
test_test: CMakeFiles/test_test.dir/src/myhello.cpp.o
test_test: CMakeFiles/test_test.dir/src/myrm.cpp.o
test_test: CMakeFiles/test_test.dir/build.make
test_test: /usr/lib/libboost_program_options.so
test_test: /usr/lib/libboost_filesystem.so
test_test: /usr/lib/libboost_regex.so
test_test: /usr/lib/libboost_system.so
test_test: /usr/lib/libboost_filesystem.so
test_test: /usr/lib/libboost_regex.so
test_test: /usr/lib/libboost_system.so
test_test: CMakeFiles/test_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable test_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_test.dir/build: test_test

.PHONY : CMakeFiles/test_test.dir/build

CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/src/mycat.cpp.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/src/myls.cpp.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/src/main.cpp.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/src/myhello.cpp.o.requires
CMakeFiles/test_test.dir/requires: CMakeFiles/test_test.dir/src/myrm.cpp.o.requires

.PHONY : CMakeFiles/test_test.dir/requires

CMakeFiles/test_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_test.dir/clean

CMakeFiles/test_test.dir/depend:
	cd /home/zabulskyy/UCU/OperatingSystems/myshell && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zabulskyy/UCU/OperatingSystems/myshell /home/zabulskyy/UCU/OperatingSystems/myshell /home/zabulskyy/UCU/OperatingSystems/myshell /home/zabulskyy/UCU/OperatingSystems/myshell /home/zabulskyy/UCU/OperatingSystems/myshell/CMakeFiles/test_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_test.dir/depend

