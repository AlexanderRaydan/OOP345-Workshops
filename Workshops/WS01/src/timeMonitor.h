#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <chrono>
#include <string>
#include "event.h"

namespace seneca
{

    class TimeMonitor
    {
        std::chrono::steady_clock::time_point m_startTime;
        std::string m_eventName;

    public:
        // Default constructor
        TimeMonitor() {}

        // Starts a new event with the given name
        void startEvent(const char *name);

        // Stops the event, calculates duration, and returns an Event object
        Event stopEvent();
    };

} // namespace seneca

#endif
