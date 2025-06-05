cmake_minimum_required(VERSION 3.5)
project(CustomNativeScript VERSION 1.0.1 DESCRIPTION "Native scripts")

add_library(${PROJECT_NAME} SHARED Scripts/HelloWorld.cpp)

find_library(MELT_ENGINE_PATH
        NAMES MeltEngineLib
        PATHS ../cmake-build-debug/MeltEngineLib # or wherever the dylib is
        NO_DEFAULT_PATH
)
message(STATUS "MeltEngineLib found as: ${MELT_ENGINE_PATH}")

target_include_directories(${PROJECT_NAME} PUBLIC
        ./Scripts
        ../MeltEngineLib/src
        ../MeltEngineLib/src/Reflection)

target_link_libraries(${PROJECT_NAME} PUBLIC ${MELT_ENGINE_PATH})