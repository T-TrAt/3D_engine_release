#include "Timer.h"

void Timer::timeStart() {
    start = std::chrono::high_resolution_clock::now();
}
void Timer::timeUpdate() {
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
}

auto Timer::getDuration() -> std::chrono::nanoseconds const {
    return duration;
}




float FrameTimer::getFrameRate() {
    frameRate = 1.0e9 / static_cast<double>(duration.count());
    return frameRate;
}
void FrameTimer::wait() {

    while (duration.count() < TDN) {
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    }
}
