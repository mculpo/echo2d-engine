#ifndef TIME_H
#define TIME_H

#include "../Core/Core.h"

class Time {
private:
    int32_t mMillisecPreviousFrame; // 4 bytes
    double mDeltaTime;   

    Time() : mMillisecPreviousFrame(SDL_GetTicks()), mDeltaTime(0.0) {}

public:
    static Time& GetInstance() {
        static Time instance;
        return instance;
    }


    void Run() {
        /*int timeToWait = ECHO2D_MILLISECS_PER_FRAME - (SDL_GetTicks() - mMillisecPreviousFrame);
        if (timeToWait > 0) {
            SDL_Delay(timeToWait);
        }*/
        mDeltaTime = (SDL_GetTicks() - mMillisecPreviousFrame) / 1000.0;
       
    }

    void UpdateMillisecPreviousFrame() {
        mMillisecPreviousFrame = SDL_GetTicks();
    }

    double DeltaTime() const {
        return mDeltaTime;
    }

    int32_t ElapsedTime() const {
        return SDL_GetTicks();
    }
};

#endif // !TIME_H
