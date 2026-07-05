#pragma once

#include <string>
#include <chrono>


class TimeProfiler
{
    private:
        std::string label;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point finishTime;


    public:
        TimeProfiler(const std::string& label="default");
        TimeProfiler(const TimeProfiler& other) = default;
        TimeProfiler& operator=(const TimeProfiler& other) = default;
        ~TimeProfiler() = default;

        void start();
        void stop();
        bool isStarted() const;
        bool isStopped() const;
        const std::string& getLabel() const;
        double getDurationInMicroseconds() const;
};
