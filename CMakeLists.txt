cmake_minimum_required(VERSION 3.25)

project(SDLTutorial VERSION 0.1
                 DESCRIPTION "SDLTutorial"
                 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_VERBOSE_MAKEFILE off)

# release需要手动关闭
set(IS_ENABLE_SANITIZE on CACHE BOOL "" FORCE)

list(APPEND CXX_FLAGS
            "-fno-rtti")

list(APPEND SANITIZE_FLAG "")

if(IS_ENABLE_SANITIZE)
    list(APPEND SANITIZE_FLAG
            "-fno-omit-frame-pointer"
            "-fsanitize=address"
            "-fsanitize=leak"
            "-fsanitize=undefined")
endif()


list(APPEND CXX_FLAGS_DEBUG
            "-Og"
            "-DDBUG")
            #"-Wsuggest-final-types"
            #"-Wsuggest-final-methods"
            #"-Wsuggest-override")

if(IS_ENABLE_SANITIZE)
    list(APPEND CXX_FLAGS_DEBUG ${SANITIZE_FLAG})
endif()

list(APPEND CXX_FLAGS_RELEASE
            "-O3"
            "-Wall"
            "-Wextra"
            "-Werror"
            "-Wconversion"
            "-Wshadow"
            "-Wno-unused-parameter"
            "-Wno-unused")

set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

include(3rd/fmtlib.cmake)

enable_testing()
#if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()

