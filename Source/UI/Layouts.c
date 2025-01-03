#include <3ds.h>

#include <clay.h>

#include "Components/Components.h"
#include "Controls/Controls.h"
#include "Theme.h"
#include "Data.h"

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
    CLAY_RECTANGLE({ .color = THCOL(BASE300) }),
    CLAY_BORDER({ .bottom = { .width = 2, .color = THCOL(PRIMARY) } }),
    CLAY_LAYOUT({
      .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
      .padding = { .x = 8, .y = 8 },
      .layoutDirection = CLAY_TOP_TO_BOTTOM
    })
  ) {
    CLAY(
      CLAY_RECTANGLE({ .color = THCOL(BASE200), .cornerRadius = CLAY_CORNER_RADIUS(8) }),
      CLAY_BORDER_OUTSIDE_RADIUS(1, THCOL(BASE100), 8),
      CLAY_LAYOUT({
        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
        .layoutDirection = CLAY_LEFT_TO_RIGHT,
        .padding = { .x = 8, .y = 6 },
        .childGap = 16
      })
    ) {
      CLAY(
        CLAY_ID("CONTENT_VIEW"),
        CLAY_TEXT(
          CITIES[curCityIndex].introduction,
          CLAY_TEXT_CONFIG({ .textColor = THCOL(BASE_CONTENT), .fontSize = 16 })
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
            CLAY_TEXT_CONFIG({ .textColor = THCOL(BASE_CONTENT), .fontSize = 14 })
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

Clay_String CityList_nameFetcher(u32 index)
{
  return CITIES[index].name;
}

void CityList_onInteraction(Clay_ElementId, Clay_PointerData pointer, intptr_t data)
{
  if (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
  {
    curCityIndex = (u32)data;
  }
}

Clay_String ThemeList_nameFetcher(u32 index)
{
  switch ((AppTheme)index)
  {
  case THEME_DARK: return CLAY_STRING("Dark");
  case THEME_LIGHT: return CLAY_STRING("Light");
  case THEME_NORD: return CLAY_STRING("Nord");
  case THEME_MACCHIATO: return CLAY_STRING("Macchiato");
  default: return CLAY_STRING("Untitled");
  }
}

void ThemeList_onInteraction(Clay_ElementId, Clay_PointerData pointer, intptr_t data)
{
  if (pointer.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
  {
    Theme_setActive((AppTheme)data);
  }
}

Clay_RenderCommandArray bottomLayout(void)
{
  Clay_BeginLayout();

  CLAY(
    CLAY_RECTANGLE({ .color = THCOL(BASE300) }),
    CLAY_LAYOUT({
      .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
      .padding = { .x = 8, .y = 8 },
      .childGap = 8,
    })
  ) {
    ListView(CityList_nameFetcher, CityList_onInteraction, NUM_CITIES, curCityIndex);

    CLAY(
      CLAY_ID("CONTROLS_VIEW"),
      CLAY_LAYOUT({
        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
        .layoutDirection = CLAY_TOP_TO_BOTTOM,
        .childGap = 4
      })
    ) {
      Switch(CLAY_STRING("Show Info"), &showInfo);
      Switch(CLAY_STRING("Hide Status Bar"), &hideStatusBar);

      ListView(ThemeList_nameFetcher, ThemeList_onInteraction, THEME_MAX, (u32)Theme_getActive());
    }
  }

  return Clay_EndLayout();
}
