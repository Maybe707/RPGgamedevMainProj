cmake_minimum_required(VERSION 3.16)
project(miniaudio)

add_library(miniaudio STATIC src/miniaudio.c)
target_include_directories(miniaudio PUBLIC include/)
