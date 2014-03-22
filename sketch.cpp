#include <Arduino.h>
#include "dhwFilters.h"

/*
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
*/

#if 1

dhwFilters Filters(10, 9, 8);

void setup()
{
    Serial.begin(9600);

    Serial.println("press to begin");
    while (!Serial.available()) ;
    Serial.read();


	Filters.SetUserFilterName(dhwFilters::FILTER_USER_1, "Bypass");
	Filters.SetUserFilterEnabled(dhwFilters::FILTER_USER_1, true);
	Filters.SetUserFilterName(dhwFilters::FILTER_USER_2, "bidon");
	Filters.SetUserFilterEnabled(dhwFilters::FILTER_USER_2, true);

	String str = Filters.GetFilterName();
    Serial.println("Current filter: " + str);
}

void loop()
{

    Serial.println("press");
    while (!Serial.available()) ;
    Serial.read();

    while (1)
    {
        int8_t n = 10;

        while (n)
        {
            dhwFilters::FilterWidth_t f = Filters.Next();
            String                    str = Filters.GetFilterName();

            Serial.print(str + ": ");
            Serial.println(f, HEX);

            Serial.println("press");
            while (!Serial.available()) ;
            Serial.read();
            n--;
        }


        Serial.println("Reverse");
        n = 10;

        while (n)
        {
            dhwFilters::FilterWidth_t f = Filters.Previous();
            String                    str = Filters.GetFilterName();

            Serial.print(str + ": ");
            Serial.println(f, HEX);

            Serial.println("press");
            while (!Serial.available()) ;
            Serial.read();
            n--;
        }
    }
}

#else
dhwFilters *Filters;

void setup()
{
    Serial.begin(9600);

    Filters = new dhwFilters(10, 9, 8);

    Serial.println("press to begin");
    while (!Serial.available()) ;
    Serial.read();


	Filters->SetUserFilterName(dhwFilters::FILTER_USER_1, "Bypass");
	Filters->SetUserFilterEnabled(dhwFilters::FILTER_USER_1, true);
	Filters->SetUserFilterName(dhwFilters::FILTER_USER_2, "bidon");
	Filters->SetUserFilterEnabled(dhwFilters::FILTER_USER_2, true);

	String str = Filters->GetFilterName();
    Serial.println("Current filter: " + str);
}

void loop()
{

    Serial.println("press");
    while (!Serial.available()) ;
    Serial.read();

    while (1)
    {
        int8_t n = 10;

        while (n)
        {
            dhwFilters::FilterWidth_t f = Filters->Next();
            String                    str = Filters->GetFilterName();

            Serial.print(str + ": ");
            Serial.println(f, HEX);

            Serial.println("press");
            while (!Serial.available()) ;
            Serial.read();
            n--;
        }


        Serial.println("Reverse");
        n = 10;

        while (n)
        {
            dhwFilters::FilterWidth_t f = Filters->Previous();
            String                    str = Filters->GetFilterName();

            Serial.print(str + ": ");
            Serial.println(f, HEX);

            Serial.println("press");
            while (!Serial.available()) ;
            Serial.read();
            n--;
        }
    }
}
#endif
