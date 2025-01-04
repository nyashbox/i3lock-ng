
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2009-2010 Michael Stapelberg and Contributors
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_H_
#define _I3LOCK_NG_H_

//! @brief Print debug output
//!
//! This macro will only print debug output when started with --debug.
//! This is important because xautolock (for example) closes stdout/stderr by
//! default, so just printing something to stdout will lead to the data ending
//! up on the X11 socket (!).
//!
//! @return Nothing
#define DEBUG(fmt, ...)                                                        \
  do {                                                                         \
    if (debug_mode) {                                                          \
      fprintf(stderr, "[i3lock-debug] " fmt, ##__VA_ARGS__);                   \
    }                                                                          \
  } while (0)

#endif // _I3LOCK_NG_H_
