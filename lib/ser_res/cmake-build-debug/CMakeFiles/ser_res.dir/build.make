# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/macbook/CLionProjects/ser_res

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macbook/CLionProjects/ser_res/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ser_res.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ser_res.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ser_res.dir/flags.make

CMakeFiles/ser_res.dir/ser_res_test.cpp.obj: CMakeFiles/ser_res.dir/flags.make
CMakeFiles/ser_res.dir/ser_res_test.cpp.obj: ../ser_res_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/CLionProjects/ser_res/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ser_res.dir/ser_res_test.cpp.obj"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ser_res.dir/ser_res_test.cpp.obj -c /Users/macbook/CLionProjects/ser_res/ser_res_test.cpp

CMakeFiles/ser_res.dir/ser_res_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ser_res.dir/ser_res_test.cpp.i"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macbook/CLionProjects/ser_res/ser_res_test.cpp > CMakeFiles/ser_res.dir/ser_res_test.cpp.i

CMakeFiles/ser_res.dir/ser_res_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ser_res.dir/ser_res_test.cpp.s"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macbook/CLionProjects/ser_res/ser_res_test.cpp -o CMakeFiles/ser_res.dir/ser_res_test.cpp.s

CMakeFiles/ser_res.dir/ser_res.cpp.obj: CMakeFiles/ser_res.dir/flags.make
CMakeFiles/ser_res.dir/ser_res.cpp.obj: ../ser_res.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macbook/CLionProjects/ser_res/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ser_res.dir/ser_res.cpp.obj"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ser_res.dir/ser_res.cpp.obj -c /Users/macbook/CLionProjects/ser_res/ser_res.cpp

CMakeFiles/ser_res.dir/ser_res.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ser_res.dir/ser_res.cpp.i"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macbook/CLionProjects/ser_res/ser_res.cpp > CMakeFiles/ser_res.dir/ser_res.cpp.i

CMakeFiles/ser_res.dir/ser_res.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ser_res.dir/ser_res.cpp.s"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macbook/CLionProjects/ser_res/ser_res.cpp -o CMakeFiles/ser_res.dir/ser_res.cpp.s

# Object files for target ser_res
ser_res_OBJECTS = \
"CMakeFiles/ser_res.dir/ser_res_test.cpp.obj" \
"CMakeFiles/ser_res.dir/ser_res.cpp.obj"

# External object files for target ser_res
ser_res_EXTERNAL_OBJECTS =

ser_res.elf: CMakeFiles/ser_res.dir/ser_res_test.cpp.obj
ser_res.elf: CMakeFiles/ser_res.dir/ser_res.cpp.obj
ser_res.elf: CMakeFiles/ser_res.dir/build.make
ser_res.elf: libmega_CORE.a
ser_res.elf: CMakeFiles/ser_res.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/macbook/CLionProjects/ser_res/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ser_res.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ser_res.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating EEP image"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 /Users/macbook/CLionProjects/ser_res/cmake-build-debug/ser_res.elf /Users/macbook/CLionProjects/ser_res/cmake-build-debug/ser_res.eep
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating HEX image"
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom /Users/macbook/CLionProjects/ser_res/cmake-build-debug/ser_res.elf /Users/macbook/CLionProjects/ser_res/cmake-build-debug/ser_res.hex
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Calculating image size"
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -DFIRMWARE_IMAGE=/Users/macbook/CLionProjects/ser_res/cmake-build-debug/ser_res.elf -DMCU=atmega2560 -DEEPROM_IMAGE=/Users/macbook/CLionProjects/ser_res/cmake-build-debug/ser_res.eep -P /Users/macbook/CLionProjects/ser_res/cmake-build-debug/CMakeFiles/FirmwareSize.cmake

# Rule to build all files generated by this target.
CMakeFiles/ser_res.dir/build: ser_res.elf

.PHONY : CMakeFiles/ser_res.dir/build

CMakeFiles/ser_res.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ser_res.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ser_res.dir/clean

CMakeFiles/ser_res.dir/depend:
	cd /Users/macbook/CLionProjects/ser_res/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macbook/CLionProjects/ser_res /Users/macbook/CLionProjects/ser_res /Users/macbook/CLionProjects/ser_res/cmake-build-debug /Users/macbook/CLionProjects/ser_res/cmake-build-debug /Users/macbook/CLionProjects/ser_res/cmake-build-debug/CMakeFiles/ser_res.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ser_res.dir/depend

