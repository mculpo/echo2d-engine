#pragma once
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>
#include <fstream>
#include <algorithm>
#include <queue>
#include <tuple>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <glm/glm.hpp>

#ifdef _DEBUG
#include <imgui/imgui.h>
#include "../../libs/imgui/backends/imgui_impl_sdl2.h"
#include "../../libs/imgui/backends/imgui_impl_sdlrenderer2.h"
#endif

#include <sol/sol.hpp>

#include "Base.h"
