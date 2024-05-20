#include "stopwatch.hpp"

Stopwatch::Stopwatch() : startTime(), endTime(), elapsed(0), running(false) {}

void Stopwatch::start() {
    if (!running) {
        startTime = std::chrono::system_clock::now();
        running = true;
    }
}

void Stopwatch::stop() {
    if (running) {
        endTime = std::chrono::system_clock::now();
        elapsed += endTime - startTime;
        running = false;
    }
}

void Stopwatch::reset() {
    running = false;
    elapsed = std::chrono::duration<double>(0);
}

void Stopwatch::update() {
    if (running) {
        auto currentTime = std::chrono::system_clock::now();
        endTime = currentTime;
        elapsed = endTime - startTime;
    }
}

int Stopwatch::getSeconds() const {
    return static_cast<int>(elapsed.count()) % 60;
}

int Stopwatch::getMinutes() const {
    return (static_cast<int>(elapsed.count()) / 60) % 60;
}

int Stopwatch::getHours() const {
    return (static_cast<int>(elapsed.count()) / 3600);
}

bool Stopwatch::isRunning() const {
    return running;
}
