#ifndef BASE_H
#define BASE_H

#include "../Logger/Logger.h"
#include "../ECS/ECS.h"

#define ANSI_COLOR_GREY    "\033[1;30m"
#define ANSI_COLOR_RED     "\033[1;31m"
#define ANSI_COLOR_GREEN   "\033[1;32m"
#define ANSI_COLOR_YELLOW  "\033[1;33m"
#define ANSI_COLOR_RESET   "\033[0m"

// Define as macros de log
#define LOG_INFO(message) Logger::Info(message, __FILE__, __LINE__)
#define LOG_WARN(message) Logger::Warning(message, __FILE__, __LINE__)
#define LOG_ERROR(message) Logger::Error(message, __FILE__, __LINE__)

// Define as constantes
const int ECHO2D_SUCCESS = 0;

const int ECHO2D_FPS = 60;
const int ECHO2D_MILLISECS_PER_FRAME = 1000 / ECHO2D_FPS;


// Defina os vetores constantes
const glm::vec2 VEC2_ZERO(0, 0);
const glm::vec2 VEC2_UP(0, -1);
const glm::vec2 VEC2_RIGHT(1, 0);
const glm::vec2 VEC2_DOWN(0, 1);
const glm::vec2 VEC2_LEFT(-1, 0);

const SDL_Color SDL_COLOR_WHITE = { 255, 255, 255, 255 };
const SDL_Color SDL_COLOR_BLACK = { 0, 0, 0, 255 };
const SDL_Color SDL_COLOR_RED = { 255, 0, 0, 255 };
const SDL_Color SDL_COLOR_GREEN = { 0, 255, 0, 255 };
const SDL_Color SDL_COLOR_BLUE = { 0, 0, 255, 255 };
const SDL_Color SDL_COLOR_YELLOW = { 255, 255, 0, 255 };
const SDL_Color SDL_COLOR_CYAN = { 0, 255, 255, 255 };
const SDL_Color SDL_COLOR_MAGENTA = { 255, 0, 255, 255 };
const SDL_Color SDL_COLOR_ORANGE = { 255, 165, 0, 255 };
const SDL_Color SDL_COLOR_PURPLE = { 128, 0, 128, 255 };
const SDL_Color SDL_COLOR_GRAY = { 128, 128, 128, 255 };
const SDL_Color SDL_COLOR_BROWN = { 165, 42, 42, 255 };
const SDL_Color SDL_COLOR_PINK = { 255, 192, 203, 255 };

const int NES_WIDTH = 256;
const int NES_HEIGHT = 240;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


#include "../Core/Time.h"
#endif


