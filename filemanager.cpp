#include "filemanager.h"
#include <QDebug>


void readFile(Data& data,FILE* file){
    rewind(file);
    char* line = allocateString(STRING_SCALE);
    char** splitedLine = allocateArr(data.countColumn,STRING_SCALE);
    int i = 0;
    while(fgets(line,STRING_SCALE,file) != NULL){
        if(!stringCheck((line))) continue;
        splitString(splitedLine,line,data.countColumn);
        copyArr(data.table[i],splitedLine,data.countColumn);
        i++;
    }
    freeString(line);
    freeArr(splitedLine,data.countColumn);
}


FILE* openFile(char* fileName){
    return fopen(fileName,"r");
}


int countColumn(FILE* file){
    rewind(file);
    char* line = allocateString(STRING_SCALE);
    int count = 1;
    fgets(line,STRING_SCALE,file);
    for(int i = 0;*(line+i);i++){
        if(*(line+i) == ',') count++;
    }
    freeString(line);
    return count;
}


int linesLen(FILE* file){
    rewind(file);
    char* line = allocateString(STRING_SCALE);
    int count = 0;
    while (fgets(line, STRING_SCALE, file) != NULL){
        if (!stringCheck(line)) continue;
        count++;
    }
    freeString(line);
    return count;
}


void downloadData(Data& data,FILE* file){
    data.countColumn = countColumn(file);
    data.size = linesLen(file);
    data.table = allocateMatrix(data.size, data.countColumn, STRING_SCALE);
}


void retrieveData(Data& data, char* fileName, Errors& error){
    FILE* file = openFile(fileName);
    if(file != NULL){
        if(data.fileExists){
            freeMatrix(data.table, data.size,data.countColumn);
        }
        downloadData(data,file);
        readFile(data,file);
        data.fileExists = true;
    }else{
        error = File;
    }
}

void fileInspection( char* fileName , Errors& error){
    FILE* file = openFile(fileName);
    rewind(file);
    char* line = allocateString(STRING_SCALE);
    int count = 0;
    fgets(line,STRING_SCALE,file);
    for(int i = 0;*(line+i);i++){
        if(*(line+i)==','){
            count++;
        }
    }
    while(fgets(line,STRING_SCALE,file)){
        int commas = 0;
        for(int i = 1;*(line+i);i++){
            if((*(line+i)==',')){
                commas++;
            }
        }
        if (commas != count){
            error = File;
            break;
            fclose(file);
        }
    }
    rewind(file);
    fclose(file);
}
