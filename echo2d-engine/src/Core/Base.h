#pragma once
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#define ECHO2D_SUCCESS 0

#define ECHO2D_FPS 60
#define ECHO2D_MILLISECS_PER_FRAME 1000/ECHO2D_FPS

#define ANSI_COLOR_GREY    "\033[1;30m"
#define ANSI_COLOR_RED     "\033[1;31m"
#define ANSI_COLOR_GREEN   "\033[1;32m"
#define ANSI_COLOR_YELLOW  "\033[1;33m"
#define ANSI_COLOR_RESET   "\033[0m"

#define LOG_INFO(message) Logger::Info(message, __FILE__, __LINE__)
#define LOG_WARN(message) Logger::Warning(message, __FILE__, __LINE__)
#define LOG_ERROR(message) Logger::Error(message, __FILE__, __LINE__)

#define VEC2_ZERO glm::vec2(0, 0)
#define VEC2_UP glm::vec2(0, -1)
#define VEC2_RIGHT glm::vec2(1, 0)
#define VEC2_DOWN glm::vec2(0, 1)
#define VEC2_LEFT glm::vec2(-1, 0)

