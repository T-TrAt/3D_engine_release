#pragma once
#include <chrono>
#include "Global.h"
class Timer {
public:

    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    std::chrono::nanoseconds duration;

    void timeStart();
    void timeUpdate();
    auto getDuration() -> std::chrono::nanoseconds const;
};

class FrameTimer :public Timer {
public:

    float frameRate;
    float getFrameRate();
    void wait();
};