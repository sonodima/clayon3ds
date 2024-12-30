#include "Components.h"

#include "Theme.h"

void StatusBar(void)
{
  CLAY(
    CLAY_LAYOUT({
      .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
      .padding = { .y = 2 }
    })
  ) {
    CLAY(
      CLAY_LAYOUT({ .sizing = { .width = CLAY_SIZING_GROW() } })
    ) {}

    CLAY(
      CLAY_TEXT(
        CLAY_STRING("ClayOn3DS by sonodima"),
        CLAY_TEXT_CONFIG({ .textColor = THCOL(PRIMARY), .fontSize = 14 })
      )
    ) {}
  }
}
