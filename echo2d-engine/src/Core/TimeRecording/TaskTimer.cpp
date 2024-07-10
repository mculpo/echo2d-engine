#include "TaskTimer.h"
std::map<std::string, Uint32> TaskTime::startTimes;
std::map<std::string, float> TaskTime::durations;

void TaskTime::start(const std::string& name) {
    Uint32 startTime = SDL_GetTicks();
    startTimes[name] = startTime;
}

void TaskTime::stop(const std::string& name) {
    Uint32 stopTime = SDL_GetTicks();
    if (startTimes.find(name) != startTimes.end()) {
        Uint32 durationMillis = stopTime - startTimes[name];
        float durationMilliseconds = static_cast<float>(durationMillis); // Armazena diretamente em milissegundos fracionados
        durations[name] = durationMilliseconds;
        startTimes.erase(name);
    }
    else {
        std::cerr << "TaskTime Error: Task with name '" << name << "' was not started." << std::endl;
    }
}

float TaskTime::get(const std::string& name) {
    if (durations.find(name) != durations.end()) {
        return durations.at(name);
    }
    else {
        std::cerr << "TaskTime Error: Task with name '" << name << "' does not exist." << std::endl;
        return 0.0f; // Retorna 0 se o tempo da tarefa não existir
    }
}
std::map<std::string, float> TaskTime::getAllDurations() {
    return durations;
}