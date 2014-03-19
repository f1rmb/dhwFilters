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
            FILTER_9_27 = 5,
            FILTER_14_73,
            FILTER_24_71,
            FILTER_USER_1 = 3,
            FILTER_USER_2
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

        static Filter_t m_Filters[];

    public:
        dhwFilters(uint8_t s0, uint8_t s1, uint8_t s2);
        virtual ~dhwFilters();

        bool                        SetUserFilterName(FilterWidth_t filter, String name);
        bool                        SetUserFilterEnabled(FilterWidth_t filter, bool enabled = true);
        FilterWidth_t               SetFilter(FilterWidth_t filter);
        const                       String GetFilterName();
        FilterWidth_t               GetFilter();
        FilterWidth_t               Next();
        FilterWidth_t               Previous();

    private:
        FilterWidth_t               _nextprev(bool direction);

    protected:
    private:
        uint8_t                 m_S0, m_S1, m_S2;
        FilterWidth_t           m_currentFilter;
};

#endif // DHWFILTERS_H
