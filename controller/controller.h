

#ifndef ASSIGNMENT03_04FIXED_CONTROLLER_H
#define ASSIGNMENT03_04FIXED_CONTROLLER_H

#endif //ASSIGNMENT03_04FIXED_CONTROLLER_H

int addCountry(char*, char*, int);
void initController();
int deleteCountry(char*);
int updateCountry(char*,int);
Country** getCountries(int*);
Country** filterByName(char*, int*);
Country** filterByContinentAndPopulation(char*, int*, int);
void quit();
DynamicVector* getRepo();