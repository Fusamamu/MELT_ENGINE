cmake_minimum_required(VERSION 3.27)
project(MeltEngineLib)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./vendors/yaml-cpp)

add_library(${PROJECT_NAME} STATIC
        src/MeltEngine.cpp
        src/Shader.cpp
        src/Quad.cpp
        src/Vertex.cpp
        src/ECS/EntityManager.cpp
        src/ECS/ComponentArray.cpp
        src/ECS/ComponentManager.cpp
        src/ECS/SystemManager.cpp
        src/ECS/Event.cpp
        src/ECS/EventManager.cpp
        src/ECS/Coordinator.cpp
        src/ECS/Components/Camera.cpp
        src/ECS/Systems/CameraControlSystem.cpp
        src/ECS/Components/Transform.cpp
        src/EventSystem/Event.cpp
        src/EventSystem/EventHandler.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/ECS)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/ECS/Components)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/ECS/Systems)
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

