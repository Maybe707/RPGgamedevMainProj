#ifndef ELEMENTSFOR_RANDSPRITES
#define ELEMENTSFOR_RANDSPRITES

#include "Map_Objects.h"

const int sprite_set1_height = 7, sprite_set1_width = 8;
const char* Sprite_Set_1[sprite_set1_height] =
{
    "       ",
    " 0   0 ",
    "       ",
    "       ",
    "       ",
    " 0   0 ",
    "       ",
};

const int sprite_set2_height = 7, sprite_set2_width = 8;
const char* Sprite_Set_2[sprite_set1_height] =
{
    "       ",
    " 00 00 ",
    " 0   0 ",
    "       ",
    " 0   0 ",
    " 00 00 ",
    "       ",
};

const int sprite_set3_height = 7, sprite_set3_width = 8;
const char* Sprite_Set_3[sprite_set1_height] =
{
    "       ",
    "  0000 ",
    "       ",
    "  00   ",
    " 0     ",
    " 0   0 ",
    "       ",
};

const char** Array_Sprites_Set[3] = {Sprite_Set_1, Sprite_Set_2, Sprite_Set_3};

#endif
