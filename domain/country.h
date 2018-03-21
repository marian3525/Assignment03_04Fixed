//
// Created by Marian on 3/15/2018.
//

#ifndef ASSIGNMENT03_04FIXED_COUNTRY_H
#define ASSIGNMENT03_04FIXED_COUNTRY_H

#endif //ASSIGNMENT03_04FIXED_COUNTRY_H

typedef struct {
    char* name;             //unique
    char* continent;
    int population;//in millions
} Country;

Country* createCountry(char*, char*, int);

void destroyCountry(Country*);

int getPopulation(Country*);