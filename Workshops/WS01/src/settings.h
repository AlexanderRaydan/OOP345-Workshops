#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>

namespace seneca
{

    class Settings
    {
    public:
        bool m_show_all = false;
        bool m_verbose = false;
        std::string m_time_units = "nanoseconds";

        // Constructor
        Settings(bool show_all = false, bool verbose = false, const std::string &time_units = "nanoseconds")
            : m_show_all(show_all), m_verbose(verbose), m_time_units(time_units) {}
    };

    // Declare a global Settings instance
    extern Settings g_settings;

}
#endif