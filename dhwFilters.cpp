/*
  Filters Board Management Class, designed to work with the card developped
  by WB6DHW available at http://wb6dhw.com/BPF.html


  Copyright (C) 2014 F1RMB, Daniel Caujolle-Bert <f1rmb.daniel@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "dhwFilters.h"

dhwFilters::dhwFilters(uint8_t s0, uint8_t s1, uint8_t s2) : m_S0(s0), m_S1(s1), m_S2(s2), m_currentFilter(FILTER_24_71)
{
    //ctor
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

dhwFilters::FilterWidth_t dhwFilters::_nextPrev(bool direction) // true: up, false: down
{
    FilterWidth_t f = (m_currentFilter == (direction ? FILTER_24_71 : FILTER_2_11))
                       ?
                        direction ? FILTER_2_11 : FILTER_24_71
                       :
                        static_cast<FilterWidth_t>(direction ? m_currentFilter + 1 : m_currentFilter - 1);

    // Avoid USER filters, if not used
    while (! m_Filters[f].m_used)
        f = static_cast<FilterWidth_t>(direction ? f + 1 : f- 1);

    return SetFilter(f);
}

const String dhwFilters::_getFilterName(FilterWidth_t filter)
{
    return m_Filters[filter].m_name;
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
    return _getFilterName(m_currentFilter);
}

const String dhwFilters::GetFilterName(FilterWidth_t filter)
{
    return _getFilterName(filter);
}

uint8_t dhwFilters::GetMaxNameLength()
{
    uint8_t len = 0;

    for (uint8_t i = 0; i < sizeof(m_Filters) / sizeof(m_Filters[0]); i++)
    {
        uint8_t l = m_Filters[i].m_name.length();

        if (len < l)
            len = l;
    }

    return len;
}

dhwFilters::FilterWidth_t dhwFilters::GetFilter()
{
    return m_currentFilter;
}

dhwFilters::FilterWidth_t dhwFilters::Next()
{
    return _nextPrev(true);
}

dhwFilters::FilterWidth_t dhwFilters::Previous()
{
    return _nextPrev(false);
}
