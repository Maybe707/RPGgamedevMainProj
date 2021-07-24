#ifndef ELEMENTS_FOR_RANDSPRITES_H
#define ELEMENTS_FOR_RANDSPRITES_H

#include "MapObject.h"

const int spriteSet1Height = 7, spriteSet1Width = 8;
const char *spriteSet1[spriteSet1Height] =
        {
                "       ",
                " 0   0 ",
                "       ",
                "       ",
                "       ",
                " 0   0 ",
                "       ",
        };

const int spriteSet2Height = 7, spriteSet2Width = 8;
const char *spriteSet2[spriteSet1Height] =
        {
                "       ",
                " 00 00 ",
                " 0   0 ",
                "       ",
                " 0   0 ",
                " 00 00 ",
                "       ",
        };

const int spriteSet3Height = 7, spriteSet3Width = 8;
const char *spriteSet3[spriteSet1Height] =
        {
                "       ",
                "  0000 ",
                "       ",
                "  00   ",
                " 0     ",
                " 0   0 ",
                "       ",
        };

const char **arraySpritesSet[3] = {spriteSet1, spriteSet2, spriteSet3};

#endif
