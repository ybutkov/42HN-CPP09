#include "TimeProfiler.hpp"
#include <chrono>


TimeProfiler::TimeProfiler(const std::string& label): label(label) {}

void TimeProfiler::start()
{
    this->startTime = std::chrono::steady_clock::now();
    this->finishTime = std::chrono::steady_clock::time_point();
}

void TimeProfiler::stop()
{
    if (isStarted())
        this->finishTime = std::chrono::steady_clock::now();
}

double TimeProfiler::getDurationInMicroseconds() const
{
    if (isStopped())
        return std::chrono::duration<double, std::micro>(finishTime - startTime).count();
    else
        return static_cast<double>(-1);
}

bool TimeProfiler::isStarted() const {
    return this->startTime != std::chrono::steady_clock::time_point();
}

bool TimeProfiler::isStopped() const {
    return this->finishTime != std::chrono::steady_clock::time_point();
}

const std::string& TimeProfiler::getLabel() const
{
    return this->label;
}
