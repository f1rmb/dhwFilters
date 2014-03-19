#include "dhwFilters.h"

    //ctor
dhwFilters::Filter_t dhwFilters::m_Filters[] =
{
    { FILTER_2_11,      "2.11 MHz",     0x0,   true,    true },
    { FILTER_3_51,      "3.51 MHz",     0x1,   true,    true },
    { FILTER_5_89,      "5.89 MHz",     0x2,   true,    true },
    { FILTER_USER_1,    "User 1",       0x3,   false,   false },
    { FILTER_USER_2,    "User 2",       0x4,   false,   false },
    { FILTER_9_27,      "9.27 MHz",     0x5,   true,    true },
    { FILTER_14_73,     "14.73 MHz",    0x6,   true,    true },
    { FILTER_24_71,     "24.71 MHz",    0x7,   true,    true },
};

dhwFilters::dhwFilters(uint8_t s0, uint8_t s1, uint8_t s2) : m_S0(s0), m_S1(s1), m_S2(s2), m_currentFilter(FILTER_2_11)
{
    // Init Pins
    pinMode(m_S0, OUTPUT);
    pinMode(m_S1, OUTPUT);
    pinMode(m_S2, OUTPUT);

    SetFilter(m_currentFilter);
}

dhwFilters::~dhwFilters()
{
    //dtor
}

dhwFilters::FilterWidth_t dhwFilters::SetFilter(FilterWidth_t filter)
{
    digitalWrite(m_S0, (m_Filters[filter].m_bits & S0_BIT) ? HIGH : LOW);
    digitalWrite(m_S1, (m_Filters[filter].m_bits & S1_BIT) ? HIGH : LOW);
    digitalWrite(m_S2, (m_Filters[filter].m_bits & S2_BIT) ? HIGH : LOW);

    m_currentFilter = filter;

    return m_currentFilter;
}

bool dhwFilters::SetUserFilterName(FilterWidth_t filter, String name)
{
    if (m_Filters[filter].m_readonly == false)
    {
        m_Filters[filter].m_name = name;
        return true;
    }

    return false;
}

bool dhwFilters::SetUserFilterEnabled(FilterWidth_t filter, bool enabled)
{
    if (m_Filters[filter].m_readonly == false)
    {
        m_Filters[filter].m_used = enabled;
        return true;
    }

    return false;
}

const String dhwFilters::GetFilterName()
{
    return m_Filters[m_currentFilter].m_name;
}

dhwFilters::FilterWidth_t dhwFilters::GetFilter()
{
    return m_currentFilter;
}

dhwFilters::FilterWidth_t dhwFilters::_nextprev(bool direction) // true: up, false: down
{
    FilterWidth_t f = (m_currentFilter == (direction ? FILTER_24_71 : FILTER_2_11)) ?
                        direction ? FILTER_2_11 : FILTER_24_71
                       :
                        static_cast<FilterWidth_t>(direction ? m_currentFilter + 1 : m_currentFilter - 1);

    // Avoid USER filter, if not used
    while (! m_Filters[f].m_used)
        f = static_cast<FilterWidth_t>(direction ? m_currentFilter + 1 : m_currentFilter - 1);

    return SetFilter(f);
}

dhwFilters::FilterWidth_t dhwFilters::Next()
{
    return _nextprev(true);
}

dhwFilters::FilterWidth_t dhwFilters::Previous()
{
    return _nextprev(false);
}
