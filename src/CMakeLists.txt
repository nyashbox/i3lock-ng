
# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2025 nyashbox and Contributors

find_package(PkgConfig REQUIRED)

pkg_check_modules(XCB REQUIRED IMPORTED_TARGET xcb)
pkg_check_modules(XCB_XKB REQUIRED IMPORTED_TARGET xcb-xkb)
pkg_check_modules(XCB_UTIL REQUIRED IMPORTED_TARGET xcb-util)
pkg_check_modules(XCB_XINERAMA REQUIRED IMPORTED_TARGET xcb-xinerama)
pkg_check_modules(XCB_RANDR REQUIRED IMPORTED_TARGET xcb-randr)
pkg_check_modules(XCB_IMAGE REQUIRED IMPORTED_TARGET xcb-image)
pkg_check_modules(XCB_XRM REQUIRED IMPORTED_TARGET xcb-xrm)
pkg_check_modules(CAIRO REQUIRED IMPORTED_TARGET cairo)
pkg_check_modules(PAM REQUIRED IMPORTED_TARGET pam)
pkg_check_modules(XKB_COMMON REQUIRED IMPORTED_TARGET xkbcommon>=0.5.0)
pkg_check_modules(XKB_COMMON_X11 REQUIRED IMPORTED_TARGET xkbcommon-x11>=0.5.0)

find_library(libev REQUIRED NAMES ev)

set(I3LOCK-NG_SRCS
    core/logging.c
    core/conf.c
    auth/auth.c
    auth/pam.c
    dpi.c
    randr.c
    unlock_indicator.c
    xcb.c
)

configure_file("config.h.in" "config.h" ESCAPE_QUOTES)

add_library(i3lock_ng_obj OBJECT ${I3LOCK-NG_SRCS})
add_library(i3lock-ng::i3lock-ng ALIAS i3lock_ng_obj)
target_include_directories(i3lock_ng_obj
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)
target_link_libraries(i3lock_ng_obj
    PUBLIC 
        PkgConfig::XCB
        PkgConfig::XCB_XKB
        PkgConfig::XCB_UTIL
        PkgConfig::XCB_XINERAMA
        PkgConfig::XCB_RANDR
        PkgConfig::XCB_IMAGE
        PkgConfig::XCB_XRM
        PkgConfig::CAIRO
        PkgConfig::PAM
        PkgConfig::XKB_COMMON
        PkgConfig::XKB_COMMON_X11

        ev
        m
)
target_compile_definitions(i3lock_ng_obj
    PUBLIC 
        _GNU_SOURCE)

add_executable(i3lock-ng i3lock-ng.c)
target_link_libraries(i3lock-ng 
        i3lock-ng::i3lock-ng
)

install(TARGETS i3lock-ng DESTINATION bin)
