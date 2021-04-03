# Install script for directory: /home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/lib/libMagnumGL.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./include/Magnum/GL" TYPE FILE FILES
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/AbstractFramebuffer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/AbstractObject.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/AbstractQuery.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/AbstractShaderProgram.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/AbstractTexture.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Attribute.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Buffer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Context.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/CubeMapTexture.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/DefaultFramebuffer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Extensions.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Framebuffer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/GL.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Mesh.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/MeshView.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/OpenGL.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/PixelFormat.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Renderbuffer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/RenderbufferFormat.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Renderer.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Sampler.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Shader.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Texture.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/TextureFormat.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/TimeQuery.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/Version.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/visibility.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/PipelineStatisticsQuery.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/RectangleTexture.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/BufferImage.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/PrimitiveQuery.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/TextureArray.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/TransformFeedback.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/DebugOutput.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/BufferTexture.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/BufferTextureFormat.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/CubeMapTextureArray.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/ImageFormat.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/MultisampleTexture.h"
    "/home/jb/Documents/Repos/voraldo/Voraldo-v1.2/resources/FastNoise2/NoiseTool/ThirdParty/magnum/src/Magnum/GL/SampleQuery.h"
    )
endif()

