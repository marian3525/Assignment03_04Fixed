//
// Created by Marian on 3/21/2018.
//


#ifndef ASSIGNMENT03_04FIXED_UNDOCONTROLLER_H
#define ASSIGNMENT03_04FIXED_UNDOCONTROLLER_H

#endif //ASSIGNMENT03_04FIXED_UNDOCONTROLLER_H

typedef struct {
    char* operationType;
    char* params;
} Operation;

void addOperationToStack(char*, char**);
char* undo();
void redo();
void initUndoController();