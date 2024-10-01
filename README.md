# Basic Render Engine

A basic render engine written in OpenGL and C++ for fun because it's cool.

There are 4 basic demos:

- Models: Shows various models with different shaders
- Lighting: Shows a model being illuminated by a point light using Phong Shading
- Texture: Shows a simple texture on a square
- Spritesheet: Shows a basic spritesheet animation

## How to Run:
A build system is not currently set up for this project (sorry :) ). 
The compile commands in compile-commands.txt should work for windows and mac. If you are on windows, everything should be included in this repo so there shouldn't be any need to download things. If you are on a different architecture or some system stuff is different than mine then you would need to recompile the libraries in this project. This is very awful and I give my condolences to you. I wasn't really expecting to stick with this for much longer so I never set up a build system. 

### Mac Specific Stuff
If you are on mac, you will need to download the SDL2 framework and put it in you /Frameworks folder. 
You can download here https://github.com/libsdl-org/SDL/releases/tag/release-2.30.7
If you are on a different architecture, which is a real possibility since I compiled this on the M1 chip which uses an ARM architecture but I know many people still have Intel chips, then this likely won't work for you. Again, sorry about the whole build system thing...