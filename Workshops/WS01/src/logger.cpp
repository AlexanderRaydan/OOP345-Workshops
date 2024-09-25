#include "logger.h"
#include <utility> // For std::move

namespace seneca
{

    // Default constructor
    Logger::Logger() : events(nullptr), eventCount(0) {}

    // Destructor
    Logger::~Logger()
    {
        delete[] events;
        events = nullptr;
    }

    // Move constructor
    Logger::Logger(Logger &&other)
        : events(other.events), eventCount(other.eventCount)
    {
        other.events = nullptr;
        other.eventCount = 0;
    }

    // Move assignment operator
    Logger &Logger::operator=(Logger &&other)
    {
        if (this != &other)
        {
            delete[] events;

            events = other.events;
            eventCount = other.eventCount;

            other.events = nullptr;
            other.eventCount = 0;
        }
        return *this;
    }

    // Adds an event
    void Logger::addEvent(const Event &event)
    {
        Event *newEvents = new Event[eventCount + 1]; // Allocate new array

        for (size_t i = 0; i < eventCount; ++i)
        {
            newEvents[i] = events[i];
        }

        delete[] events;
        events = newEvents;

        events[eventCount++] = event;
    }

    std::ostream &operator<<(std::ostream &os, const Logger &logger)
    {
        for (size_t i = 0; i < logger.eventCount; i++)
        {
            os << logger.events[i] << std::endl;
        }
        return os;
    }

}
