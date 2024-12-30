#ifndef __CLAYON3DS_CONSTANTS_H
#define __CLAYON3DS_CONSTANTS_H

#include <clay.h>

static const Clay_Color COLOR_TRNS = (Clay_Color){ 0, 0, 0, 0 };
static const Clay_Color COLOR_BASE_100 = (Clay_Color){ 48, 48, 48, 255 };
static const Clay_Color COLOR_BASE_200 = (Clay_Color){ 32, 32, 32, 255 };
static const Clay_Color COLOR_BASE_300 = (Clay_Color){ 18, 18, 18, 255 };
static const Clay_Color COLOR_BASE_CON = (Clay_Color){ 210, 210, 210, 255 };
static const Clay_Color COLOR_PRI = (Clay_Color){ 183, 197, 141, 255 };
static const Clay_Color COLOR_PRI_CON = (Clay_Color){ 0, 0, 0, 255 };
static const Clay_Color COLOR_SEC = (Clay_Color){ 255, 248, 193, 255 };
static const Clay_Color COLOR_SEC_CON = (Clay_Color){ 0, 0, 0, 255 };

static const Clay_Sizing SIZING_FIT = (Clay_Sizing){ .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() };
static const Clay_Sizing SIZING_GROW = (Clay_Sizing){ .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() };

#endif // __CLAYON3DS_CONSTANTS_H
