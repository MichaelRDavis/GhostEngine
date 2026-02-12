Ghost Engine
============

Ghost Engine source code repository.

Introduction
------------
Ghost Engine is a game engine written in C++.
Ghost Engine will support the following features upon release:

- High-performance 3D renderer powered by the Vulkan graphics API (WIP).
- Fully featured custom physics library called Dynamo (WIP).
- Custom built ECS solution (WIP).
- Runtime compiled C++ for gameplay scripting (WIP).
- Networking support for multiplayer (WIP).

Getting Started
---------------
Ghost Engine currently only supports Windows, with Linux and MacOS support to be delivered in future updates.  

### Prerequisites 
- Premake5 https://premake.github.io/
- Visual Studio 2026 https://visualstudio.microsoft.com/insiders/
- VulkanSDK https://vulkan.lunarg.com/sdk/home

### Windows
- Run **GenerateProjectFiles.bat** to generate the Visual Studio 2026 project files.
- Run **CompileShaders.bat** inside the 'Source/Shaders/glsl/' folder.