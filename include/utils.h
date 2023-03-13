#ifndef CUB_3D_UTILS_H
#define CUB_3D_UTILS_H

struct DVector {
    double x;
    double y;
};

struct IVector {
    int x;
    int y;
};

int checkRgbValues(int r, int g, int b);

int digitToInt(char d);

#endif //CUB_3D_UTILS_H
