
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_AUTH_H_
#define _I3LOCK_NG_AUTH_H_

//! @brief Authentication type
typedef enum {
  LKNG_AUTH_PASSWORD //!< Perform password-based authentication
} lkng_auth_t;

//! @brief Authentication status
typedef enum {
  LKNG_AUTH_SUCCESS, //!< Authentication successful
  LKNG_AUTH_FAILURE, //!< Authentication failed
  LKNG_AUTH_ERROR    //!< Authentication error
} lkng_auth_result_t;

//! @brief Perform user authentication
//!
//! This function performs user authentication. One may use different
//! authentication types.
//!
//! @param auth_type Authentication type
//! @param ctx Authentication context
//!
//! @return Authentication result (code)
lkng_auth_result_t lkng_auth(lkng_auth_t auth_type, void *ctx);

#endif // _I3LOCK_NG_AUTH_H_
