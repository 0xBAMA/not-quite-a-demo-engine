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
CMAKE_SOURCE_DIR = /home/jb/Documents/Repos/voraldo/Voraldo-v1.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jb/Documents/Repos/voraldo/Voraldo-v1.2

# Include any dependencies generated for this target.
include resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/depend.make

# Include the progress variables for this target.
include resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/progress.make

# Include the compile flags for this target's objects.
include resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/flags.make

resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.o: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/flags.make
resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.o: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/FrameProfiler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.o"
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.o -c /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/FrameProfiler.cpp

resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.i"
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/FrameProfiler.cpp > CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.i

resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.s"
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/FrameProfiler.cpp -o CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.s

# Object files for target MagnumDebugTools
MagnumDebugTools_OBJECTS = \
"CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.o"

# External object files for target MagnumDebugTools
MagnumDebugTools_EXTERNAL_OBJECTS = \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ColorMap.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/Profiler.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ResourceManager.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/Screenshot.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/TextureImage.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/BufferData.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ForceRenderer.cpp.o" \
"/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ObjectRenderer.cpp.o"

lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/FrameProfiler.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ColorMap.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/Profiler.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ResourceManager.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/Screenshot.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/TextureImage.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/BufferData.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ForceRenderer.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugToolsObjects.dir/ObjectRenderer.cpp.o
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/build.make
lib/libMagnumDebugTools.a: resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../../../../../../lib/libMagnumDebugTools.a"
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools && $(CMAKE_COMMAND) -P CMakeFiles/MagnumDebugTools.dir/cmake_clean_target.cmake
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MagnumDebugTools.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/build: lib/libMagnumDebugTools.a

.PHONY : resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/build

resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/clean:
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools && $(CMAKE_COMMAND) -P CMakeFiles/MagnumDebugTools.dir/cmake_clean.cmake
.PHONY : resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/clean

resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/depend:
	cd /home/jb/Documents/Repos/voraldo/Voraldo-v1.2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jb/Documents/Repos/voraldo/Voraldo-v1.2 /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools /home/jb/Documents/Repos/voraldo/Voraldo-v1.2 /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/CMakeFiles/MagnumDebugTools.dir/depend

