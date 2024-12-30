#ifndef __CLAYON3DS_THEME_H
#define __CLAYON3DS_THEME_H

#include <clay.h>

typedef enum
{
  COLOR_BASE100,
  COLOR_BASE200,
  COLOR_BASE300,
  COLOR_BASE_CONTENT,
  COLOR_PRIMARY,
  COLOR_PRIMARY_CONTENT,
  COLOR_SECONDARY,
  COLOR_SECONDARY_CONTENT,
  COLOR_MAX,
} AppColorKey;

typedef enum
{
  THEME_LIGHT,
  THEME_DARK,
  THEME_MAX,
} AppTheme;

#define THCOL(key) Theme_getColor(COLOR_##key)

void Theme_setTheme(AppTheme value);
AppTheme Theme_getTheme();

Clay_Color Theme_getColor(AppColorKey key);

#endif // __CLAYON3DS_THEME_H
