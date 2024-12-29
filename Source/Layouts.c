#include <3ds.h>

#include <clay.h>

#include "Data.h"
#include "Constants.h"
#include "Components/Include.h"

// ===========================
// Shared State
// ===========================

static bool showInfo = true;
static bool hideStatusBar = false;
static u32 curCityIndex = 0;

// ===========================
// Top Screen
// ===========================

Clay_RenderCommandArray topLayout(void)
{
  Clay_BeginLayout();

  CLAY(
    CLAY_RECTANGLE({ .color = COLOR_BLK }),
    CLAY_BORDER({ .bottom = { .width = 2, .color = COLOR_PRI_L } }),
    CLAY_LAYOUT({
      .sizing = SIZING_GROW,
      .padding = { .x = 8, .y = 8 },
      .layoutDirection = CLAY_TOP_TO_BOTTOM
    })
  ) {
    CLAY(
      CLAY_RECTANGLE({ .color = COLOR_SURF }),
      CLAY_BORDER_ALL({ .width = 1, .color = COLOR_PRI_L }),
      CLAY_LAYOUT({
        .sizing = SIZING_GROW,
        .layoutDirection = CLAY_LEFT_TO_RIGHT,
        .padding = { .x = 8, .y = 6 },
        .childGap = 16
      })
    ) {
      CLAY(
        CLAY_ID("CONTENT_VIEW"),
        CLAY_TEXT(
          CITIES[curCityIndex].introduction,
          CLAY_TEXT_CONFIG({ .textColor = COLOR_TEXT, .fontSize = 16 })
        ),
          CLAY_LAYOUT({
            .sizing = { 
              .width = showInfo ? CLAY_SIZING_PERCENT(.5f) : CLAY_SIZING_GROW(),
              .height = CLAY_SIZING_GROW()
            }
          })
      ) {}

      if (showInfo)
      {
        CLAY(
          CLAY_ID("INFO_VIEW"),
          CLAY_TEXT(
            CITIES[curCityIndex].highlights,
            CLAY_TEXT_CONFIG({ .textColor = COLOR_TEXT, .fontSize = 14 })
          ),
          CLAY_LAYOUT({
            .sizing = { .width = CLAY_SIZING_PERCENT(.5f), .height = CLAY_SIZING_GROW() }
          })
        ) {}
      }
    }

    if (hideStatusBar == false)
    {
      StatusBar();
    }
  }

  return Clay_EndLayout();
}

// ===========================
// Bottom Screen
// ===========================

Clay_String CityList_NameFetcher(u32 index)
{
  return CITIES[index].name;
}

void CityList_OnInteraction(Clay_ElementId, Clay_PointerData pointer, intptr_t data)
{
  if (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
  {
    curCityIndex = (u32)data;
  }
}

Clay_RenderCommandArray bottomLayout(void)
{
  Clay_BeginLayout();

  CLAY(
    CLAY_RECTANGLE({ .color = COLOR_BLK }),
    CLAY_LAYOUT({
      .sizing = SIZING_GROW,
      .padding = { .x = 8, .y = 8 },
      .childGap = 8,
    })
  ) {
    ListView(CityList_NameFetcher, CityList_OnInteraction, NUM_CITIES, curCityIndex);

    CLAY(
      CLAY_ID("CONTROLS_VIEW"),
      CLAY_LAYOUT({
        .sizing = SIZING_GROW,
        .layoutDirection = CLAY_TOP_TO_BOTTOM,
        .childGap = 4
      })
    ) {
      ToggleButton(CLAY_STRING("Show Info"), &showInfo);
      ToggleButton(CLAY_STRING("Hide Status Bar"), &hideStatusBar);
    }
  }

  return Clay_EndLayout();
}