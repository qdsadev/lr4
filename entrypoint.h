#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"
#include "filemanager.h"

enum Operation {
    LoadData,
    Calculate
};

enum Errors {
    PtrIsNull,
    Success,
    File
};

void doOperation(Operation operation, Data& data, int column, Errors& error);
void retrieveData(Data& data, char* fileName, Errors& error);
void operations(Data& data);
#endif // ENTRYPOINT_H
