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
CMAKE_SOURCE_DIR = /Users/macbook/CLionProjects/TDS_PH_meter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug

# Utility rule file for TDS_PH_meter-upload.

# Include the progress variables for this target.
include CMakeFiles/TDS_PH_meter-upload.dir/progress.make

CMakeFiles/TDS_PH_meter-upload: TDS_PH_meter.elf
	/Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/avrdude -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -patmega2560 -cwiring -b115200 -P/dev/cu.SLAB_USBtoUART -D -v -Uflash:w:/Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug/TDS_PH_meter.hex:i -Ueeprom:w:/Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug/TDS_PH_meter.eep:i

TDS_PH_meter-upload: CMakeFiles/TDS_PH_meter-upload
TDS_PH_meter-upload: CMakeFiles/TDS_PH_meter-upload.dir/build.make

.PHONY : TDS_PH_meter-upload

# Rule to build all files generated by this target.
CMakeFiles/TDS_PH_meter-upload.dir/build: TDS_PH_meter-upload

.PHONY : CMakeFiles/TDS_PH_meter-upload.dir/build

CMakeFiles/TDS_PH_meter-upload.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TDS_PH_meter-upload.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TDS_PH_meter-upload.dir/clean

CMakeFiles/TDS_PH_meter-upload.dir/depend:
	cd /Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macbook/CLionProjects/TDS_PH_meter /Users/macbook/CLionProjects/TDS_PH_meter /Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug /Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug /Users/macbook/CLionProjects/TDS_PH_meter/cmake-build-debug/CMakeFiles/TDS_PH_meter-upload.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TDS_PH_meter-upload.dir/depend

