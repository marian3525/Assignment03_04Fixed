#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "undoController.h"
#include "../repository/repo.h"

DynamicVector* repo;
char** stack;
int height=0;  //current position in the stack
int top=0;

void initUndoController() {
    stack = malloc(100 * sizeof(char*));
    for(int i=0; i<100; i++) {
        stack[i] = malloc(50 * sizeof(char));
    }
}

void addOperationToStack(char* command, char** params) {
    char* cmd = malloc(50 * sizeof(char));
    if(strcmp(command, "add") == 0) {
        strcat(cmd, "delete ");
        strcat(cmd, params[0]);
    }

    if(strcmp(command, "delete") == 0) {
        strcat(cmd, "add ");
        //get the properties of the country to be removed
        Country* c = getByName(repo, params[0]);
        strcat(cmd, params[0]);
        strcat(cmd, " ");
        strcat(cmd, c->continent);
        strcat(cmd, " ");
        char* aux = malloc(10*sizeof(char));
        sprintf(aux, "%d", c->population);
        strcat(cmd, aux);
        free(aux);
    }
    if(strcmp(command, "update") == 0) {
        strcat(cmd, "update ");
        //build an update statement with the yet not updated data
        strcat(cmd, params[0]);  // the name doesn't change
        strcat(cmd, " ");
        Country* c = getByName(repo, params[0]);
        char* aux = malloc(10*sizeof(char));
        sprintf(aux, "%d", c->population);
        strcat(cmd, aux);
        free(aux);
    }
    strcpy(stack[height], cmd);
    height++;
    top++;
}

void deleteAbove(int start) {
    for(int i=start+1; i<top; i++) {
        stack[i] = NULL;
    }
}

char* undo() {
    /**
     * Returns a command that will undo the last command
     * Return "" is bottom is reached
     */
    if(height) {
        height--;
        return stack[height];

    }
    else {
        char* empty = malloc(2*sizeof(char));
        empty = "";
        return empty;
    }

    //execute statement at stack[height]
}

void redo() {
    if(height<top)
        height++;
    //execute statement at stack[height]
}