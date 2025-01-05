
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_AUTH_PAM_H_
#define _I3LOCK_NG_AUTH_PAM_H_

#include "auth.h"

//! @brief Perform password authentication using PAM
//!
//! @param password password string
//!
//! @return Status Code
lkng_auth_result_t lkng_auth_pam_password(const char *password);

#endif // _I3LOCK_NG_AUTH_PAM_H_
