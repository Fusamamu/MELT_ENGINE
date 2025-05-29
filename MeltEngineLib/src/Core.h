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
#include <dlfcn.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <entt/entt.hpp>


#define M_VEC3 glm::vec3


namespace MELT
{
    std::string GenerateUUID(uintptr_t _id);
}
