#include <stdlib.h>
#include "country.h"

Country* createCountry(char* name, char* continent, int population) {
    /**
     * Create a country with the specified attributes
     * IN: @param name: Name of the country (unique)
     *     @param continent: The continent the country belongs to
     *     @
     *     param population: The population of the country
     * OUT: NULL if a referece to Country could not be created
     *      *Country is successful
     */
    Country* country = (Country*) malloc(sizeof(Country));
    if(country == NULL) {
        return NULL;
    }
    else {
        country->name = name;
        country->continent = continent;
        country->population = population;
        return country;
    }
}

void destroyCountry(Country* country) {
    /**
     * @param country: Country*: country to be freed
     */
    if (country != NULL) {
        //free(country->name);
        //free(country->continent);
        free(country);
        country = NULL;
    } else {
        return;
    }
}

int getPopulation(Country* c) {
    return c->population;
}