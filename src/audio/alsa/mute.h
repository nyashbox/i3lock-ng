
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_AUDIO_ALSA_MUTE_H_
#define _I3LOCK_NG_AUDIO_ALSA_MUTE_H_

#include <audio/audio.h>

//! @brief Initialize ALSA mixers
//!
//! @param mixer_ids NULL-terminated array of mixer IDs (strings) in
//!                  format "device:element" (e.g. "default:Master").
//!
//! @return Result code
lkng_audio_result_t lkng_audio_backend_init(const char **mixer_ids);

//! @brief Mute all mixers
//!
//! @return Result code
lkng_audio_result_t lkng_audio_backend_mute(void);

//! @brief Unmute all mixers
//!
//! @return Result code
lkng_audio_result_t lkng_audio_backend_unmute(void);

//! @brief Free resources
//!
//! @return Nothing
void lkng_audio_backend_free(void);

#endif // _I3LOCK_NG_AUDIO_ALSA_MUTE_H_
