cmake_minimum_required(VERSION 3.11)
project(cProject)

include(FetchContent)

FetchContent_Declare(
    cjson
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(cjson)

FetchContent_GetProperties(cjson SOURCE_DIR cjson_SOURCE_DIR)

add_executable(cProject src/main.c)

target_include_directories(cProject PRIVATE ${cjson_SOURCE_DIR})

target_link_libraries(cProject cjson)