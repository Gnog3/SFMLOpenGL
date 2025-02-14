cmake_minimum_required(VERSION 3.16)
project(SFMLOpenGL)

set(CMAKE_CXX_STANDARD 20)
include_directories(SFML/include glew/include glm/glm ConcurrentQueue ReaderWriterQueue)
link_directories(SFML/lib glew/lib/Release/x64)
add_definitions(-DDEBUG)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
# set(CMAKE_CXX_FLAGS "-march=native")
add_executable(SFMLOpenGL
        source/main.cpp
        source/Application/Client.cpp
        source/Application/Client.hpp
        source/Application/Player/Player.cpp
        source/Application/Player/Player.hpp
        source/Application/World/SkyBox/SkyBox.cpp
        source/Application/World/SkyBox/SkyBox.hpp
        source/Application/World/World.cpp
        source/Application/World/World.hpp
        source/Application/Vector3LessThan/Vector3LessThan.hpp
        source/Application/World/VertexOperations/VertexOperations.cpp
        source/Application/World/VertexOperations/VertexOperations.hpp
        source/Application/World/Chunk/Chunk.cpp
        source/Application/World/Chunk/Chunk.hpp
        source/Application/World/Block/Block.cpp
        source/Application/World/Block/Block.hpp
        source/Application/World/ChunkMap.hpp
        source/Application/World/Adjoins/Adjoins.hpp
        source/Application/World/Adjoins/Adjoins.cpp
        source/Application/Direction.hpp
        source/Application/static_for/static_for.hpp
        source/Application/Timer/Timer.cpp
        source/Application/Timer/Timer.hpp
        source/Application/DestructionTimer.hpp
        source/Application/NotConstructed.hpp
        source/Application/World/Crosshair/Crosshair.cpp
        source/Application/World/Crosshair/Crosshair.hpp
        source/Application/Engine/Engine.cpp
        source/Application/Engine/Engine.hpp
        source/Application/Engine/RenderChunkMap.hpp
        source/Application/Engine/RenderChunk/RenderChunk.cpp
        source/Application/Engine/RenderChunk/RenderChunk.hpp
        source/Application/Engine/PlaneVertex.hpp
        source/Application/World/ChunkVertexData.hpp
        source/Application/GlobalRef.hpp
        source/Application/GlobalRef.cpp
        source/Application/Thready.hpp)


target_link_libraries(SFMLOpenGL
        sfml-audio
        sfml-graphics
        sfml-window
        sfml-system
        glew32
        opengl32
        winmm
        atomic)