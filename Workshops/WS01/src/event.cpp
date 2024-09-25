#include "event.h"
#include <iomanip>

namespace seneca
{

    Event &Event::operator=(const Event &other)
    {
        if (this != &other)
        {
            m_duration = other.m_duration;
            m_name = other.m_name;
        }
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Event &event)
    {
        static int callCounter = 0;
        callCounter++;

        std::chrono::nanoseconds duration_ns = event.m_duration;
        double duration_value;
        std::string unit = g_settings.m_time_units;

        if (unit == "seconds")
        {
            duration_value = std::chrono::duration_cast<std::chrono::duration<double>>(duration_ns).count();
            os << std::setw(2) << callCounter << ": "
               << std::setw(40) << event.m_name << " -> "
               << std::setw(2) << std::fixed << std::setprecision(0) << duration_value << " " << unit;
        }
        else if (unit == "milliseconds")
        {
            duration_value = std::chrono::duration_cast<std::chrono::milliseconds>(duration_ns).count();
            os << std::setw(2) << callCounter << ": "
               << std::setw(40) << event.m_name << " -> "
               << std::setw(5) << duration_value << " " << unit;
        }
        else if (unit == "microseconds")
        {
            duration_value = std::chrono::duration_cast<std::chrono::microseconds>(duration_ns).count();
            os << std::setw(2) << callCounter << ": "
               << std::setw(40) << event.m_name << " -> "
               << std::setw(8) << duration_value << " " << unit;
        }
        else
        {
            duration_value = std::chrono::duration_cast<std::chrono::nanoseconds>(duration_ns).count();
            os << std::setw(2) << callCounter << ": "
               << std::setw(40) << event.m_name << " -> "
               << std::setw(11) << duration_value << " " << unit;
        }

        return os;
    }

}