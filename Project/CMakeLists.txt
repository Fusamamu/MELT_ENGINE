cmake_minimum_required(VERSION 3.5)
project(CustomNativeScript VERSION 1.0.1 DESCRIPTION "Native scripts")
#set(CMAKE_BUILD_TYPE Release)

add_library(${PROJECT_NAME} SHARED Scripts/TestCustomSystem.cpp)

#set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME} PUBLIC Scripts)

target_link_libraries(${PROJECT_NAME} PUBLIC MeltEngineLib)