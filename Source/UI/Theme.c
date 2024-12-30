#include "Theme.h"

#include <3ds.h>

#include "Utils.h"

static const Clay_Color THEME_DARK_DATA[COLOR_MAX] =
{
  { 48, 48, 48, 255 },     // COLOR_BASE100
  { 32, 32, 32, 255 },     // COLOR_BASE200
  { 18, 18, 18, 255 },     // COLOR_BASE300
  { 210, 210, 210, 255 },  // COLOR_BASE_CONTENT
  { 183, 197, 141, 255 },  // COLOR_PRIMARY
  { 0, 0, 0, 255 },        // COLOR_PRIMARY_CONTENT
  { 255, 248, 193, 255 },  // COLOR_SECONDARY
  { 0, 0, 0, 255 },        // COLOR_SECONDARY_CONTENT
};

static const Clay_Color THEME_LIGHT_DATA[COLOR_MAX] =
{
  { 240, 240, 240, 255 },  // COLOR_BASE100
  { 230, 230, 230, 255 },  // COLOR_BASE200
  { 220, 220, 220, 255 },  // COLOR_BASE300
  { 60, 60, 60, 255 },     // COLOR_BASE_CONTENT
  { 49, 79, 117, 255 },    // COLOR_PRIMARY
  { 255, 255, 255, 255 },  // COLOR_PRIMARY_CONTENT
  { 125, 105, 55, 255 },   // COLOR_SECONDARY
  { 255, 255, 255, 255 },  // COLOR_SECONDARY_CONTENT
};

static const Clay_Color THEME_NORD_DATA[COLOR_MAX] =
{
  { 67, 76, 94, 255 },     // COLOR_BASE100
  { 59, 66, 82, 255 },     // COLOR_BASE200
  { 46, 52, 64, 255 },     // COLOR_BASE300
  { 236, 239, 244, 255 },  // COLOR_BASE_CONTENT
  { 94, 129, 172, 255 },   // COLOR_PRIMARY
  { 46, 52, 64, 255 },     // COLOR_PRIMARY_CONTENT
  { 143, 188, 187, 255 },  // COLOR_SECONDARY
  { 46, 52, 64, 255 },     // COLOR_SECONDARY_CONTENT
};

static const Clay_Color THEME_MACCHIATO_DATA[COLOR_MAX] =
{
  { 49, 50, 68, 255 },     // COLOR_BASE100
  { 30, 30, 46, 255 },     // COLOR_BASE200
  { 17, 17, 27, 255 },     // COLOR_BASE300
  { 205, 214, 244, 255 },  // COLOR_BASE_CONTENT
  { 250, 179, 135, 255 },  // COLOR_PRIMARY
  { 17, 17, 27, 255 },     // COLOR_PRIMARY_CONTENT
  { 203, 166, 247, 255 },  // COLOR_SECONDARY
  { 17, 17, 27, 255 },     // COLOR_SECONDARY_CONTENT
};

static AppTheme curTheme = THEME_DARK;
static Clay_Color curColors[COLOR_MAX];

static const Clay_Color* tarColors = THEME_DARK_DATA;
static float trnProgress = 0.f;

void Theme_updateTransition(float deltaTime)
{
  if (trnProgress < 1.0f)
  {
    trnProgress += deltaTime;
    if (trnProgress > 1.f)
    {
      trnProgress = 1.f;
    }

    for (u32 i = 0; i < COLOR_MAX; ++i)
    {
      Clay_Color* current = &curColors[i];
      const Clay_Color* target = &tarColors[i];
      current->r = (u8)LERP(current->r, target->r, trnProgress);
      current->g = (u8)LERP(current->g, target->g, trnProgress);
      current->b = (u8)LERP(current->b, target->b, trnProgress);
      current->a = (u8)LERP(current->a, target->a, trnProgress);
    }
  }
}

void Theme_setActive(AppTheme value)
{
  if (value >= 0 && value < THEME_MAX)
  {
    trnProgress = 0.f;
    curTheme = value;
    switch (value)
    {
    case THEME_DARK:
      tarColors = THEME_DARK_DATA;
      break;
    case THEME_LIGHT:
      tarColors = THEME_LIGHT_DATA;
      break;
    case THEME_NORD:
      tarColors = THEME_NORD_DATA;
      break;
    case THEME_MACCHIATO:
      tarColors = THEME_MACCHIATO_DATA;
      break;
    }

  }
}

AppTheme Theme_getActive()
{
  return curTheme;
}

Clay_Color Theme_getColor(AppColorKey key)
{
  if (key >= 0 && key < COLOR_MAX)
  {
    return curColors[key];
  }

  return (Clay_Color){ 0, 0, 0, 255 };
}
