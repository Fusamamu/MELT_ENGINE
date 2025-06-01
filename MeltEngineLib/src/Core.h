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
#include <random>
#include <chrono>
#include <iomanip>
#include <functional>
#include <typeindex>
#include <stdexcept>
#include <dlfcn.h>
#include <optional>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <entt/entt.hpp>

#define UUID std::string
#define M_VEC3 glm::vec3
#define IM_TEXTURE_ID_FROM_GL(t) reinterpret_cast<void*>((uintptr_t)(t))

namespace MELT
{
    std::string GenerateUUID(uintptr_t _id);
}
