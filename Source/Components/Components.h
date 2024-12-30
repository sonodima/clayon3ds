#ifndef __CLAYON3DS_COMPONENTS_H
#define __CLAYON3DS_COMPONENTS_H

#include <stdbool.h>

#include <3ds.h>

#include <clay.h>

typedef Clay_String(*ListView_NameFetcher)(u32 index);
typedef void(*ListView_OnInteraction)(Clay_ElementId, Clay_PointerData pointer, intptr_t /* u32 */ data);

void ListView(ListView_NameFetcher nameFetcher, ListView_OnInteraction onInteraction, u32 numItems, u32 curItem);
void StatusBar(void);
void ToggleButton(Clay_String text, bool* value);
void Switch(Clay_String text, bool* value);

#endif // __CLAYON3DS_COMPONENTS_H
