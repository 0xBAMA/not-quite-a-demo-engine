# not-quite-a-demo-engine
## (aka NQADE /eŋkweɪd/)




# Setup
- Requires `libsdl2-dev` on Ubuntu.
- Make sure to recurse submodules to pull in FastNoise2 code - `git submodule update --init --recursive`
- Run build.sh in order to build on Ubuntu. It just automates the building of the executable and moves it to the root directory, as files are referenced relative to that location, and then deletes the build folder (if called with the "clean" option).



# Features
##  Graphics Stuff
  - OpenGL Debug callback for error/warning reporting
  - GLM for vector and matrix types
  - dearImGUI for menus, etc
  - SDL is used for windowing and input handling


##  Noise
  - Diamond-Square algorithm heightmap generation
  - FastNoise2 - flexible, powerful, very fast noise generation


##  Utilities
  - CMake build setup
  - LodePNG for loading/saving of PNG images ( supports transparency and very large images )
  - JSON parsing using nlohmann's single header implementation
  - TinyOBJLoader for loading of Wavefront .OBJ 3D model files
  - Brent Werness' Voxel Automata Terrain ( VAT ), converted from processing to C++
    - BigInt library required by the VAT implementation ( to replace java/processing BigInt )
