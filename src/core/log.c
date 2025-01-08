
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <core/log.h>

//! insert new sink
static int _lkng_logger_insert_sink(lkng_logger_t *logger, FILE *sink);

struct lkng_logger_t {
  lkng_logger_level_t level;
  FILE *sinks[LKNG_LOGGER_MAX_SINKS];
  size_t sinks_count;
};

struct lkng_logger_t LKNG_DEFAULT_LOGGER;

void lkng_logger_init(lkng_logger_t *logger) {
  logger->level = LOG_WARN;
  logger->sinks_count = 0;

  // null all thinks
  for (int i = 0; i < LKNG_LOGGER_MAX_SINKS; i++)
    logger->sinks[i] = NULL;
}

lkng_logger_level_t lkng_logger_get_level(lkng_logger_t *logger) {
  return logger->level;
}

void lkng_logger_set_level(lkng_logger_t *logger, lkng_logger_level_t level) {
  logger->level = level;
}

int lkng_logger_add_file_sink(lkng_logger_t *logger, const char *path) {
  FILE *file = NULL;
  int index = logger->sinks_count;

  if (!(file = fopen(path, "a"))) {
    fprintf(stderr, "failed to open log file: %s", strerror(errno));

    return -1;
  } else {
    if (index < LKNG_LOGGER_MAX_SINKS)
      logger->sinks[logger->sinks_count++] = file;
    else
      return -1;
  }

  return 0;
}

int lkng_logger_add_stdout_sink(lkng_logger_t *logger) {
  return _lkng_logger_insert_sink(logger, stdout);
}

int lkng_logger_add_stderr_sink(lkng_logger_t *logger) {
  return _lkng_logger_insert_sink(logger, stderr);
}

void lkng_logger_log(lkng_logger_t *logger, lkng_logger_level_t level,
                     const char *fmt, ...) {
  if (level >= logger->level) {
    va_list args;
    va_start(args, fmt);

    // write logging message to all sinks
    for (int i = 0; i < logger->sinks_count; i++) {
      FILE *sink = logger->sinks[i];

      // don't write to NULLed sinks
      if (sink)
        vfprintf(sink, fmt, args);
    }

    va_end(args);
  }
}

int lkng_logger_close_file_sinks(lkng_logger_t *logger) {
  for (int i = 0; i < logger->sinks_count; i++) {
    FILE *sink = logger->sinks[i];

    // don't close stderr, stdout and NULL sinks
    if (sink != stderr && sink != stdout && sink != NULL) {
      fclose(sink);
      sink = NULL;
    }
  }

  return 0;
}

static int _lkng_logger_insert_sink(lkng_logger_t *logger, FILE *sink) {
  int index = logger->sinks_count;

  // check if still have space for new sinks
  if (index < LKNG_LOGGER_MAX_SINKS)
    logger->sinks[logger->sinks_count++] = stderr;
  else
    return -1;

  // return 0 on success
  return 0;
}
