<p align="center">
<img src="https://raw.githubusercontent.com/MattGuerrette/VixenEngine/master/assets/Others/vixen.png?token=AGF82f6bQ31yR9rHAllCYsrR50J2y6ebks5WGJ5twA%3D%3D" height="200">
</p>
# Vixen Engine
C++ Open Source Game Engine

# About

Vixen Engine, is an attempt to develop a completely free and open game engine for use in commerical, academic, and personal projects. 

Development started on Vixen Engine in 2014 at Rochester Institue of Technology.

# Platforms

Vixen Engine currently targets the following platforms:

* Windows ( Windows 10, Windows 7 )
* Linux   ( Ubuntu )

# Dependencies

* SDL2
* GLEW
* DirectX (DirectX 11)
* OpenGL  (OpenGL 3.3+)
* Assimp
* FreeImage
* tinyxml2
* Lua
* lua-intf

# Building

Build instructions are available for Ubuntu Linux and Microsoft Windows

## Windows (64-bit)  CMake

Included in the repository is a CMake lists file along with a configure batch script. The script is setup to run cmake and output a Visual Studio 2015 x64 solution with project files for each subsystem of Vixen Engine. 

All you need to do is run the configure script and locate the generate solution in the _build directory.

**NOTE:** All dependencies have been included prebuilt targeting x64 with VC++14 compiler in the repository for building on Windows.

## Linux  CMake

Vixen Engine is being developed on Linux using CMake.

All you need to do to setup development for Linux is navigate into the Linux directory of the repo, and run the supplied configure shell script. It will run cmake and output the Makefile to the _build directory which will function as your testbed for development.

**NOTE:** All Vixen libraries will output to **/usr/local/lib** as specified in Makefile.
