
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2009-2010 Michael Stapelberg and Contributors
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_UNLOCK_INDICATOR_H_
#define _I3LOCK_NG_UNLOCK_INDICATOR_H_

#include <xcb/xcb.h>

typedef enum {
  STATE_STARTED = 0,     //!< Default state
  STATE_KEY_PRESSED = 1, //!< Key was pressed, show unlock indicator
  STATE_KEY_ACTIVE = 2,  //!< A key was pressed recently, highlight part of the
                         //!< unlock indicator.
  STATE_BACKSPACE_ACTIVE = 3, //!< Backspace was pressed recently, highlight
                              //!< part of the unlock indicator in red.
  STATE_NOTHING_TO_DELETE =
      4, //!< Backspace was pressed, but there is nothing to delete.
} unlock_state_t;

typedef enum {
  STATE_AUTH_IDLE = 0,   //!< No authenticator interaction at the moment
  STATE_AUTH_VERIFY = 1, //!< Currently verifying the password via authenticator
  STATE_AUTH_LOCK = 2,   //!< Currently locking the screen
  STATE_AUTH_WRONG = 3,  //!< The password was wrong
  STATE_I3LOCK_LOCK_FAILED = 4, //!< i3lock-ng failed to load
} auth_state_t;

void free_bg_pixmap(void);
void draw_image(xcb_pixmap_t bg_pixmap, uint32_t *resolution);
void redraw_screen(void);
void clear_indicator(void);

#endif // _I3LOCK_NG_UNLOCK_INDICATOR_H_
