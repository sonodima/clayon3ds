#include "Include.h"

#include "Constants.h"

void ListView(ListView_NameFetcher nameFetcher, ListView_OnInteraction onInteraction, u32 numItems, u32 curItem)
{
  CLAY(
    CLAY_RECTANGLE({ .color = COLOR_BASE_200 }),
    CLAY_BORDER_OUTSIDE({ .width = 1, .color = COLOR_BASE_100 }),
    CLAY_SCROLL({ .vertical = true }),
    CLAY_LAYOUT({ .sizing = SIZING_GROW, .layoutDirection = CLAY_TOP_TO_BOTTOM })
  ) {
    for (u32 i = 0; i < numItems; ++i)
    {
      CLAY(
        Clay_OnHover(onInteraction, (intptr_t)i),
        CLAY_RECTANGLE({ .color = curItem == i ? COLOR_BASE_100 : COLOR_TRNS }),
        CLAY_LAYOUT({
          .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
          .padding = { .x = 6, .y = 2 }
        })
      ) {
        CLAY(
          CLAY_TEXT(
            nameFetcher(i),
            CLAY_TEXT_CONFIG({
              .textColor = curItem == i ? COLOR_PRI : COLOR_BASE_CON,
              .fontSize = 16
            })
          )
        ) {}
      }
    }
  }
}
