#include "stopwatch.hpp"

Stopwatch::Stopwatch() : startTime(), endTime(), elapsed(0), running(false) {}                  // Default constructor
Stopwatch::~Stopwatch() {}                                                                      // Destructor                 

void Stopwatch::start() {                                                                       // Function to start the stopwatch
    if (!running) {
        startTime = std::chrono::system_clock::now();
        running = true;
    }
}

void Stopwatch::stop() {                                                                        // Function to stop the stopwatch
    if (running) {
        endTime = std::chrono::system_clock::now();
        elapsed += endTime - startTime;
        running = false;
    }
}

void Stopwatch::reset() {                                                                       // Function to reset the stopwatch
    running = false;
    elapsed = std::chrono::duration<double>(0);
}

void Stopwatch::update() {                                                                      // Function to update the elapsed time
    if (running) {  
        auto currentTime = std::chrono::system_clock::now();
        endTime = currentTime;
        elapsed = endTime - startTime;
    }
}

int Stopwatch::getSeconds() const {                                                             // Function to get the seconds
    return static_cast<int>(elapsed.count()) % 60;
}

int Stopwatch::getMinutes() const {                                                             // Function to get the minutes
    return (static_cast<int>(elapsed.count()) / 60) % 60;
}

bool Stopwatch::isRunning() const {                                                             // Function to check if the stopwatch is running
    return running;
}