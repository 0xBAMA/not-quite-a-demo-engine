# not-quite-an-engine
I've been using a very similar structure for the last few projects - why not boil it down to some basics, so I can start a new project more quickly and cleanly. My recent efforts have been to clean up the directory structure and provide all the improvements that I have been adding to the Voraldo codebase.

In order to support rapid prototyping of graphical applications, there are a number of utilities provided:

  - OpenGL Debug callback for error/warning reporting
  
  - GLM for vector and matrix types
  
  - LodePNG for loading of PNG images (supports transparency)
  
  - Diamond-Square algorithm heightmap generation
  
  - JSON parsing using nlohmann's single header implementation
  
  - dearImGUI for menus, etc
  
  - Perlin Noise generation
  
  - TinyOBJLoader for loading of Wavefront .OBJ 3D model files
  
  - Brent Werness' Voxel Automata Terrain, converted from processing to C++
  
  - BigInt library required by the VAT implementation (to replace java/processing BigInt)
  
  - SDL is used for windowing and input handling, basic template for application in `resources/engine_code/`
