cmake_minimum_required(VERSION 3.27)
project(MeltEngineLib VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vendors/yaml-cpp)

add_library(${PROJECT_NAME} STATIC
        src/Core.cpp
        src/MeltEngine.cpp
        src/Vertex.cpp
        src/Mesh.cpp
        src/Renderer/Shader.cpp

        src/ECS/EntityManager.cpp
        src/ECS/ComponentArray.cpp
        src/ECS/SystemManager.cpp
        src/ECS/Coordinator.cpp
        src/ECS/Systems/RenderSystem.cpp
        src/ECS/Systems/CameraControlSystem.cpp
        src/ECS/ComponentManager.cpp
        src/ECS/Components/Camera.cpp
        src/ECS/Components/Transform.cpp
        src/ECS/Components/Renderer.cpp
        src/ECS/Components/SpriteRenderer.cpp

        src/Renderer/FrameBuffer.cpp
        src/TextureManager.cpp
        src/Renderer/Line.cpp
        src/GizmosTransform.cpp

        src/EventSystem/Event.cpp
        src/EventSystem/EventHandler.cpp
        src/EventSystem/EventHandlerWrapper.cpp
        src/EventSystem/EventManager.cpp

        src/InputSystem.cpp
        src/Primitive/Cube.cpp
        src/Primitive/Quad.cpp
        src/Resources/MeshImporter.cpp
        src/Node.cpp
        src/NodeManager.cpp
        src/MathLib/Vector.cpp
        src/Renderer/RendererAPI.cpp
        src/Renderer/RenderPipeline.cpp
        src/RayCast.cpp)

target_precompile_headers(${PROJECT_NAME} PUBLIC ./include/Core.h)

target_include_directories(${PROJECT_NAME} PUBLIC
        ./include
        ./include/EventSystem
        ./include/Renderer
        ./include/Primitive
        ./include/ECS
        ./include/ECS/Components
        ./include/ECS/Systems
        ./include/Resources
        ./include/MathLib
        ./vendors/stb
        ./vendors/yaml-cpp/include
        ./vendors/assimp)

find_package(SDL2   REQUIRED COMPONENTS SDL2)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm    REQUIRED)

if (APPLE)
find_library(COCOA_FRAMEWORK Cocoa)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(COREVIDEO_FRAMEWORK CoreVideo)

find_library(ASSIMP_PATH assimp PATHS vendors/assimp/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC ${ASSIMP_PATH})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::glew)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
if (APPLE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA_FRAMEWORK})
target_link_libraries(${PROJECT_NAME} PUBLIC ${IOKIT_FRAMEWORK})
target_link_libraries(${PROJECT_NAME} PUBLIC ${COREVIDEO_FRAMEWORK})
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)

## Include the installation script
#include(CMakePackageConfigHelpers)
#include(MeltEngine_install.cmake)

