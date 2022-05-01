#include "memory.h"


char* allocateString(int size){
    return (char*)calloc(size, sizeof(char));
}


char** allocateArr(int count, int size){
    char** mas = (char**)calloc(count, sizeof(char*));
    for (int i = 0; i < count; i++){
        mas[i] = allocateString(size);
    }
    return mas;
}

char*** allocateMatrix(int len, int count, int size){
    char*** matrix = (char***)calloc(len, sizeof(char**));
    for (int i = 0; i < len; i++){
        matrix[i]  = allocateArr(count, size);
    }
    return matrix;
}


void freeString(char* string){
    free(string);
}

void freeArr(char** mas, int count){
    for (int i = 0; i < count; i++){
        free(mas[i]);
    }
    free(mas);
}

void freeMatrix(char*** matrix, int len, int count){
    for (int i = 0; i < len; i++){
        for (int j = 0; j < count; j++){
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);
}


Coord3D** allocateCoord3D(Data& data){
    Coord3D** coord3D = (Coord3D**) malloc (data.size *sizeof(Coord3D*));
    for (int i = 0; i < data.size; i++) {
        coord3D[i] = (Coord3D*)malloc (data.countColumn * sizeof(Coord3D));
    }
    return coord3D;
}


Coord2D** allocateCoord2D(Data& data){
    Coord2D** coord2D = (Coord2D**)malloc(data.size * sizeof(Coord2D*));
    for(int i = 0; i < data.size;i++){
        coord2D[i] = (Coord2D*)malloc(data.countColumn * sizeof(Coord2D));
    }
    return coord2D;
}


void deleteCoord(Data& data){
    for(int i = 0; i < data.size; i++){
        free(data.coord3D[i]);
    }
    free(data.coord3D);

    for(int i = 0; i < data.size; i++){
        free(data.coord2D[i]);
    }
    free(data.coord2D);
}



