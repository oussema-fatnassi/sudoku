#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>

class Stopwatch {                                                           // Class for the stopwatch
public:                                                                     // Public members

    Stopwatch();                                                            // Default constructor
    ~Stopwatch();                                                           // Destructor
    void start();
    void stop();
    void reset();
    void update();  
    int getSeconds() const;
    int getMinutes() const;
    bool isRunning() const;

private:                                                                    // Private members
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;
    std::chrono::duration<double> elapsed;
    bool running;
};

#endif // STOPWATCH_HPP