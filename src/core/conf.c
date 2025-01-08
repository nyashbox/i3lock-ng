
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#include <cursors.h>
#include <stddef.h>

#include <core/conf.h>

lkng_config_t LKNG_DEFAULT_CONFIG = {.verbosity = LOG_ERROR,
                                     .dont_fork = false,
                                     .beep = false,
                                     .tile = false,
                                     .color = "a3a3a3",
                                     .image_path = NULL,
                                     .debug_mode = false,
                                     .show_failed_attempts = false,
                                     .unlock_indicator = true,
                                     .show_keyboard_layout = false,
                                     .retry_verification = true,
                                     .ignore_empty_password = false,
                                     .skip_repeated_empty_password = false,
                                     .cursor_choice = CURS_NONE};
