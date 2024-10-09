cmake_minimum_required(VERSION 3.27)
project(MeltEngineLib)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vendors/yaml-cpp)

add_library(${PROJECT_NAME} STATIC
        src/MeltEngine.cpp
        src/Shader.cpp
        src/Quad.cpp
        src/Vertex.cpp
        ECS/EntityManager.cpp
        ECS/ComponentArray.cpp
        ECS/ComponentManager.cpp
        ECS/SystemManager.cpp
        ECS/Event.cpp
        ECS/EventManager.cpp
        ECS/Coordinator.cpp
        ECS/Components/Camera.cpp
        ECS/Systems/CameraControlSystem.cpp
        ECS/Components/Transform.cpp
        src/EventSystem/Event.cpp
        src/EventSystem/EventHandler.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ./ECS/include)
target_include_directories(${PROJECT_NAME} PUBLIC ./ECS/Components/include)
target_include_directories(${PROJECT_NAME} PUBLIC ./ECS/Systems/include)
target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/yaml-cpp/include)

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

