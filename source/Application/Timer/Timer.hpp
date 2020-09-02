#pragma once

#include <chrono>
#include <iostream>
class Timer {
    private:
        typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> timepoint_t;
        timepoint_t time = std::chrono::high_resolution_clock::now();
    public:
        Timer() = default;
        void restart();
        void printSeconds();
        void printMilliseconds();
        void printMicroseconds();
        void printNanoseconds();
        int64_t getSeconds();
        int64_t getMilliseconds();
        int64_t getMicroseconds();
        int64_t getNanoseconds();
};
