#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <cstdint>

namespace seneca
{
    struct Settings
    {
        uint16_t m_maxSummaryWidth = 80;
        bool m_tableView = false;
    };

    extern Settings g_settings;

}

#endif // SENECA_SETTINGS_H