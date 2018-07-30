# Egler

Egler is an extremely basic OpenGL renderer, writen in C++. It's just a learning project for low-level rendering; don't expect much.

Nonetheless notable is the program's memory layout: other than the one-time initialization of the renderer context, the program makes no dynamic allocations, beyond those inextricably hidden behind library APIs. The `EglerContext` instead cleanly lays out preallocated pools of each object type; as the effective owner of all data, client objects instead hold opaque index IDs into these pools, retrieving their values from the context only as and when necessary.

### Libraries
- [SDL2](https://www.libsdl.org) and [GLEW](http://glew.sourceforge.net/) are used for low-level abstraction.
- Autodesk's [FBX SDK](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2019-0) is used to import mesh data from .fbx files.
- [Google Test](https://github.com/google/googletest) is used for unit testing.