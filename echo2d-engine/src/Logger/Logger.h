#ifndef ECHO2D_LOGGER_H
#define ECHO2D_LOGGER_H
#include "../Core/Core.h"

class Logger {
public:
	static void Info(const std::string& message, const char* file, int line);
	static void Warning(const std::string& message, const char* file, int line);
	static void Error(const std::string& message, const char* file, int line);
};

#endif // !ECHO2D_LOGGER_H
