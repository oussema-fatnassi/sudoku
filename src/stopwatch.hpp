#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class Stopwatch {
public:
    Stopwatch();
    void start();
    void stop();
    void reset();
    void update();  // New method to update elapsed time
    int getSeconds() const;
    int getMinutes() const;
    int getHours() const;
    bool isRunning() const;

private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
    std::chrono::duration<double> elapsed;
    bool running;
};

#endif // STOPWATCH_HPP
