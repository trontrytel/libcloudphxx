# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build

# Include any dependencies generated for this target.
include tests/common/CMakeFiles/test_common_pvs.dir/depend.make

# Include the progress variables for this target.
include tests/common/CMakeFiles/test_common_pvs.dir/progress.make

# Include the compile flags for this target's objects.
include tests/common/CMakeFiles/test_common_pvs.dir/flags.make

tests/common/CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.o: tests/common/CMakeFiles/test_common_pvs.dir/flags.make
tests/common/CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.o: ../tests/common/test_common_pvs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/common/CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.o"
	cd /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.o -c /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/tests/common/test_common_pvs.cpp

tests/common/CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.i"
	cd /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/tests/common/test_common_pvs.cpp > CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.i

tests/common/CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.s"
	cd /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/tests/common/test_common_pvs.cpp -o CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.s

# Object files for target test_common_pvs
test_common_pvs_OBJECTS = \
"CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.o"

# External object files for target test_common_pvs
test_common_pvs_EXTERNAL_OBJECTS =

tests/common/test_common_pvs: tests/common/CMakeFiles/test_common_pvs.dir/test_common_pvs.cpp.o
tests/common/test_common_pvs: tests/common/CMakeFiles/test_common_pvs.dir/build.make
tests/common/test_common_pvs: libcloudphxx_lgrngn.so
tests/common/test_common_pvs: /usr/lib/gcc/x86_64-linux-gnu/7/libgomp.so
tests/common/test_common_pvs: /usr/lib/x86_64-linux-gnu/libpthread.so
tests/common/test_common_pvs: tests/common/CMakeFiles/test_common_pvs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_common_pvs"
	cd /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_common_pvs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/common/CMakeFiles/test_common_pvs.dir/build: tests/common/test_common_pvs

.PHONY : tests/common/CMakeFiles/test_common_pvs.dir/build

tests/common/CMakeFiles/test_common_pvs.dir/clean:
	cd /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common && $(CMAKE_COMMAND) -P CMakeFiles/test_common_pvs.dir/cmake_clean.cmake
.PHONY : tests/common/CMakeFiles/test_common_pvs.dir/clean

tests/common/CMakeFiles/test_common_pvs.dir/depend:
	cd /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/tests/common /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common /mnt/local/pzmij/UWLCM_singu/singularity/libcloudphxx/build/tests/common/CMakeFiles/test_common_pvs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/common/CMakeFiles/test_common_pvs.dir/depend

