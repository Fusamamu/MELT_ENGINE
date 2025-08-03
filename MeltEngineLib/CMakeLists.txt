cmake_minimum_required(VERSION 3.27)
project(MeltEngineLib VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(./vendors/yaml-cpp)
add_subdirectory(./vendors/entt)
add_subdirectory(./vendors/freetype)

get_target_property(_aliased EnTT::EnTT ALIASED_TARGET)
message(STATUS "EnTT target found as: ${_aliased}")

add_library(${PROJECT_NAME} SHARED
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
        src/ECS/Components/Renderer.cpp
        src/ECS/Components/SpriteRenderer.cpp

        src/Renderer/FrameBuffer.cpp
        src/TextureManager.cpp
        src/GizmosTransform.cpp

        src/EventSystem/Event.cpp
        src/EventSystem/EventHandler.cpp
        src/EventSystem/EventHandlerWrapper.cpp
        src/EventSystem/EventManager.cpp

        src/InputSystem.cpp

        src/Primitive/Cube.cpp
        src/Primitive/Quad.cpp
        src/Primitive/Plane.cpp

        src/Resources/MeshImporter.cpp
        src/Node.cpp
        src/NodeManager.cpp
        src/MathLib/Vector.cpp
        src/Renderer/RendererAPI.cpp
        src/Renderer/RenderPipeline.cpp
        src/RayCast.cpp
        src/Scene.cpp
        src/SceneManager.cpp
        src/ManagerRegistry.cpp
        src/ResourceManager.cpp

        src/Components/Transform.cpp
        src/Components/BoxCollider.cpp
        src/Components/MeshRenderer.cpp
        src/Components/Light.cpp
        src/Components/LineRenderer.cpp
        src/Components/Gizmos.cpp

        src/Texture.cpp
        src/ShaderPreview.cpp
        src/Renderer/GizmosRenderer.cpp
        src/MELT.cpp
        src/MELT.inl
        src/Reflection/Reflection.cpp
        src/Logger.cpp
        src/Serializer.cpp
        src/UI/UI.cpp
        src/UI/UISystem.cpp
        src/UI/Text.h
        src/Bounds.cpp
        src/Primitive/Line.cpp
        src/Systems/MovementSystem.cpp
        src/Components/NodeEditor.cpp
        src/Components/NodeEditor.h
        src/Renderer/DepthPass.cpp
        src/Renderer/DepthPass.h
        src/Renderer/RenderPass.cpp
        src/Renderer/RenderPass.h
        src/Renderer/Material.cpp
        src/Renderer/Material.h
        src/Renderer/CommandBuffer.cpp
        src/Renderer/CommandBuffer.h
        src/Renderer/RenderCommand.cpp
        src/Renderer/RenderCommand.h
        src/Renderer/RenderContext.h
        src/AssetRegistry.cpp
        src/AssetRegistry.h
        src/TileSystem/TileGridFixedSize.cpp
        src/TileSystem/TileGridFixedSize.h
        src/Animation/Bone.cpp
        src/Animation/Bone.h
        src/Util.h
        src/UI/Text.cpp
        src/UI/Text.h
        src/Components/TextRenderer.cpp
        src/Components/TextRenderer.h
        src/UI/UIRenderer.cpp
        src/UI/UIRenderer.h
        src/TileSystem/Grid.cpp
        src/TileSystem/Grid.h
        src/Components/Components.h
)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/Core.h)

target_include_directories(${PROJECT_NAME} PUBLIC
        ./src
        ./src/Components
        ./src/UI
        ./src/TileSystem

        ./src/EventSystem
        ./src/Renderer
        ./src/Primitive
        ./src/ECS
        ./src/ECS/Components
        ./src/ECS/Systems
        ./src/Resources
        ./src/MathLib
        ./src/Reflection
        ./src/Systems

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
        ./vendors/assimp/include
        ./vendors/freetype/include

        ./vendors/spdlog/include)

find_package(SDL2   REQUIRED COMPONENTS SDL2)
find_package(GLEW   REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm    REQUIRED)
find_package(ZLIB   REQUIRED)

find_library(SPDLOG_PATH spdlog PATHS vendors/spdlog/build)
message(STATUS "SPDLOG found as: ${SPDLOG_PATH}")

find_library(ASSIMP_PATH assimp PATHS vendors/assimp/lib)
message(STATUS "ASSIMP found as: ${ASSIMP_PATH}")

if (APPLE)
find_library(COCOA_FRAMEWORK Cocoa)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(COREVIDEO_FRAMEWORK CoreVideo)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::glew)
target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC EnTT)
target_link_libraries(${PROJECT_NAME} PUBLIC freetype)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} PUBLIC ${ASSIMP_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SPDLOG_PATH})
if (APPLE)
target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA_FRAMEWORK})
target_link_libraries(${PROJECT_NAME} PUBLIC ${IOKIT_FRAMEWORK})
target_link_libraries(${PROJECT_NAME} PUBLIC ${COREVIDEO_FRAMEWORK})
endif()

