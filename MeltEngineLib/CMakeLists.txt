cmake_minimum_required(VERSION 3.27)
project(MeltEngineLib)
set(CMAKE_CXX_STANDARD 17)

#set(IMGUI_INCLUDE  ./vendors/imgui)
#set(IMGUI_BACKENDS ./vendors/imgui/backends)

#file(GLOB IMGUI_SRCS ${IMGUI_INCLUDE}/*.cpp)

add_library(${PROJECT_NAME} STATIC ./src/MeltEngine.cpp)
#        ${IMGUI_SRCS}
#        ${IMGUI_BACKENDS}/imgui_impl_sdl2.cpp
#        ${IMGUI_BACKENDS}/imgui_impl_opengl3.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
#target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/imgui)
#target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/imgui/backends)

find_package(SDL2   REQUIRED COMPONENTS SDL2)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm    REQUIRED)

#if (APPLE)
find_library(COCOA_FRAMEWORK Cocoa)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(COREVIDEO_FRAMEWORK CoreVideo)
#endif()

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::glew)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
#if (APPLE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA_FRAMEWORK})
target_link_libraries(${PROJECT_NAME} PUBLIC ${IOKIT_FRAMEWORK})
target_link_libraries(${PROJECT_NAME} PUBLIC ${COREVIDEO_FRAMEWORK})
#endif()
