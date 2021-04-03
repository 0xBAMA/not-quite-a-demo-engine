# Install script for directory: /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/lib/libMagnumSceneGraph.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./include/Magnum/SceneGraph" TYPE FILE FILES
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractFeature.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractFeature.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractGroupedFeature.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractObject.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractTransformation.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractTranslation.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractTranslationRotation2D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractTranslationRotation3D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractTranslationRotationScaling2D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AbstractTranslationRotationScaling3D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Animable.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Animable.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/AnimableGroup.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Camera.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Camera.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Drawable.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Drawable.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/DualComplexTransformation.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/DualQuaternionTransformation.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/RigidMatrixTransformation2D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/RigidMatrixTransformation2D.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/RigidMatrixTransformation3D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/RigidMatrixTransformation3D.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/FeatureGroup.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/FeatureGroup.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/MatrixTransformation2D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/MatrixTransformation2D.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/MatrixTransformation3D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/MatrixTransformation3D.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Object.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Object.hpp"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/Scene.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/SceneGraph.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/TranslationTransformation.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/TranslationRotationScalingTransformation2D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/TranslationRotationScalingTransformation3D.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/SceneGraph/visibility.h"
    )
endif()

