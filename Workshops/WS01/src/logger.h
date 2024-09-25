#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include <iostream>
#include "event.h"

namespace seneca
{

    class Logger
    {
        Event *events;
        size_t eventCount;

    public:
        // Default constructor
        Logger();

        // Destructor
        ~Logger();

        // Move constructor
        Logger(Logger &&other);

        // Move assignment operator
        Logger &operator=(Logger &&other);

        // Add event
        void addEvent(const Event &event);

        friend std::ostream &operator<<(std::ostream &os, const Logger &logger);
    };

}

#endif