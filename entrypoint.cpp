#include "entrypoint.h"

void doOperation(Operation operation, Data& data, int column, Errors& error){
    switch(operation){
    case LoadData:
        retrieveData(data, data.name, error);
        break;
    case Calculate:
        operations(data);
        break;
    }
}
