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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.5.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.5.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dan/Dropbox/FatBike-teensy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dan/Dropbox/FatBike-teensy

# Utility rule file for FatBike_Firmware.

# Include the progress variables for this target.
include CMakeFiles/FatBike_Firmware.dir/progress.make

CMakeFiles/FatBike_Firmware: bin/FatBike.elf.eep
CMakeFiles/FatBike_Firmware: bin/FatBike.elf.hex


bin/FatBike.elf.eep: bin/FatBike.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/dan/Dropbox/FatBike-teensy/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating bin/FatBike.elf.eep"
	/Applications/Arduino.app/Contents/Java/hardware/tools/arm/bin/arm-none-eabi-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 /Users/dan/Dropbox/FatBike-teensy/bin/FatBike.elf /Users/dan/Dropbox/FatBike-teensy/bin/FatBike.elf.eep

bin/FatBike.elf.hex: bin/FatBike.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/dan/Dropbox/FatBike-teensy/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating bin/FatBike.elf.hex"
	/Applications/Arduino.app/Contents/Java/hardware/tools/arm/bin/arm-none-eabi-objcopy -O ihex -R .eeprom /Users/dan/Dropbox/FatBike-teensy/bin/FatBike.elf /Users/dan/Dropbox/FatBike-teensy/bin/FatBike.elf.hex

FatBike_Firmware: CMakeFiles/FatBike_Firmware
FatBike_Firmware: bin/FatBike.elf.eep
FatBike_Firmware: bin/FatBike.elf.hex
FatBike_Firmware: CMakeFiles/FatBike_Firmware.dir/build.make

.PHONY : FatBike_Firmware

# Rule to build all files generated by this target.
CMakeFiles/FatBike_Firmware.dir/build: FatBike_Firmware

.PHONY : CMakeFiles/FatBike_Firmware.dir/build

CMakeFiles/FatBike_Firmware.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FatBike_Firmware.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FatBike_Firmware.dir/clean

CMakeFiles/FatBike_Firmware.dir/depend:
	cd /Users/dan/Dropbox/FatBike-teensy && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dan/Dropbox/FatBike-teensy /Users/dan/Dropbox/FatBike-teensy /Users/dan/Dropbox/FatBike-teensy /Users/dan/Dropbox/FatBike-teensy /Users/dan/Dropbox/FatBike-teensy/CMakeFiles/FatBike_Firmware.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FatBike_Firmware.dir/depend
