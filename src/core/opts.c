
// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 nyashbox and Contributors

#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <core/log.h>
#include <core/opts.h>
#include <cursors.h>

#include <config.h>

// long options
static struct option LONGOPTS[] = {
    {"version", no_argument, NULL, 'v'},
    {"nofork", no_argument, NULL, 'n'},
    {"dpms", no_argument, NULL, 'd'},
    {"color", required_argument, NULL, 'c'},
    {"pointer", required_argument, NULL, 'p'},
    {"debug", no_argument, NULL, 0},
    {"help", no_argument, NULL, 'h'},
    {"no-unlock-indicator", no_argument, NULL, 'u'},
    {"image", required_argument, NULL, 'i'},
    {"raw", required_argument, NULL, 0},
    {"tiling", no_argument, NULL, 't'},
    {"ignore-empty-password", no_argument, NULL, 'e'},
    {"inactivity-timeout", required_argument, NULL, 'I'},
    {"show-failed-attempts", no_argument, NULL, 'f'},
    {"show-keyboard-layout", no_argument, NULL, 'k'},
    {NULL, no_argument, NULL, 0}};

// help message
static const char HELP_MSG[] =
    "Usage: i3lock-ng [OPTION...]\n\n"
    "Options:\n"
    "\t-u, --no-unlock-indicator   Disable the unlock indicator.\n"
    "\t-f, --show-failed-attempts  Show the number of failed attempts.\n"
    "\t-t, --tiling                Display image tiled.\n"
    "\t    --raw FORMAT            Read raw image instead of PNG.\n"
    "\t-p, --pointer {win|default} Use default/Windows pointer.\n"
    "\t-c, --color RRGGBB          Use specified color instead of white.\n"
    "\t-e, --ignore_empty_password Do not validate empty password.\n"
    "\t-i, --image IMAGE           Display the given PNG image instead of\n"
    "\t                            a blank screen.\n"
    "\n"
    "\t    --debug  Enable debug logging.\n"
    "\t-n, --nofork Don't fork after starting.\n"
    "\n"
    "\t-h, --help    Display this help message and exit.\n"
    "\t-v, --version Display version and exit.\n";

void lkng_opts_parse(lkng_config_t *conf, int argc, char **argv) {
  const char *shortopts = "hvndc:p:ui:teI:fk";

  int o;
  int longindex = 0;
  while ((o = getopt_long(argc, argv, shortopts, LONGOPTS, &longindex)) != -1) {
    switch (o) {
    case 'v': {
      printf("i3lock-ng version " I3LOCK_VERSION);

      exit(EXIT_SUCCESS);
    }
    case 'n': {
      LKNG_DEFAULT_CONFIG.dont_fork = true;

      break;
    }
    case 'd': {
      LKNG_LOGGER_FATAL(
          "DPMS support has been removed from i3lock (and was "
          "not returned in i3lock-ng). It will be completely removed soon.\n");

      exit(EXIT_FAILURE);
    }
    case 'I': {
      LKNG_LOGGER_FATAL("Inactivity timeout only makes sense with DPMS, which "
                        "was removed.\n");

      exit(EXIT_FAILURE);
    }
    case 'c': {
      char *arg = optarg;

      // do not process '#'
      if (optarg[0] == '#')
        optarg++;

      if (strlen(arg) != 6 ||
          sscanf(arg, "%06[0-9a-fA-F]", LKNG_DEFAULT_CONFIG.color) != 1) {
        LKNG_LOGGER_FATAL("Invalid color format. Color argument should follow "
                          "default RGB color format: \"#FFFFFF\"\n");

        exit(EXIT_FAILURE);
      }

      break;
    }
    case 'u': {
      LKNG_DEFAULT_CONFIG.unlock_indicator = false;

      break;
    }

    case 'i': {
      LKNG_DEFAULT_CONFIG.image_path = strdup(optarg);

      break;
    }
    case 't': {
      LKNG_DEFAULT_CONFIG.tile = true;

      break;
    }
    case 'p': {
      if (!strcmp(optarg, "win")) {
        LKNG_DEFAULT_CONFIG.cursor_choice = CURS_WIN;
      } else if (!strcmp(optarg, "default")) {
        LKNG_DEFAULT_CONFIG.cursor_choice = CURS_DEFAULT;
      } else {
        LKNG_LOGGER_FATAL("Invalid pointer type given. Expected either \"win\" "
                          "or \"default\"\n");
        exit(EXIT_FAILURE);
      }

      break;
    }
    case 'e': {
      LKNG_DEFAULT_CONFIG.ignore_empty_password = true;

      break;
    }
    case 0: {
      if (strcmp(LONGOPTS[longindex].name, "debug") == 0) {
        LKNG_DEFAULT_CONFIG.debug_mode = true;
        lkng_logger_set_level(&LKNG_DEFAULT_LOGGER, LOG_DEBUG);
        lkng_logger_add_stdout_sink(&LKNG_DEFAULT_LOGGER);
      } else if (strcmp(LONGOPTS[longindex].name, "raw") == 0) {
        // TODO: add code here for correct handling of raw image format
        // image_raw_format = strdup(optarg);
      }
    }
    case 'f': {
      LKNG_DEFAULT_CONFIG.show_failed_attempts = true;

      break;
    }
    case 'k': {
      LKNG_DEFAULT_CONFIG.show_keyboard_layout = true;

      break;
    }
    case 'h':
      /* fallthrough */
    default: {
      printf(HELP_MSG);
      exit(EXIT_SUCCESS);
    }
    }
  }
  return;
}
