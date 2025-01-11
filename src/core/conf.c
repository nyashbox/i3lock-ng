
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#include <cursors.h>
#include <errno.h>
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ini.h>

#include <core/conf.h>
#include <core/log.h>

// convenient macros for parsing config files
#define CONFIG_MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
#define CONFIG_READ_BOOL(value) strcmp(value, "true") == 0 ? true : false

lkng_config_t LKNG_DEFAULT_CONFIG = {.verbosity = LOG_ERROR,
                                     .dont_fork = false,
                                     .beep = false,
                                     .tile = false,
                                     .color = "a3a3a3",
                                     .image_path = NULL,
                                     .debug_mode = false,
                                     .show_failed_attempts = false,
                                     .unlock_indicator = true,
                                     .show_keyboard_layout = false,
                                     .retry_verification = true,
                                     .ignore_empty_password = false,
                                     .skip_repeated_empty_password = false,
                                     .cursor_choice = CURS_NONE};

static int _lkng_config_file_handler(void *user, const char *section,
                                     const char *name, const char *value) {
  lkng_config_t *config = (lkng_config_t *)user;

  if (CONFIG_MATCH("core", "fork")) {
    config->dont_fork = !(CONFIG_READ_BOOL(value));
  } else if (CONFIG_MATCH("core", "debug")) {
    config->debug_mode = CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("background", "color")) {
    if (value[0] != '#')
      strcpy(config->color, value);
    else
      strcpy(config->color, value + 1);
  } else if (CONFIG_MATCH("background", "tile")) {
    config->debug_mode = CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("background", "image")) {
    config->image_path = strdup(value);
  } else if (CONFIG_MATCH("widgets", "unlock_indicator")) {
    config->unlock_indicator - CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("widgets", "keyboard_layout")) {
    config->show_keyboard_layout = CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("widgets", "failed_attempts")) {
    config->show_failed_attempts = CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("auth", "retry_verification")) {
    config->skip_repeated_empty_password = CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("auth", "skip_repeated_empty_password")) {
    config->skip_repeated_empty_password = CONFIG_READ_BOOL(value);
  } else if (CONFIG_MATCH("auth", "ignore_empty_password")) {
    config->ignore_empty_password = CONFIG_READ_BOOL(value);
  }

  return 0;
}

lkng_config_result_t lkng_config_parse(lkng_config_t *conf,
                                       const char **files) {
  for (int i = 0; files[i]; i++) {
    FILE *fd = NULL;
    const char *file = files[i];

    // check if file exists and readable
    if (access(file, R_OK) != 0) {
      LKNG_LOGGER_DEBUG(
          "(Core/Config) File \"%s\" is not readable, skipping...\n", file);
      continue;
    }
    LKNG_LOGGER_DEBUG("(Core/Config) File \"%s\" is open and readable!\n",
                      file);

    // open config file
    if (!(fd = fopen(file, "r"))) {
      LKNG_LOGGER_ERROR(
          "(Core/Config) Failed to open configuration file \"%s\": %s\n",
          strerror(errno));

      return LKNG_CONFIG_ERROR;
    }

    // parse configuration file
    if (ini_parse_file(fd, _lkng_config_file_handler, &LKNG_DEFAULT_CONFIG) <
        0) {
      LKNG_LOGGER_ERROR("(Config) Failed to parse configuration file %s\n",
                        file);

      return LKNG_CONFIG_ERROR;
    }

    fclose(fd);
  }

  return LKNG_CONFIG_SUCCESS;
}

char **lkng_config_get_default_paths(void) {
  const char *environments[] = {"XDG_CONFIG_HOME", "XDG_CONFIG_DIRS", "HOME"};
  const char *suffix = "i3lock-ng/i3lock-ng.ini";

  int files_count;
  for (files_count = 0; environments[files_count]; files_count++)
    ;

  char **files = malloc(sizeof(char *) * (files_count + 1));
  if (!files) {
    LKNG_LOGGER_FATAL(
        "(Config) Failed to allocate memory for configuration files array!\n");

    return NULL;
  }

  char *env;
  int counter = 0;

  // $XDG_CONFIG_HOME/i3lock-ng/i3lock-ng.ini
  if ((env = getenv("XDG_CONFIG_HOME")))
    asprintf(&files[counter++], "%s/%s", env, suffix);

  // $XGD_CONFIG_DIRS/i3lock-ng/i3lock-ng.ini
  if ((env = getenv("XDG_CONFIG_DIRS")))
    asprintf(&files[counter++], "%s/%s", env, suffix);

  // $HOME/.config/i3lock-ng/i3lock-ng.ini
  if ((env = getenv("HOME")))
    asprintf(&files[counter++], "%s/.config/%s", env, suffix);

  // trailing NULL
  files[counter] = NULL;

  return files;
};

void lkng_config_free_default_paths(char **paths) {
  for (int i = 0; paths[i]; i++)
    free((char *)paths[i]);

  free(paths);
}
