#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

#include <string>

struct Settings
{
    uint16_t m_maxSummaryWidth = 80;
    bool m_tableView = false;
};

// Global variable
extern Settings g_settings;

namespace seneca
{
    Settings g_settings;
}

#endif