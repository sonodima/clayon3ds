#include "Controls.h"

#include "UI/Theme.h"

void ListView(ListView_NameFetcher nameFetcher, ListView_OnInteraction onInteraction, u32 numItems, u32 curItem)
{
  CLAY(
    CLAY_RECTANGLE({ .color = THCOL(BASE200) }),
    CLAY_BORDER_OUTSIDE({ .width = 1, .color = THCOL(BASE100) }),
    CLAY_SCROLL({ .vertical = true }),
    CLAY_LAYOUT({ 
      .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
      .layoutDirection = CLAY_TOP_TO_BOTTOM
    })
  ) {
    for (u32 i = 0; i < numItems; ++i)
    {
      CLAY(
        Clay_OnHover(onInteraction, (intptr_t)i),
        CLAY_RECTANGLE({ .color = curItem == i ? THCOL(BASE100) : (Clay_Color){} }),
        CLAY_LAYOUT({
          .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
          .padding = { .x = 6, .y = 2 }
        })
      ) {
        CLAY(
          CLAY_TEXT(
            nameFetcher(i),
            CLAY_TEXT_CONFIG({
              .textColor = curItem == i ? THCOL(PRIMARY) : THCOL(BASE_CONTENT),
              .fontSize = 16
            })
          )
        ) {}
      }
    }
  }
}
