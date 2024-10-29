cmake_minimum_required(VERSION 3.27)
project(MeltEngineEditorLib)
set(CMAKE_CXX_STANDARD 17)

set(IMGUI_INCLUDE  ./vendors/imgui)
set(IMGUI_BACKENDS ./vendors/imgui/backends)

file(GLOB IMGUI_SRCS ${IMGUI_INCLUDE}/*.cpp)

add_subdirectory(vendors/nativefiledialog-extended)

add_library(${PROJECT_NAME} STATIC
            ./src/MeltEngineEditor.cpp
            ./src/ScriptEditorGUI/ScriptEditorGUI.cpp
            ./src/ConsoleGUI.cpp
            ./src/SpriteEditorGUI.cpp
            ${IMGUI_SRCS}
            ${IMGUI_BACKENDS}/imgui_impl_sdl2.cpp
            ${IMGUI_BACKENDS}/imgui_impl_opengl3.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/ScriptEditor)
target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/imgui/backends)
target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/IconFontCppHeaders)
target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/x86_64-w64-mingw32/include)
target_include_directories(${PROJECT_NAME} PUBLIC ./vendors/nativefiledialog-extended/src/include)

target_link_libraries(${PROJECT_NAME} PUBLIC MeltEngineLib)
target_link_libraries(${PROJECT_NAME} PUBLIC nfd)


