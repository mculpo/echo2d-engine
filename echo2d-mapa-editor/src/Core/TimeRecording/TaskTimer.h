#ifndef TASKTIME_H
#define TASKTIME_H

#include "../Core.h"

class TaskTime {
public:
    static void start(const std::string& name);
    static void stop(const std::string& name);
    static float get(const std::string& name);
    static std::map<std::string, float> getAllDurations(); // Novo método

private:
    static std::map<std::string, Uint32> startTimes;
    static std::map<std::string, float> durations;
};

#endif

