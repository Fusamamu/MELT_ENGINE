cmake_minimum_required(VERSION 3.27)
project(MeltEngineLib)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vendors/yaml-cpp)

add_library(${PROJECT_NAME} STATIC
        src/Core.cpp
        src/MeltEngine.cpp
        src/Vertex.cpp
        src/Renderer/Shader.cpp
        src/Renderer/Quad.cpp

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

        src/InputSystem.cpp)

target_precompile_headers(${PROJECT_NAME} PUBLIC ./include/Core.h)

target_include_directories(${PROJECT_NAME} PUBLIC
        ./include
        ./include/EventSystem
        ./include/Renderer
        ./include/ECS
        ./include/ECS/Components
        ./include/ECS/Systems
        ./vendors/stb
        ./vendors/yaml-cpp/include)

find_package(SDL2   REQUIRED COMPONENTS SDL2)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm    REQUIRED)

if (APPLE)
find_library(COCOA_FRAMEWORK Cocoa)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(COREVIDEO_FRAMEWORK CoreVideo)
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

