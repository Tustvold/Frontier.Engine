Frontier.Engine
===============

## Description

A wrapper around OpenGL which provides some basic functionality (Shaders, VAO Management, Truetype Font Rendering, etc).
It was created as part of a voxel engine and so is designed to be as lightweight as possible both in terms of CPU and memory usage.

## Installation (Visual Studio 2013)

- Run CMake in the root directories of ThirdParty/freetype-gl and ThirdParty/glfw
- Download glew from https://sourceforge.net/projects/glew/files/glew/1.11.0/glew-1.11.0.zip/download
- Extract glew into ThirdParty/glew-1.11.0 such that ThirdParty/glew-1.11.0/Makefile exists
- Open Frontier.sln
- If prompted agree to upgrade projects
- Right click and reload any projects which failed to load
- Build all

## Still to do

- Better 2D support (currently all vertices are 3D)
- Proper AppDelegate system with support for handling the window losing focus, etc
- System to verify that the mesh being used and the shader are compatible
- Skeletal Animation
- Obj import
- Mouse input
- Multithreading support (ThreadPools etc)
- Lighting

These features, among others, will be added as I need them in my other projects but feel free to contribute your own implementations.
