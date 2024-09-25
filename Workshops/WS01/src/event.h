
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <iostream>
#include <string>
#include <chrono>
#include "settings.h"

namespace seneca
{

    class Event
    {
        std::string m_name;
        std::chrono::nanoseconds m_duration;

    public:
        // Default constructor
        Event() : m_name{""}, m_duration{0} {}

        // Parameterized constructor
        Event(const char *name, const std::chrono::nanoseconds &duration)
            : m_name{name}, m_duration{duration} {}

        Event &operator=(const Event &other);

        friend std::ostream &operator<<(std::ostream &os, const Event &event);
    };

}

#endif
