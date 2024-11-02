cmake_minimum_required(VERSION 3.5)
project(MELT_ENGINE)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DM_EDITOR)

add_subdirectory(MeltEngineLib)
add_subdirectory(MeltEngineEditorLib)
#add_subdirectory(Project)

add_executable(MELT_ENGINE main.cpp)

target_link_libraries(MELT_ENGINE PUBLIC MeltEngineLib MeltEngineEditorLib)
