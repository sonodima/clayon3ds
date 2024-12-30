#include "Theme.h"

static const Clay_Color THEME_DARK_DATA[COLOR_MAX] =
{
  { 48, 48, 48, 255 },     // COLOR_BASE100
  { 32, 32, 32, 255 },     // COLOR_BASE200
  { 18, 18, 18, 255 },  // COLOR_BASE300
  { 210, 210, 210, 255 },  // COLOR_BASE_CONTENT
  { 183, 197, 141, 255 },  // COLOR_PRIMARY
  { 0, 0, 0, 255 },        // COLOR_PRIMARY_CONTENT
  { 255, 248, 193, 255 },  // COLOR_SECONDARY
  { 0, 0, 0, 255 }         // COLOR_SECONDARY_CONTENT
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
  { 255, 255, 255, 255 }   // COLOR_SECONDARY_CONTENT
};

static AppTheme curTheme = THEME_DARK;
static Clay_Color* curColors = THEME_DARK_DATA;

void Theme_setTheme(AppTheme value)
{
  if (value >= 0 && value < THEME_MAX)
  {
    curTheme = value;
    switch (value)
    {
    case THEME_DARK:
      curColors = THEME_DARK_DATA;
      break;
    case THEME_LIGHT:
      curColors = THEME_LIGHT_DATA;
      break;
    }
  }
}

AppTheme Theme_getTheme()
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
