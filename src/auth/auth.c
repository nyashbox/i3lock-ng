
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include <unistd.h>

#include "auth.h"
#include "pam.h"

lkng_auth_result_t lkng_auth(lkng_auth_t auth_type, void *ctx) {
  switch (auth_type) {
  case LKNG_AUTH_PASSWORD:
    return lkng_auth_pam_password((const char *)ctx);
  default:
    return LKNG_AUTH_ERROR;
  }
}
