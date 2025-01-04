
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2009-2010 Michael Stapelberg and Contributors
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_DPI_H_
#define _I3LOCK_NG_DPI_H_

//! @brief Initialize the DPI setting.
//!
//! This function will use the 'Xft.dpi' X resource if available and fall back
//! to guessing the correct value otherwise.
//!
//! @return Nothing
void init_dpi(void);

//! @brief Get DPI setting value.
//!
//! This function returns the vlaue of the DPI setting.
//!
//! @return DPI setting
long get_dpi_value(void);

//! @brief Convert a logical amount of pixel to an amount of physical pixels.
//!
//! This function will convert a logical amount of pixels (e.g. 2 pixels on a
//! “standard” 96 DPI screen) to a corresponding amount of physical pixels on a
//! standard or retina screen.
//!
//! @param logical logical amount of pixels
//!
//! @return amount of physical pixels
int logical_px(const int logical);

#endif // _I3LOCK_NG_DPI_H_
