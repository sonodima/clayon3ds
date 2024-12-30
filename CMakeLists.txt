cmake_minimum_required(VERSION 3.14)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Source")
set(CMAKE_DIR "${CMAKE_SOURCE_DIR}/CMake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_DIR}")

project(ClayOn3DS
  VERSION 1.0.0
  DESCRIPTION "Clay running on the 3DS, for no good reason"
  HOMEPAGE_URL "https://github.com/sonodima/clayon3ds"
  LANGUAGES C)

# Obtain the Clay UI library with FetchContent.
include(Clay)

add_executable(ClayOn3DS)
target_sources(ClayOn3DS PRIVATE
  "${SOURCE_DIR}/UI/Components/Components.h"
  "${SOURCE_DIR}/UI/Components/StatusBar.c"
  "${SOURCE_DIR}/UI/Controls/Controls.h"
  "${SOURCE_DIR}/UI/Controls/ListView.c"
  "${SOURCE_DIR}/UI/Controls/Switch.c"
  "${SOURCE_DIR}/UI/Controls/ToggleButton.c"
  "${SOURCE_DIR}/UI/Layouts.c"
  "${SOURCE_DIR}/UI/Theme.c"
  "${SOURCE_DIR}/UI/Theme.h"
  "${SOURCE_DIR}/Data.h"
  "${SOURCE_DIR}/Entry.c"
  "${SOURCE_DIR}/Renderer.c"
  "${SOURCE_DIR}/Renderer.h"
  "${SOURCE_DIR}/Utils.h")
target_include_directories(ClayOn3DS PRIVATE
  "${SOURCE_DIR}"
  "${clay_SOURCE_DIR}")
target_link_libraries(ClayOn3DS PRIVATE citro2d citro3d)

ctr_generate_smdh("ClayOn3DS.smdh"
  NAME "ClayOn3DS ${PROJECT_VERSION}"
  DESCRIPTION "${PROJECT_DESCRIPTION}"
  AUTHOR "sonodima"
  ICON "${CMAKE_SOURCE_DIR}/Icon.png")
ctr_create_3dsx(ClayOn3DS
  SMDH "ClayOn3DS.smdh")
