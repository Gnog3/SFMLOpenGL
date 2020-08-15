cmake_minimum_required(VERSION 3.16)
project(SFMLOpenGL)

set(CMAKE_CXX_STANDARD 20)
include_directories(SFML/include glew/include glm/glm)
link_directories(SFML/lib glew/bin/Release/x64)
add_definitions(-DDEBUG)
add_executable(SFMLOpenGL source/main.cpp source/Application/Client.cpp source/Application/Client.hpp source/Application/ogl.hpp source/Application/Player/Player.cpp source/Application/Player/Player.hpp source/Application/World/SkyBox/SkyBox.cpp source/Application/World/SkyBox/SkyBox.hpp source/Application/World/OpenGLWrappers/OpenGLModel/OpenGLModel.cpp source/Application/World/OpenGLWrappers/OpenGLModel/OpenGLModel.hpp source/Application/World/OpenGLWrappers/VBO/VBO.hpp source/Application/World/World.cpp source/Application/World/World.hpp source/Application/Thing.hpp source/Application/World/Texture/Texture.cpp source/Application/World/Texture/Texture.hpp source/Application/World/StaticBlockFragmentContainer/StaticBlockFragmentContainer.cpp source/Application/World/StaticBlockFragmentContainer/StaticBlockFragmentContainer.hpp source/Application/World/IThingContainer/IThingContainer.hpp source/Application/World/StaticBlockFragment/StaticBlockFragment.cpp source/Application/World/StaticBlockFragment/StaticBlockFragment.hpp source/Application/World/ThingContainers.hpp source/Application/World/IBlockFragmentContainer.hpp source/Application/Things.hpp source/Application/WorldReferenceHack/WorldReferenceHack.hpp source/Application/WorldReferenceHack/WorldReferenceHack.cpp source/Application/Vector3LessThan/Vector3LessThan.hpp source/Application/World/VertexOperations/VertexOperations.cpp source/Application/World/VertexOperations/VertexOperations.hpp source/Application/Vector3LessThan/Vector3LessThan.cpp source/Application/World/IThingContainer/IThingContainer.cpp)


target_link_libraries(SFMLOpenGL
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window
        glew32
        opengl32)