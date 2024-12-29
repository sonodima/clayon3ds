#include "Include.h"

#include <stdint.h>

#include "Constants.h"

void onToggleButtonInteraction(Clay_ElementId element, Clay_PointerData pointer, intptr_t data)
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
    Clay_OnHover(onToggleButtonInteraction, (intptr_t)value),
    CLAY_BORDER_OUTSIDE({ .width = 1, .color = COLOR_PRI_L }),
    CLAY_RECTANGLE({ .color = value != NULL && *value ? COLOR_PRI_L : COLOR_BLK }),
    CLAY_LAYOUT({
      .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
      .padding = { .x = 8, .y = 4 }
    })
  ) {
    CLAY(
      CLAY_TEXT(
        text,
        CLAY_TEXT_CONFIG({
          .textColor = value != NULL && *value ? COLOR_BLK : COLOR_PRI_L,
          .fontSize = 16
        })
      )
    ) {}
  }
}
