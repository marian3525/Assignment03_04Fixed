#include <string.h>
#include <stdlib.h>
#include "../repository/repo.h"
#include "undoController.h"

DynamicVector *repo;



int addCountry(char* countryName, char* continent, int population) {
    /**
     * Create and add a country* to the repo
     * @param countryName: string: name of the country ot build
     * @param continent: string: name of the continent
     * @param population: int: the population of the country
     * @return int: 0 if successful
     */
    Country* country = createCountry(countryName, continent, population);
    add(repo, country);
    return 0;
}

DynamicVector* getRepo() {  //only used for testing
    return repo;
}

int deleteCountry(char* name) {
    /**
     * Delete the country with the given name
     * @param name: string: name of the country
     * @return void
     */
    deleteByName(repo, name);
}

int updateCountry(char* countryName, int newPopulation) {
    /**
     * Updates the country with the given name by changing the continent and/or the population
     * @param countryName: string: name of the unique country to be updated
     * @param continent: string: new continent
     * @param newPopulation: int
     */
    update(repo, countryName, newPopulation);
}

Country** filterByName(char* substring, int* nr) {
    /**
     * Filters the countries
     * @param substring: string: the substring to be searched
     * @param nr: int*: int pointer to return the number of countries which passed the filter
     * @return Country**: a list of Country* which contain the given substring
     */
    int n;
    int index=0;
    Country** list = malloc(100 * sizeof(Country*));
    Country** countries = getAll(repo, &n);

    for(int i=0; i<n; i++) {
        if(strstr(countries[i]->name, substring) != NULL) {
            list[index++] = countries[i];
        }
    }
    *nr = index;
    return list;
}

void bSort(Country** c, int n) {
    int done = 0;
    size_t aux;
    do {
        done = 1;
        for(int i=0; i<n-1; i++) {
            if(c[i]->population > c[i+1]->population) {
                aux = (size_t)c[i];
                c[i] = c[i+1];
                c[i+1] = (size_t)aux;
                done = 0;
            }
        }
    }while (done == 0);
}

int gt(const void *a, const void* b) {
    if(((Country*)a)->population < ((Country*)b)->population) {
        return -1;
    }
    if(((Country*)a)->population == ((Country*)b)->population) {
        return 0;
    }
    if(((Country*)a)->population > ((Country*)b)->population) {
        return 1;
    }
}

Country** filterByContinentAndPopulation(char* continent, int* nr, int threshold) {
    /**
     * Filters the countries by the continent and the population limit
     * @param continent: string: The continent to filter by
     * @param nr: int*: int* to return the number of countries who passed the filter
     * @param threshold: int: population limit for the contries
     * @return Country**: List of countries with the specified continent and population above threshold
     */
    int n;
    int index=0;
    Country** list = malloc(100 * sizeof(Country*));
    Country** countries = getAll(repo, &n);

    for(int i=0; i<n; i++) {
        if(strstr(countries[i]->continent, continent) != NULL && countries[i]->population > threshold) {
            list[index++] = countries[i];
        }
    }
    *nr = index;

    bSort(list, index);
    return list;
}
void quit() {
    /**
     * Called by the interface on exit commands, destroy the repo
     */
    destroyRepo(repo);
}

Country** getCountries(int* n) {
    /**
     * @param n: int*: int* to return the number of countries
     * @return Country**: list of countries currently stored
     */
    return getAll(repo, n);
}

void populateRepo() {
    /**
     * populate the repo with some test data
     */
    addCountry("Romania", "Europe", 18);
    addCountry("US", "North-America", 325);
    addCountry("Egypt", "Africa", 95);
    addCountry("UK", "Europe", 65);
    addCountry("China", "Asia", 1379);
    addCountry("Australia", "Australia", 24);
    addCountry("Canada", "North-America", 36);
    addCountry("Germany", "Europe", 82);
    addCountry("France", "Europe", 67);
    addCountry("Italy", "Europe", 60);


}

void initController() {
    /**
     * Called by the interface on application start
     */
    repo = createRepo(20);
    populateRepo();
}