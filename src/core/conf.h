
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_CORE_CONF_H_
#define _I3LOCK_NG_CORE_CONF_H_

#include <stdbool.h>

#include <core/log.h>

//! @brief i3lock-ng config
typedef struct {
  lkng_logger_level_t verbosity;     //!< Logger verbosity
  bool dont_fork;                    //!< Fork after starting
  bool beep;                         //!< Enable beeping
  bool tile;                         //!< Should background be tiled
  char color[7];                     //!< Set background color
  char *image_path;                  //!< Background image path
  bool debug_mode;                   //!< Debug mode
  bool show_failed_attempts;         //!< Show failed attempts
  bool unlock_indicator;             //!< Display unlock indicator
  bool show_keyboard_layout;         //!< Show keyboard layout
  bool retry_verification;           //!< Retry verification
  bool ignore_empty_password;        //!< Ignore empty password
  bool skip_repeated_empty_password; //!< Skip repeated empty password
  int cursor_choice;                 //!< Cursor choice
} lkng_config_t;

extern lkng_config_t LKNG_DEFAULT_CONFIG;

#endif // _I3LOCK_NG_CORE_CONF_H_
