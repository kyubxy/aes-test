cmake_minimum_required(VERSION 3.1)

project(aestest)

set(SOURCES
    src/main.cpp
    src/softwareaes.cpp
)

add_executable(aestest ${SOURCES})

target_include_directories(aestest
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
