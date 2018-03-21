#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../validator/validator.h"
#include "../controller/controller.h"
#include "../controller/undoController.h"

char *getInput() {
    /**
     * Read user input from the keyboard
     * Returns the read string or "" if an endline char is read
     */
    char *input = malloc(100 * sizeof(char));
    fgets(input, 100, stdin);
    if (strcmp(input, "\n") == 0) {
        input = "";
    }
    return strtok(input, "\n");
}

char *getCommand(char *input) {
    /**
     * Extracts and returns the command from a input string (without the endline char)
     */
    if (input == NULL) {
        return NULL;
    }
    char *copy = strdup(input);
    if (strchr(input, ' ') == NULL) { //single word commnad, e.g. print
        return strtok(copy, "\n");
    }

    char *result = strtok(copy, " ");
    return result;
}

char **getParams(char *input, int *paramNumber) {
    /**
     * Extracts the params and returns a list of pointers to them
     * paramNumber: number of params parsed
     */
    *paramNumber = 0; //in case it was not initialised
    char **result = malloc(10 * sizeof(char *));  //assuming each command has at most 10 params
    char *param;
    char *copy = strdup(input);

    int index = 0;
    for (int i = 0; i < 10; i++) {
        result[i] = malloc(20 * sizeof(char));  //assuming each param has at most 20 chars
    }

    param = strtok(copy, " "); //getting rid of the command
    param = strtok(NULL, " "); //getting 1st param

    while (param != NULL) { //parsing params
        result[index++] = param;
        param = strtok(NULL, " ");
    }
    *paramNumber = index;
    return result;
}

char* getHelp() {
    char* help = malloc(650*sizeof(char));
    help = "Country management application\nAvaliable commands:\n"
            "add <countryName> <continent> <population> : adds a new country to the app\n"
            "delete <countryName> : deletes a country with the given name\n"
            "update <countryName> <continent> <population> : updates the details for the given country\n"
            "filter name <substring> : print all countries containing the given substring\n"
            "filter continent <continent> <populationThreshold> : print in ascending order by population countries from the given continent with population greated than the limit\n"
            "undo\n"
            "redo\n";
    return help;
}

char* buildStatement(char* command, char** params, int paramNumber) {
    char* result = malloc(100*sizeof(char));
    strcat(result, command);
    for(int i=0; i<paramNumber; i++) {
        strcat(result, " ");
        strcat(result, params[i]);
    }
    return result;
}

void start() {
    char *command;
    char *input;
    char **params;
    int stopped = 0;
    int paramNumber = 0;
    char **auxPtr;
    int undoing = 0; //flag not to put anything on the undo stack when running commands for an undo statement

    initController();
    initUndoController();

    while (!stopped) {
        if(!undoing) {
            printf(">>>");
            input = getInput();
        }
        //if undoing, the input will have been provided from the previous loop
        command = getCommand(input);
        params = getParams(input, &paramNumber);

        if (strcmp(command, "add") == 0) {
            if (paramNumber != 3) {
                printf("'add' command takes 3 arguments: add countryName continent population");
            } else {
                //the number of params in correct, validate them
                char *countryName;
                countryName = strdup(params[0]);
                char *continent;
                continent = strdup(params[1]);
                int population;
                population = strtol(strdup(params[2]), NULL, 10);

                int errorCode = validateAdd(countryName, continent, population);
                if (errorCode != 0) {
                    switch (errorCode) {
                        case (1): {
                            printf("Invalid country name");
                            break;
                        }
                        case (2): {
                            printf("Invalid continent");
                            break;
                        }
                        case (3): {
                            printf("Invalid population");
                            break;
                        }
                    }
                    printf("\n");
                }
                else {
                    //everything ok, call the controller
                    if(!undoing) {
                        addOperationToStack(command, params);
                    }
                    errorCode = addCountry(countryName, continent, population);
                    undoing = 0;


                    if(errorCode != 0) {
                        printf("Error!"); //TODO add cases
                    }
                }
            }
        }
        if (strcmp(command, "delete") == 0) {
            //delete <name>
            if (paramNumber != 1) {
                printf("Wrong number of parameters");
            } else {
                int errorCode = validateDelete(params[0]);

                if(errorCode != 0) {
                    switch (errorCode) {
                        case(1): {
                            printf("Invalid name");
                        }
                    }
                    printf("\n");
                }
                else {
                    if(!undoing) {
                        addOperationToStack(command, params);
                    }
                    int errorCode = deleteCountry(params[0]);
                    undoing = 0;
                }
        }
        }
        if (strcmp(command, "update") == 0) {
            //update <name> <continent> <population>
            if(paramNumber != 2) {
                printf("Wrong number of parameters");
            }
            else {
                int population = strtol(strdup(params[1]), NULL, 10);
                int errorCode = validateUpdate(params[0], population);

                if(errorCode != 0) {

                    switch (errorCode) {
                        case (1): {
                            printf("Invalid name");
                            break;
                        }
                        case (3): {
                            printf("Invalid population");
                            break;
                        }
                    }
                    printf("\n");
                }
                else {
                    if(!undoing) {
                        addOperationToStack(command, params);
                    }
                    int errorCode = updateCountry(params[0], population);
                    undoing = 0;
                }
            }
        }
        if(strcmp(command, "filter") == 0) {
            if(strcmp(params[0], "name") == 0 && paramNumber == 2) {
                int errorCode = validateFilterByName(params[1]);

                if(errorCode != 0) {

                    switch (errorCode) {
                        case(1): {
                            printf("Invalid name");
                            break;
                        }
                    }
                    printf("\n");

                }
                else {
                    Country** list;
                    int n;
                    list = filterByName(params[1], &n);

                    for(int i=0; i<n; i++) {
                        printf("%d.%s | %s | %dM\n", i+1 ,  list[i]->name, list[i]->continent, list[i]->population);
                    }
                    free(list);
                }

            }
            if(strcmp(params[0], "continent") ==0 && paramNumber == 3) {
                int errorCode = validateFilterByContinent(params[1], strtol(strdup(params[2]), NULL, 10));
                if(errorCode != 0) {
                    switch(errorCode) {
                        case(1): {
                            printf("Invalid continent");
                            break;
                        }
                        case(2): {
                            printf("Invalid population limit");
                            break;
                        }
                    }
                    printf("\n");

                }
                else {
                    Country** list;
                    int n;
                    int treshold = strtol(strdup(params[2]), NULL, 10);
                    list = filterByContinentAndPopulation(params[1], &n, treshold);

                    for(int i=0; i<n; i++) {
                        printf("%d.%s | %s | %dM\n", i+1 ,  list[i]->name, list[i]->continent, list[i]->population);
                    }
                    free(list);
                }
            }
        }
        if (strcmp(command, "print") == 0) {
            int n = 0;
            Country** countries = getCountries(&n);

            for(int i=0; i<n; i++) {
                printf("%d.%s | %s | %dM\n", i+1 ,  countries[i]->name, countries[i]->continent, countries[i]->population);
            }
        }
        if(strcmp(command,"exit") == 0) {
            quit();  //free the repo
            break;
        }

        if(strcmp(command, "undo") == 0) {
            input = undo();
            if(strlen(input) > 0) {
                undoing = 1;
            }
        }
        if(strcmp(command, "redo") == 0) {
            redo();
        }
        if(strcmp(command, "help") == 0) {
            char* help = getHelp();
            printf("%s", help);
            //free(help);
        }
        else {
            printf("Unknown command\n");
        }
    }

    free(command);
    free(input);
    for(int i=0; i<10; i++) {
        free(params[i]);
    }
}