# not-quite-a-demo-engine
## (aka NQADE /eŋkweɪd/)

My recent efforts have been to clean up the directory structure and provide all the improvements that I have been adding to the Voraldo codebase.

Requires `libsdl2-dev` on Ubuntu.

Make sure to recurse submodules to pull in FastNoise2 code - `git submodule update --init --recursive`

In order to support rapid prototyping of graphical applications, there are a number of utilities provided:

  - OpenGL Debug callback for error/warning reporting
  - GLM for vector and matrix types
  - dearImGUI for menus, etc
  - SDL is used for windowing and input handling, basic template for application in `resources/engine_code/`

  - LodePNG for loading/saving of PNG images (supports transparency)
  - Diamond-Square algorithm heightmap generation
  - Now using FastNoise2 for more flexible, more powerful, and much, much faster noise generation

  - JSON parsing using nlohmann's single header implementation
  - TinyOBJLoader for loading of Wavefront .OBJ 3D model files
  - Brent Werness' Voxel Automata Terrain (VAT), converted from processing to C++
    - BigInt library required by the VAT implementation (to replace java/processing BigInt)

Run build.sh in order to build on Ubuntu. It just automates the building of the executable and moves it to the root directory, as files are referenced relative to that location, and then deletes the build folder (if called with the "clean" option).
