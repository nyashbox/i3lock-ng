
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_AUDIO_H_
#define _I3LOCK_NG_AUDIO_H_

#include <stdbool.h>

//! @brief Audio operation result
typedef enum {
  LKNG_AUDIO_SUCCESS, //!< Audio successful
  LKNG_AUDIO_FAILURE, //!< Audio failed
  LKNG_AUDIO_ERROR,   //!< Audio error
} lkng_audio_result_t;

#endif // _I3LOCK_NG_AUDIO_H_
