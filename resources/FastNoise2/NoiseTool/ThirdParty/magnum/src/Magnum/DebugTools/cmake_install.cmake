# Install script for directory: /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/lib/libMagnumDebugTools.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./include/Magnum/DebugTools" TYPE FILE FILES
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/ColorMap.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/DebugTools.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/FrameProfiler.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/visibility.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/Profiler.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/ResourceManager.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/Screenshot.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/TextureImage.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/BufferData.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/ForceRenderer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/DebugTools/ObjectRenderer.h"
    )
endif()

