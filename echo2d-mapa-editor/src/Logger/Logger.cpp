#include "Logger.h"


std::string GetFileName(const std::string& path) {
	// Encontra a última ocorrência do caractere de barra invertida
	size_t pos = path.find_last_of("\\");
	if (pos != std::string::npos) {
		// Retorna a parte da string a partir dessa posição
		return path.substr(pos);
	}
	else {
		// Se não houver nenhuma ocorrência, retorna o caminho completo
		return path;
	}
}

std::string CurrentDataTimeToString() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	struct tm timeinfo;
	if (localtime_s(&timeinfo, &now) == 0) {
		std::strftime(&output[0], output.size(), "%d/%b/%Y %H:%M:%S", &timeinfo);
	}
	return output;
}

void Logger::Info(const std::string& message, const char* file, int line) {

	std::cout << CurrentDataTimeToString();
	std::cout << ANSI_COLOR_GREEN << " INFO " << ANSI_COLOR_RESET;
	std::cout << ANSI_COLOR_GREY << GetFileName(file) << ":" << line << ": " << ANSI_COLOR_RESET;
	std::cout << message << std::endl;
}

void Logger::Warning(const std::string& message, const char* file, int line) {
	std::cout << CurrentDataTimeToString();
	std::cout << ANSI_COLOR_YELLOW << " WARN " << ANSI_COLOR_RESET;
	std::cout << ANSI_COLOR_GREY << GetFileName(file) << ":" << line << ": " << ANSI_COLOR_RESET;
	std::cout << message << std::endl;
}

void Logger::Error(const std::string& message, const char* file, int line) {
	std::cout << CurrentDataTimeToString();
	std::cout << ANSI_COLOR_RED << " ERRO " << ANSI_COLOR_RESET;
	std::cout << ANSI_COLOR_GREY << GetFileName(file) << ":" << line << ": " << ANSI_COLOR_RESET;
	std::cout << message << std::endl;
}