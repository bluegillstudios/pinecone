# Pinecone

Pinecone is a lightweight, easy-to-use 3D engine written in C++ for creating retro-style first-person games like Quake and DOOM.  
We use SDL2 and OpenGL and support modern C++17.

---

## Features

- Simple API for rendering and camera control  
- Retro-style 3D graphics with textured meshes  
- Cross-platform support (Windows, Linux, macOS)  
- Easy integration of assets and external libraries via Git submodules
---
## Getting Started

1. Clone the repository with submodules

```bash
git clone --recurse-submodules https://github.com/bluegillstudios/pinecone.git
cd pinecone
```

## Prereqs

- C++17 compatible compiler (GCC, Clang, MSVC)
- SDL2 development libraries
- OpenGL development headers
- CMake 3.15 or newer

## "How do I install that?"


On Ubuntu/Debian:
```bash
sudo apt install build-essential cmake libsdl2-dev libgl1-mesa-dev
```
On macOS (using Homebrew):

bash

```brew install cmake sdl2
```
On Windows, the submodules should do
