#include "Timer.hpp"

void Timer::restart() {
    time = std::chrono::high_resolution_clock::now();
}
void Timer::printSeconds() {
    std::cout << getSeconds() << "s" << std::endl;
}
void Timer::printMilliseconds() {
    std::cout << getMilliseconds() << "ms" << std::endl;
}
void Timer::printMicroseconds() {
    std::cout << getMicroseconds() << "us" << std::endl;
}
void Timer::printNanoseconds() {
    std::cout << getNanoseconds() << "ns" << std::endl;
}
int64_t Timer::getSeconds() {
    auto elapsed = std::chrono::high_resolution_clock::now() - time;
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
}
int64_t Timer::getMilliseconds() {
    auto elapsed = std::chrono::high_resolution_clock::now() - time;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
}
int64_t Timer::getMicroseconds() {
    auto elapsed = std::chrono::high_resolution_clock::now() - time;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}
int64_t Timer::getNanoseconds() {
    auto elapsed = std::chrono::high_resolution_clock::now() - time;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
}
