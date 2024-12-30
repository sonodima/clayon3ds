#include "Include.h"

#include <stdint.h>

#include "Constants.h"

void ToggleButton_OnInteraction(Clay_ElementId element, Clay_PointerData pointer, intptr_t data)
{
  if (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
  {
    bool* value = (bool*)data;
    if (value != NULL)
    {
      *value = !*value;
    }
  }
}

void ToggleButton(Clay_String text, bool* value)
{
  CLAY(
    Clay_OnHover(ToggleButton_OnInteraction, (intptr_t)value),
    CLAY_LAYOUT({
      .sizing = SIZING_FIT,
      .childGap = 6,
      .layoutDirection = CLAY_LEFT_TO_RIGHT
    })
  ) {
    CLAY(
      CLAY_BORDER_OUTSIDE({
        .width = 1,
        .color = value != NULL && *value ? COLOR_PRI : COLOR_BASE_CON
      }),
      CLAY_LAYOUT({ .sizing = SIZING_FIT, .padding = { .x = 2, .y = 2 } })
    ) {
      CLAY(
        CLAY_RECTANGLE({ .color = value != NULL && *value ? COLOR_PRI : COLOR_BASE_100 }),
        CLAY_LAYOUT({
          .sizing = {
            .width = CLAY_SIZING_FIXED(10),
            .height = CLAY_SIZING_FIXED(10)
          }
        })
      ) {}
    }

    CLAY(
      CLAY_TEXT(
        text,
        CLAY_TEXT_CONFIG({
          .textColor = value != NULL && *value ? COLOR_PRI : COLOR_BASE_CON,
          .fontSize = 16
        })
      )
    ) {}
  }
}
