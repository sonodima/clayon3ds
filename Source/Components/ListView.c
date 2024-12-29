#include "Include.h"

#include "Constants.h"

void ListView(ListView_NameFetcher nameFetcher, ListView_OnInteraction onInteraction, u32 numItems, u32 curItem)
{
  CLAY(
    CLAY_RECTANGLE({ .color = COLOR_SURF }),
    CLAY_BORDER_OUTSIDE({ .width = 1, .color = COLOR_PRI_L }),
    CLAY_SCROLL({ .vertical = true }),
    CLAY_LAYOUT({
      .sizing = SIZING_GROW,
      .layoutDirection = CLAY_TOP_TO_BOTTOM,
      .padding = { .x = 3, .y = 3 }
    })
  ) {
    for (u32 i = 0; i < numItems; ++i)
    {
      CLAY(
        Clay_OnHover(onInteraction, (intptr_t)i),
        CLAY_RECTANGLE({ .color = curItem == i ? COLOR_PRI_L : COLOR_TRNS }),
        CLAY_LAYOUT({
          .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
          .padding = { .x = 4, .y = 2 }
        })
      ) {
        CLAY(
          CLAY_TEXT(
            nameFetcher(i),
            CLAY_TEXT_CONFIG({
              .textColor = curItem == i ? COLOR_BLK : COLOR_PRI_L,
              .fontSize = 16
            })
          )
        ) {}
      }
    }
  }
}
