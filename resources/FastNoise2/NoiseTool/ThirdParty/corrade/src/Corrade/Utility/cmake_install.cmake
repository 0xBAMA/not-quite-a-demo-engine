# Install script for directory: /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/lib/libCorradeUtility.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./include/Corrade/Utility" TYPE FILE FILES
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Algorithms.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Arguments.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/AbstractHash.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Assert.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Configuration.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/ConfigurationGroup.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/ConfigurationValue.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Debug.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/DebugStl.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Directory.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Endianness.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/EndiannessBatch.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Format.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/FormatStl.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Macros.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/MurmurHash2.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Resource.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Sha1.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/String.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/StlForwardArray.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/StlForwardString.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/StlForwardTuple.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/StlForwardVector.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/StlMath.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/System.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/TypeTraits.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Unicode.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/utilities.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Utility.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/VisibilityMacros.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/visibility.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/FileWatcher.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/Tweakable.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/corrade/src/Corrade/Utility/TweakableParser.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/corrade-rc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/corrade-rc")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/corrade-rc"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/bin/corrade-rc")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/corrade-rc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/corrade-rc")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/corrade-rc")
    endif()
  endif()
endif()

