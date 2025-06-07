#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <stdexcept>
#include <random>
#include <chrono>
#include <iomanip>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <optional>
#include <mutex>

#include <dlfcn.h>
#include <cstdlib>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <entt/entt.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <yaml-cpp/yaml.h>

#define UUID std::string
#define M_VEC3 glm::vec3
#define IM_TEXTURE_ID_FROM_GL(t) reinterpret_cast<void*>((uintptr_t)(t))

namespace MELT
{
    std::string GenerateUUID(uintptr_t _id);
}
