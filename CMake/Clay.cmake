include(FetchContent)

FetchContent_Declare(Clay
  GIT_REPOSITORY https://github.com/nicbarker/clay.git
  GIT_TAG        main)

FetchContent_GetProperties(Clay)
if(NOT clay_POPULATED)
  FetchContent_Populate(Clay)
endif()
