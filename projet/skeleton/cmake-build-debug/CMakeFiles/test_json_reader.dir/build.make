# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /home/ensimag/Downloads/clion-2024.3.2/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/ensimag/Downloads/clion-2024.3.2/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ensimag/3aif/taux/rates_market/projet/skeleton

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test_json_reader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_json_reader.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_json_reader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_json_reader.dir/flags.make

CMakeFiles/test_json_reader.dir/json_reader.cpp.o: CMakeFiles/test_json_reader.dir/flags.make
CMakeFiles/test_json_reader.dir/json_reader.cpp.o: /home/ensimag/3aif/taux/rates_market/projet/skeleton/json_reader.cpp
CMakeFiles/test_json_reader.dir/json_reader.cpp.o: CMakeFiles/test_json_reader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_json_reader.dir/json_reader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_json_reader.dir/json_reader.cpp.o -MF CMakeFiles/test_json_reader.dir/json_reader.cpp.o.d -o CMakeFiles/test_json_reader.dir/json_reader.cpp.o -c /home/ensimag/3aif/taux/rates_market/projet/skeleton/json_reader.cpp

CMakeFiles/test_json_reader.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_json_reader.dir/json_reader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ensimag/3aif/taux/rates_market/projet/skeleton/json_reader.cpp > CMakeFiles/test_json_reader.dir/json_reader.cpp.i

CMakeFiles/test_json_reader.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_json_reader.dir/json_reader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ensimag/3aif/taux/rates_market/projet/skeleton/json_reader.cpp -o CMakeFiles/test_json_reader.dir/json_reader.cpp.s

CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o: CMakeFiles/test_json_reader.dir/flags.make
CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o: /home/ensimag/3aif/taux/rates_market/projet/skeleton/test_json_reader.cpp
CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o: CMakeFiles/test_json_reader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o -MF CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o.d -o CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o -c /home/ensimag/3aif/taux/rates_market/projet/skeleton/test_json_reader.cpp

CMakeFiles/test_json_reader.dir/test_json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_json_reader.dir/test_json_reader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ensimag/3aif/taux/rates_market/projet/skeleton/test_json_reader.cpp > CMakeFiles/test_json_reader.dir/test_json_reader.cpp.i

CMakeFiles/test_json_reader.dir/test_json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_json_reader.dir/test_json_reader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ensimag/3aif/taux/rates_market/projet/skeleton/test_json_reader.cpp -o CMakeFiles/test_json_reader.dir/test_json_reader.cpp.s

# Object files for target test_json_reader
test_json_reader_OBJECTS = \
"CMakeFiles/test_json_reader.dir/json_reader.cpp.o" \
"CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o"

# External object files for target test_json_reader
test_json_reader_EXTERNAL_OBJECTS =

test_json_reader: CMakeFiles/test_json_reader.dir/json_reader.cpp.o
test_json_reader: CMakeFiles/test_json_reader.dir/test_json_reader.cpp.o
test_json_reader: CMakeFiles/test_json_reader.dir/build.make
test_json_reader: /home/ensimag/3aif/pnl-1.15.0/build/lib/libpnl.so
test_json_reader: /usr/lib/x86_64-linux-gnu/libopenblas.so
test_json_reader: /usr/lib/x86_64-linux-gnu/libopenblas.so
test_json_reader: /usr/lib/x86_64-linux-gnu/openmpi/lib/libmpi.so
test_json_reader: CMakeFiles/test_json_reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_json_reader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_json_reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_json_reader.dir/build: test_json_reader
.PHONY : CMakeFiles/test_json_reader.dir/build

CMakeFiles/test_json_reader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_json_reader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_json_reader.dir/clean

CMakeFiles/test_json_reader.dir/depend:
	cd /home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ensimag/3aif/taux/rates_market/projet/skeleton /home/ensimag/3aif/taux/rates_market/projet/skeleton /home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug /home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug /home/ensimag/3aif/taux/rates_market/projet/skeleton/cmake-build-debug/CMakeFiles/test_json_reader.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_json_reader.dir/depend

