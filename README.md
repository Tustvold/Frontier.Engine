Frontier.Engine
===============

## Description

A wrapper around OpenGL which provides some basic functionality (Shaders, VAO Management, Truetype Font Rendering, etc).
It was created as part of a voxel engine and so is designed to be as lightweight as possible both in terms of CPU and memory usage.

## Disclaimer

This engine is still very young and so whilst I will try to keep breaking changes to a minimum, I can make no promise that I won't decide to rewrite large portions of it and therefore break any dependent code.

## Usage

For an example of how to use this library see - https://github.com/Tustvold/Frontier.Engine.DemoProject

## Still to do

- Better 2D support (currently all vertices are 3D)
- Proper AppDelegate system with support for handling the window losing focus, etc
- System to verify that the mesh being used and the shader are compatible
- Skeletal Animation
- Obj import
- Mouse input
- Multithreading support (ThreadPools etc)
- Lighting
- VBO sharing (meshes with the same vertex type can share a VBO)

These features, among others, will be added as I need them in my other projects but feel free to contribute your own implementations.
