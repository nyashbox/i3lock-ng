
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2009-2010 Michael Stapelberg and Contributors
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_RANDR_H_
#define _I3LOCK_NG_RANDR_H_

#include <stdint.h>
#include <xcb/xcb.h>

typedef struct Rect {
  int16_t x;
  int16_t y;
  uint16_t width;
  uint16_t height;
} Rect;

extern int xr_screens;
extern Rect *xr_resolutions;

void randr_init(int *event_base, xcb_window_t root);
void randr_query(xcb_window_t root);

#endif // _I3LOCK_NG_RANDR_H_
