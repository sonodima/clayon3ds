#ifndef __CLAYON3DS_CONSTANTS_H
#define __CLAYON3DS_CONSTANTS_H

#include <clay.h>

static const Clay_Color COLOR_BLK = (Clay_Color){ 18, 18, 18, 255 };
static const Clay_Color COLOR_SURF = (Clay_Color){ 32, 32, 32, 255 };
static const Clay_Color COLOR_TEXT = (Clay_Color){ 255, 248, 193, 255 };
static const Clay_Color COLOR_PRI_L = (Clay_Color){ 183, 197, 141, 255 };
static const Clay_Color COLOR_PRI_D = (Clay_Color){ 137, 145, 110, 255 };

static const Clay_Sizing SIZING_FIT = (Clay_Sizing){ .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() };
static const Clay_Sizing SIZING_GROW = (Clay_Sizing){ .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() };

#endif // __CLAYON3DS_CONSTANTS_H
