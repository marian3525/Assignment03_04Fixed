#include "../domain/country.h"

#ifndef ASSIGNMENT03_04FIXED_REPO_H
#define ASSIGNMENT03_04FIXED_REPO_H

#endif //ASSIGNMENT03_04FIXED_REPO_H

typedef struct {
    int size;
    int capacity;
    Country** elems;
} DynamicVector;

DynamicVector* createRepo(int);

void destroyRepo(DynamicVector*);

void add(DynamicVector *, Country *);

void deleteByName(DynamicVector*, char *);

void update(DynamicVector*, char*, int);

void updateAsMigration(DynamicVector, Country*, Country*);

Country** getAll(DynamicVector*, int *);

Country* getByName(DynamicVector*, char*);

int getIndex(DynamicVector*, char* name);