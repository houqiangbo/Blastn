#pragma once

#include <chrono>
#include <ctime>

struct Progress {
    Progress(size_t max);
    uint32_t iteration = 0;
    uint32_t max = 0;

    void update();
};

class Timer {
    using Clock = std::chrono::high_resolution_clock::time_point;
public:
    Timer(std::string program_name);

    Clock start_clock;

    std::string program_name;
    void start();
    void stop();
};
