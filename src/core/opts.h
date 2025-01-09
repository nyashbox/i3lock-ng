
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_CORE_OPTS_H_
#define _I3LOCK_NG_CORE_OPTS_H_

#include <core/conf.h>

//! @brief Parse command line options
//!
//! This function will parse command line arguments and populate
//! configuration structure
//!
//! @param conf configuration structure
//! @param argc argument count
//! @param argv arguments
//!
//! @return Nothing
void lkng_opts_parse(lkng_config_t *conf, int argc, char **argv);

#endif // _I3LOCK_NG_CORE_OPTS_H_
