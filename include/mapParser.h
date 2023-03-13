#ifndef CUB_3D_MAPPARSER_H
#define CUB_3D_MAPPARSER_H

#include "init.h"

int parseMapFile(const char *fileName, struct Settings *pSettings);

int setNbLinesAndNbColumns(const char *fileName, struct Settings *pSettings);

#endif //CUB_3D_MAPPARSER_H
