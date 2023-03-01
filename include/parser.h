//
// Created by coren on 01/03/2023.
//

#ifndef CUB_3D_PARSER_H
#define CUB_3D_PARSER_H

#include "main.h"


int parse_config_file(const char *fileName, struct Settings *pSettings);

int checkRgbValues(int r, int g, int b);

#endif //CUB_3D_PARSER_H
