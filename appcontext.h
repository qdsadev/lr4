#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define CONST_TO_SCALE 2

struct Steps{
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Coord3D{
    double x;
    double y;
    double z;
};

struct Norm{
    int a = 0;
    int b = 20;
};

struct Coord2D{
    double x = 0;
    double y = 0;
};

struct Scale{
    double x = CONST_TO_SCALE;
    double y = CONST_TO_SCALE;
    double z = CONST_TO_SCALE;
};

struct Offset{
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Rotation{
    double x = 0;
    double y = 0;
    double z = 0;
};

struct Data {
    char* name;
    char** nameColumn;
    char*** table;
    int countColumn;
    int size;
    char* region;
    bool fileExists;
    double min;
    double max;
    int scaling;
    Coord2D** coord2D;
    Coord3D** coord3D;
    Norm norm;
    Steps steps;
    Offset offsets;
    Rotation rotations;
};


#endif // APPCONTEXT_H
