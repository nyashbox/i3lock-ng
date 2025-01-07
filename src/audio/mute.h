
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_AUDIO_MUTE_H_
#define _I3LOCK_NG_AUDIO_MUTE_H_

#include <stdbool.h>

#include <audio/alsa/mute.h>
#include <audio/audio.h>

//! @brief Initialize audio module
//!
//! This function initializes audio module of i3lock-ng. Context argument
//! should be used for passing backend-specific initialization data.
//!
//! @param ctx Initialization context
//!
//! @return Result code
lkng_audio_result_t lkng_audio_init(void *ctx);

//! @brief Mute audio devices
//!
//! When called, this function mutes all registered audio devices. Audio system
//! should be initialized before this call is performed.
//!
//! @return Nothing
lkng_audio_result_t lkng_audio_mute(void);

//! @brief Unmute audio devices
//!
//! When called, this function unmutes all registered audio devices.
//! Audio system should be initialized before using this method.
//!
//! @return Nothing
//!
//! @see lkng_audio_unmute()
//! @see lkng_audio_init()
lkng_audio_result_t lkng_audio_unmute(void);

//! @brief Free audio resources
//!
//! This function cleans up audio system.
//!
//! @return Nothing
//!
//! @see lkng_audio_init()
void lkng_audio_free(void);

//
// inlines
//

inline lkng_audio_result_t lkng_audio_init(void *ctx) {
  return lkng_audio_backend_init((const char **)ctx);
}

inline lkng_audio_result_t lkng_audio_mute(void) {
  return lkng_audio_backend_mute();
}

inline lkng_audio_result_t lkng_audio_unmute(void) {
  return lkng_audio_backend_unmute();
}

inline void lkng_audio_free(void) { lkng_audio_backend_free(); }

#endif // _I3LOCK_NG_AUDIO_MUTE_H_
