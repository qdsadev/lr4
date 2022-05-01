#include "logic.h"
#include <math.h>
#define PI 3.14


void conversionFromStringToCoord3D(Data& data){
     data.coord3D = allocateCoord3D(data);
     for(int i = 0;i < data.size;i++){
         for(int j = 0; j < data.countColumn;j++){
             data.coord3D[i][j].x = i;
             data.coord3D[i][j].y = j;
             data.coord3D[i][j].z = atof(data.table[i][j]);
         }
     }
}

void obtainDigits(Data& data){
    double* arrDigits = (double*)calloc(data.size*data.countColumn, sizeof(double));
    for(int i = 0; i<data.size; i++){
        for (int column = 0; column < data.countColumn; column++){
            arrDigits[i*data.countColumn+column] = atof(data.table[i][column]);
        }
    }
    maxNumber(arrDigits, data);
    minNumber(arrDigits, data);
    free(arrDigits);
}


void maxNumber(double* arrDigits, Data& data){
    if(arrDigits == nullptr){
        return;
    } else {
        double max = *arrDigits;
        for(int i = 0; i<data.size; i++){
            for(int j = 0; j<data.countColumn; j++){
                if(max<*(arrDigits+j)){
                    max=*(arrDigits+j);
                }
            }
        }
        data.max = max;
    }
}


void minNumber(double* arrDigits, Data& data){
    if(arrDigits == nullptr){
        return;
    } else {
        double min = *arrDigits;
        for(int i = 0; i<data.size; i++){
            for(int j = 0; j<data.countColumn; j++){
                if(min>*(arrDigits+i)){
                    min=*(arrDigits+i);
                }
            }
        }
        data.min = min;
    }
}


void scaleNumber(Data& data){
    if(data.size==0){
        return;
    }
    for(int i = 0; i<data.size; i++){
        for(int j = 0; j<data.countColumn; j++){
            data.coord3D[i][j].x *= data.offsets.x*BASE;
            data.coord3D[i][j].y *= data.offsets.y*BASE;
            data.coord3D[i][j].z *= data.offsets.z*BASE;
        }
    }
}


void scaleData(Data& data){
    for(int i = 0; i  < data.size ;i++){
        for(int j = 0 ; j < data.countColumn;j++){
            data.coord3D[i][j].z = data.norm.a + (data.coord3D[i][j].z-data.min)*(data.norm.b-data.norm.a)/(data.max-data.min);
        }
    }
}

void conversionFrom3Dto2D(Data& data){
    data.coord2D = allocateCoord2D(data);
    for(int i = 0;i < data.size;i++){
       for(int j = 0; j < data.countColumn;j++){
           data.coord2D[i][j].x =  - data.coord3D[i][j].x * cos(30*PI/180) + data.coord3D[i][j].y * cos(30*PI/180);
           data.coord2D[i][j].y = data.coord3D[i][j].x * sin(30*PI/180) + data.coord3D[i][j].y * sin(30*PI/180) - data.coord3D[i][j].z;
        }
    }
}

void rotations(Data& data){
    for(int i = 0; i<data.size; i++){
        for(int j = 0; j<data.size; j++){
            data.coord3D[i][j].y = data.coord3D[i][j].y * cos(CONVERSION_TO_DEGREES_NUMBER * data.rotations.x)
                    - data.coord3D[i][j].z * sin(CONVERSION_TO_DEGREES_NUMBER * data.rotations.x);
            data.coord3D[i][j].z = data.coord3D[i][j].z * sin(CONVERSION_TO_DEGREES_NUMBER * data.rotations.x)
                    + data.coord3D[i][j].z * cos(CONVERSION_TO_DEGREES_NUMBER*data.rotations.x);

            data.coord3D[i][j].x = data.coord3D[i][j].x * cos(CONVERSION_TO_DEGREES_NUMBER * data.rotations.y)
                    + data.coord3D[i][j].z * sin(CONVERSION_TO_DEGREES_NUMBER*data.rotations.y);
            data.coord3D[i][j].z = - data.coord3D[i][j].x * sin(CONVERSION_TO_DEGREES_NUMBER * data.rotations.y)
                    + data.coord3D[i][j].z * cos(CONVERSION_TO_DEGREES_NUMBER * data.rotations.y);

            data.coord3D[i][j].x = data.coord3D[i][j].x * cos(CONVERSION_TO_DEGREES_NUMBER * data.rotations.z)
                    - data.coord3D[i][j].y * sin(CONVERSION_TO_DEGREES_NUMBER * data.rotations.z);
            data.coord3D[i][j].y = data.coord3D[i][j].x * sin(CONVERSION_TO_DEGREES_NUMBER * data.rotations.z)
                    + data.coord3D[i][j].y * cos(CONVERSION_TO_DEGREES_NUMBER * data.rotations.z);
        }
    }
}

void step(Data& data){
    for(int i = 0; i<data.size; i++){
        for(int j = 0; j<data.countColumn; j++){
            data.coord3D[i][j].x += data.steps.x;
            data.coord3D[i][j].y += data.steps.y;
            data.coord3D[i][j].z += data.steps.z;
        }
    }
}

void operations(Data& data){
    obtainDigits(data);
    conversionFromStringToCoord3D(data);
    scaleData(data);
    scaleNumber(data);
    rotations(data);
    step(data);
    conversionFrom3Dto2D(data);
}

