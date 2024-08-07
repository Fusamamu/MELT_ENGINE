cmake_minimum_required(VERSION 3.5)
project(MELT_ENGINE)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MeltEngineLib)

add_executable(MELT_ENGINE main.cpp)
target_link_libraries(MELT_ENGINE PRIVATE MeltEngineLib)
