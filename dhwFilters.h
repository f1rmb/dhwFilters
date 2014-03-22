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
#ifndef DHWFILTERS_H
#define DHWFILTERS_H

#include <Arduino.h>

class dhwFilters
{
    public:
        typedef enum
        {
            FILTER_2_11 = 0,
            FILTER_3_51,
            FILTER_5_89,
            FILTER_USER_1,
            FILTER_USER_2,
            FILTER_9_27,
            FILTER_14_73,
            FILTER_24_71
        } FilterWidth_t;

    private:
        static const uint8_t S0_BIT = 0x01;
        static const uint8_t S1_BIT = 0x02;
        static const uint8_t S2_BIT = 0x04;

        typedef struct
        {
            FilterWidth_t   m_width;
            String          m_name;
            uint8_t         m_bits;
            bool            m_used;
            bool            m_readonly;
        } Filter_t;

    public:
        dhwFilters(uint8_t s0, uint8_t s1, uint8_t s2);
        virtual ~dhwFilters();

        bool                        SetUserFilterName(FilterWidth_t filter, const String &name);
        bool                        SetUserFilterName(FilterWidth_t filter, const __FlashStringHelper *ifsh);
        bool                        SetUserFilterEnabled(FilterWidth_t filter, bool enabled = true);
        FilterWidth_t               SetFilter(FilterWidth_t filter);
        const String                GetFilterName();
        const String                GetFilterName(FilterWidth_t filter);
        uint8_t                     GetMaxNameLength();
        FilterWidth_t               GetFilter();
        FilterWidth_t               Next();
        FilterWidth_t               Previous();

    private:
        FilterWidth_t               _nextPrev(bool direction);
        const String                _getFilterName(FilterWidth_t filter);

    protected:
    private:
        uint8_t                 m_S0, m_S1, m_S2;
        FilterWidth_t           m_currentFilter;
        Filter_t                m_Filters[8] =
        {
            {
                .m_width    = FILTER_2_11,
                .m_name     = "2.11 MHz",
                .m_bits     = 0x0,
                .m_used     = true,
                .m_readonly = true
            },
            {
                .m_width    = FILTER_3_51,
                .m_name     = "3.51 MHz",
                .m_bits     = 0x1,
                .m_used     = true,
                .m_readonly = true
            },
            {
                .m_width    = FILTER_5_89,
                .m_name     = "5.89 MHz",
                .m_bits     = 0x2,
                .m_used     = true,
                .m_readonly = true
            },
            {
                .m_width    = FILTER_USER_1,
                .m_name     = "User 1",
                .m_bits     = 0x3,
                .m_used     = false,
                .m_readonly = false
            },
            {
                .m_width    = FILTER_USER_2,
                .m_name     = "User 2",
                .m_bits     = 0x4,
                .m_used     = false,
                .m_readonly = false
            },
            {
                .m_width    = FILTER_9_27,
                .m_name     = "9.27 MHz",
                .m_bits     = 0x5,
                .m_used     = true,
                .m_readonly = true
            },
            {
                .m_width    = FILTER_14_73,
                .m_name     = "14.73 MHz",
                .m_bits     = 0x6,
                .m_used     = true,
                .m_readonly = true
            },
            {
                .m_width    = FILTER_24_71,
                .m_name     = "24.71 MHz",
                .m_bits     = 0x7,
                .m_used     = true,
                .m_readonly = true
            }
        };
};

#endif // DHWFILTERS_H
