#include <stdlib.h>
#include <string.h>
#include "repo.h"

DynamicVector* createRepo(int capacity) {
    /**
     * Creates a dynamic vector with an initial capacity
     * IN: capacity: The initial capacity of the vector
     * OUT: NULL if a DynamicVector was not created
     *      DynamicVector: A reference to the created vector, if successful
     */
    DynamicVector *v = (DynamicVector *) malloc(sizeof(DynamicVector));
    if (v == NULL) {
        return NULL;
    } else {
        v->size = 0;
        v->capacity = capacity;
        v->elems = malloc(capacity * sizeof(Country*));
        return v;
    }
}

void destroyRepo(DynamicVector *v) {
    /**
     * Called by the controller on application exit
     * @param v, DynamicVector*: vector to be freed
     */
    if (v != NULL) {
        free(v->elems);
        v->elems = NULL;
        free(v);
        v = NULL;
    } else {
        return;
    }
}
DynamicVector* resize(DynamicVector* v) {
    /**
     * Increase the size of the vector
     * @param v: DynamicVector: vector to be extended
     */
    v->capacity *= 2;
    v = realloc(v->elems, v->capacity * sizeof(Country*));
    return v;
}

DynamicVector* shrink(DynamicVector* v) {
    v->capacity/=2;
    v = realloc(v->elems, v->capacity * sizeof(Country*));
    return v;
}

void add(DynamicVector *v, Country* a) {
    /**
     * Add an element to the vector
     * @param v: DynamicVector*: vector for the element to be added into
     * @param a: Country*: Country to be added
     */

    if (v == NULL) {
        return;
    }
    if (v->size == v->capacity) {
        v = resize(v);
    }

    v->elems[v->size] = a;
    v->size++;
}
void deleteByName(DynamicVector* v, char* name) {
    /**
     * Destroy the county with a given name
     */

    for(int i=0; i<v->size; i++) {
        if(strcmp(name, v->elems[i]->name) == 0) {
            destroyCountry(v->elems[i]);            //clear the references
            for(int j=i; j<v->size-1; j++) {
                v->elems[j] = v->elems[j+1];
            }
            v->size--;
        }
    }
}

Country** getAll(DynamicVector* v, int* n) {
    /**
     * @param v: source vector
     * @param n: int* to return the number of elements
     * @return Country**: list of Country* existing in the repo
     */
    *n = v->size;
    return v->elems;
}

int getIndex(DynamicVector* v, char* countryName) {
    /**
     * returns the index of the country with the given name
     * -1 if it doesn't exist
     */
    for(int i=0; i<v->size; i++) {
        if(strcmp(v->elems[i]->name, countryName) == 0) {
            return i;
        }
    }
    return -1;
}

Country* getByName(DynamicVector* v, char* name) {
    for(int i=0; i<v->size; i++) {
        if(strcmp(name, v->elems[i]->name) == 0) {
            return v->elems[i];  //or &
        }
    }
}

void update(DynamicVector* v, char* name, int population) {
    /**
     * Update the country with the given name
     */
    for(int i=0; i<v->size; i++) {
        if(strcmp(v->elems[i]->name, name) == 0) {
            v->elems[i]->population = population;
            break; //since countries are unique
        }
    }
}