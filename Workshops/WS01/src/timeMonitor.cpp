#include "timeMonitor.h"
#include "event.h"
#include <stdexcept> // For throwing exceptions

namespace seneca
{

    // Starts a new event by recording its name and the current time
    void TimeMonitor::startEvent(const char *name)
    {
        m_eventName = name;
        m_startTime = std::chrono::steady_clock::now();
    }

    // Stops the event, calculates its duration, and returns an Event object
    Event TimeMonitor::stopEvent()
    {
        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);

        return Event(m_eventName.c_str(), duration);
    }

}
