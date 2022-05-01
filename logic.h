#ifndef LOGIC_H
#define LOGIC_H

#include "filemanager.h"

#define AXIS_X 691
#define AXIS_Y 691
#define CONVERSION_TO_DEGREES_NUMBER 0.0174532
#define CONST_TO_DIV_SCALE 2
#define BASE 13

void conversionFromStringToCoordinates(Data& data);
void obtainDigits(Data& data, int column);
void minNumber(double* arrDigits, Data& data);
void maxNumber(double* arrDigits, Data& data);
void scaleNumber(Data& data);

#endif // LOGIC_H
