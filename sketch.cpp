#include <Arduino.h>
#include "dhwFilters.h"

/*
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
*/

dhwFilters Filters(2, 3, 4);

void setup()
{
	Filters.SetUserFilterName(dhwFilters::FILTER_USER_1, "Filter 1");
	Filters.SetUserFilterEnabled(dhwFilters::FILTER_USER_1, true);
	Filters.SetUserFilterName(dhwFilters::FILTER_USER_2, "Filter 2");
	Filters.SetUserFilterEnabled(dhwFilters::FILTER_USER_2, true);

	String str = Filters.GetFilterName();
}

void loop()
{

    while (1)
    {
        int8_t n = 10;

        while (n)
        {
            dhwFilters::FilterWidth_t f = Filters.Next();
            String                    str = Filters.GetFilterName();

            delay(10000);
            n--;
        }

        n = 10;

        while (n)
        {
            dhwFilters::FilterWidth_t f = Filters.Previous();
            String                    str = Filters.GetFilterName();

            delay(10000);
            n--;
        }
    }
}
