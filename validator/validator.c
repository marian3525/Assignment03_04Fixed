#include <memory.h>

int validateAdd(char* name, char* continent, int population) {
    /**
     * @returns 0: all params are ok
     * @returns 1: at least the name is wrong
     * @returns 2: at least the continent is wrong
     * @returns 3: at least the population is wrong
     */
    if(! strlen(name) > 0) {
        return 1;
    }
    if(! strlen(continent) > 0) {
        return 2;
    }
    if(! population > 0) {
        return 3;
    }
    return 0;
}

int validateDelete(char* name) {
    if(strlen(name) == 0) {
        return 1;
    }
    return 0;
}

int validateUpdate(char* name, int population) {
    if(strlen(name) == 0) {
        return 1;
    }

    if(population <= 0) {
        return 3;
    }
    return 0;
}

int validateFilterByName(char* name) {
    if(strlen(name) == 0) {
        return 1;
    }
    return 0;
}

int validateFilterByContinent(char* name, int population) {
    if(strlen(name) == 0) {
        return 1;
    }
    if(population <= 0) {
        return 2;
    }
    return 0;
}