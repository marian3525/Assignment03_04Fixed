#include "../ui/cli.h"
#include "../validator/validator.h"
#include "../controller/controller.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void testGetCommand() {
    char *result = getCommand("add e e 3\n");
    assert(strcmp(result, "add") == 0);
    result = getCommand("print\n");
    assert(strcmp(result, "print") == 0);

}

void testGetParams() {
    int n = 0;
    char **result = getParams("add param1 param2 param3", &n);
    assert(n == 3);
    assert(strcmp(result[0], "param1") == 0);
    assert(strcmp(result[1], "param2") == 0);
    assert(strcmp(result[2], "param3") == 0);
}

void testParser() {
    testGetCommand();
    testGetParams();
}

void testAddCountry() {
    initController();
    DynamicVector *repo;
    repo = getRepo();
    assert(repo->size == 10);
    addCountry("testCountry", "testContinent", 99);
    assert(repo->size == 11);
    int* n = malloc(sizeof(int));
    *n=0;
    assert(strcmp(getCountries(n)[10]->name, "testCountry") == 0);
    assert(strcmp(getCountries(n)[10]->continent, "testContinent") == 0);
    assert(getCountries(n)[10]->population == 99);
    quit();

}

void testDeleteCountry() {
    initController();
    DynamicVector *repo;
    repo = getRepo();
    assert(repo->size == 10);
    deleteCountry("Romania");
    assert(repo->size == 9);
    quit();
}

void testFilter() {
    initController();
    DynamicVector *repo;
    repo = getRepo();
    assert(repo->size == 10);
    Country **result;
    int *n = malloc(sizeof(int));
    result = filterByName("na", n);
    assert(*n == 2);
    assert(strcmp(result[0]->name, "China") == 0);
    assert(strcmp(result[1]->name, "Canada") == 0);

}

void testController() {
    testAddCountry();
    testDeleteCountry();
    testFilter();
}

void testRepo() {
    testAddCountry();
    testDeleteCountry();
}

void testValidator() {
    assert(validateAdd("Name", "Continent", 10) == 0);
    assert(validateAdd("Name", "Continent", 0) == 3);
    assert(validateAdd("", "Cont", 11) == 1);
    assert(validateAdd("Name", "", 11) == 2);


}

void test() {
    testParser();
    testController();
    testRepo();
    testValidator();
}