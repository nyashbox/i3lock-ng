
# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2025 nyashbox and Contributors

cmake_minimum_required(VERSION 3.25.1)

project(
    i3lock-ng
    DESCRIPTION "i3lock with bells and whistles" 
    HOMEPAGE_URL "https://github.com/nyashbox/i3lock-ng"
    VERSION 0.1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_subdirectory(src)

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/CPackConfig.cmake.in
    ${CMAKE_BINARY_DIR}/CPackConfig.cmake
    @ONLY
)
include(${CMAKE_BINARY_DIR}/CPackConfig.cmake)
include(CPack)
