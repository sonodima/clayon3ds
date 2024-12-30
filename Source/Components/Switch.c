#include "Components.h"

#include <stdint.h>

#include "Theme.h"

void Switch_onInteraction(Clay_ElementId element, Clay_PointerData pointer, intptr_t data)
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

void Switch(Clay_String text, bool* value)
{
  CLAY(
    Clay_OnHover(Switch_onInteraction, (intptr_t)value),
    CLAY_LAYOUT({
      .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() },
      .childGap = 6,
      .layoutDirection = CLAY_LEFT_TO_RIGHT
    })
  ) {
    CLAY(
      CLAY_BORDER_OUTSIDE({
        .width = 1,
        .color = value != NULL && *value ? THCOL(PRIMARY) : THCOL(BASE_CONTENT)
      }),
      CLAY_LAYOUT({
        .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() },
        .padding = { .x = 2, .y = 2 }
      })
    ) {
      if (value != NULL && *value)
      {
        CLAY(
          CLAY_LAYOUT({
            .sizing = {
              .width = CLAY_SIZING_FIXED(10),
              .height = CLAY_SIZING_FIXED(10)
            }
          })
        ) {}
      }

      CLAY(
        CLAY_RECTANGLE({ .color = value != NULL && *value ? THCOL(PRIMARY) : THCOL(BASE_CONTENT) }),
        CLAY_LAYOUT({
          .sizing = {
            .width = CLAY_SIZING_FIXED(10),
            .height = CLAY_SIZING_FIXED(10)
          }
        })
      ) {}

      if (value == NULL || *value == false)
      {
        CLAY(
          CLAY_LAYOUT({
            .sizing = {
              .width = CLAY_SIZING_FIXED(10),
              .height = CLAY_SIZING_FIXED(10)
            }
          })
        ) {}
      }
    }

    CLAY(
      CLAY_TEXT(
        text,
        CLAY_TEXT_CONFIG({
          .textColor = value != NULL && *value ? THCOL(PRIMARY) : THCOL(BASE_CONTENT),
          .fontSize = 16
        })
      )
    ) {}
  }
}
