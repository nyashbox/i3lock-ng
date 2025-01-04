
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#ifndef _I3LOCK_NG_CORE_LOGGING_H_
#define _I3LOCK_NG_CORE_LOGGING_H_

#define LKNG_LOGGER_MAX_SINKS 4

//! @brief structure representing logger object
typedef struct lkng_logger_t lkng_logger_t;

extern lkng_logger_t LKNG_DEFAULT_LOGGER;

//! @brief logging levels
typedef enum {
  LOG_DEBUG, //!< 'debug' level
  LOG_INFO,  //!< 'info' level
  LOG_WARN,  //!< 'warn' level
  LOG_ERROR, //!< 'error' level
  LOG_FATAL  //!< 'fatal' level
} lkng_logger_level_t;

//! @brief Initialize logger
//!
//! This function MUST be called before any operations with the logger.
//! When called, this function will set default logger values.
//!
//! @param logger logger object (pointer)
//!
//! @return Nothing
void lkng_logger_init(lkng_logger_t *logger);

//! @brief Log message
//!
//! This function will write log message to the sinks specified
//! in the logger object. In common cases convenient macros should
//! be used
//!
//! @param logger logger object (pointer)
//! @param level log level
//! @param fmt log message format
//!
//! @see lkng_logger_level_t
//!
//! @return Nothing
void lkng_logger_log(lkng_logger_t *logger, lkng_logger_level_t level,
                     const char *fmt, ...);

//! @brief Add file sink
//!
//! This function adds new file sink to the logger object. It will
//! correctly open log file, and close it when logger object will be destroyed.
//!
//! @param logger logger object (pointer)
//! @param path path to the log file
//!
//! @return Status Code
int lkng_logger_add_file_sink(lkng_logger_t *logger, const char *path);

//! @brief Add stdout sink
//!
//! This function adds 'stdout' sink to the logger object.
//!
//! @param logger logger object (pointer)
//!
//! @return Status Code
int lkng_logger_add_stdout_sink(lkng_logger_t *logger);

//! @brief Add stderr sink
//!
//! This function adds 'stderr' sink to the logger object.
//!
//! @param logger logger object (pointer)
//!
//! @return Status Code
int lkng_logger_add_stderr_sink(lkng_logger_t *logger);

//! @brief Close all file sinks
//!
//! When called, this function closes all open file sinks.
//!
//! @param logger logger object (pointer)
//!
//! @return Status Code
int lkng_logger_close_file_sinks(lkng_logger_t *logger);

//! @brief Set logger logging level
//!
//! When called, this function will update logging level in the specified
//! logger object
//!
//! @param logger logger object (pointer)
//! @param level logger desired level
//!
//! @return Nothing
void lkng_logger_set_level(lkng_logger_t *logger, lkng_logger_level_t level);

//! @brief Get logger logging level
//!
//! @param logger logger object (pointer)
//!
//! @return Current logging level
lkng_logger_level_t lkng_logger_get_level(lkng_logger_t *logger);

//! @defgroup LogMacros Logger macros
//! @brief Collection of macros for simple logging
//!
//! These macros are used for convenient writing log message
//! to the standard logger object
//!
//! @{

#define LKNG_LOGGER_DEBUG(...)                                                 \
  lkng_logger_log(&LKNG_DEFAULT_LOGGER, LOG_DEBUG, __VA_ARGS__)
#define LKNG_LOGGER_INFO(...)                                                  \
  lkng_logger_log(&LKNG_DEFAULT_LOGGER, LOG_INFO, __VA_ARGS__)
#define LKNG_LOGGER_WARN(...)                                                  \
  lkng_logger_log(&LKNG_DEFAULT_LOGGER, LOG_WARN, __VA_ARGS__)
#define LKNG_LOGGER_ERROR(...)                                                 \
  lkng_logger_log(&LKNG_DEFAULT_LOGGER, LOG_ERROR, __VA_ARGS__)
#define LKNG_LOGGER_FATAL(...)                                                 \
  lkng_logger_log(&LKNG_DEFAULT_LOGGER, LOG_FATAL, __VA_ARGS__)

//! @}

#endif // _I3LOCK_NG_CORE_LOGGING_H_
