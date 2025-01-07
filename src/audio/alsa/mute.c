#include <alsa/asoundlib.h>

#include <audio/alsa/mute.h>
#include <audio/audio.h>
#include <core/logging.h>

typedef struct {
  snd_mixer_t *mixer_handle;
  snd_mixer_elem_t *element_id;
} _mixer_t;

static _mixer_t *_mixers = NULL;
static size_t _mixer_count = 0;

lkng_audio_result_t lkng_audio_backend_init(const char **mixer_ids) {
  LKNG_LOGGER_DEBUG("(Audio/ALSA) Initializing mixers\n");
  for (/* blank */; mixer_ids[_mixer_count]; _mixer_count++)
    ;

  _mixers = malloc(sizeof(_mixer_t) * _mixer_count);
  if (!_mixers) {
    LKNG_LOGGER_FATAL(
        "(Audio/ALSA) Failed to allocate memory for the mixers\n");

    return LKNG_AUDIO_ERROR;
  }

  for (int i = 0; i < _mixer_count; i++) {
    char *mixer_str = strdup(mixer_ids[i]);
    LKNG_LOGGER_DEBUG("(Audio/ALSA) Initializing mixer \"%s\"\n", mixer_str);

    const char *device = strtok(mixer_str, ":");
    const char *element = strtok(NULL, ":");

    int res;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;

    LKNG_LOGGER_DEBUG("(Audio/ALSA) Trying to open ALSA mixer...\n");
    if ((res = snd_mixer_open(&handle, 0)) < 0) {
      LKNG_LOGGER_FATAL("(Audio/ALSA) Failed to open ALSA mixer: %s\n",
                        snd_strerror(res));

      return LKNG_AUDIO_ERROR;
    }

    LKNG_LOGGER_DEBUG(
        "(Audio/ALSA) Trying to attach card \"%s\" to ALSA mixer...\n", device);
    if ((res = snd_mixer_attach(handle, device)) < 0) {
      LKNG_LOGGER_FATAL("(Audio/ALSA) Failed to attach card: %s\n",
                        snd_strerror(res));

      lkng_audio_backend_free();
      return LKNG_AUDIO_ERROR;
    }

    LKNG_LOGGER_DEBUG("(Audio/ALSA) Trying to register ALSA simple element\n");
    if ((res = snd_mixer_selem_register(handle, NULL, NULL)) < 0) {
      LKNG_LOGGER_FATAL(
          "(Audio/ALSA) Failed to register ALSA simple element: %s\n",
          snd_strerror(res));

      lkng_audio_backend_free();
      return LKNG_AUDIO_ERROR;
    }

    LKNG_LOGGER_DEBUG("(Audio/ALSA) Trying to load ALSA mixer\n");
    if ((res = snd_mixer_load(handle)) < 0) {
      LKNG_LOGGER_FATAL("(Audio/ALSA) Failed to load ALSA mixer: %s\n",
                        snd_strerror(res));

      lkng_audio_backend_free();
      return LKNG_AUDIO_ERROR;
    }

    snd_mixer_selem_id_alloca(&sid);
    if (!sid) {
      LKNG_LOGGER_FATAL("(Audio/ALSA) Failed to allocate memory for ALSA "
                        "simple element ID\n");

      lkng_audio_backend_free();
      return LKNG_AUDIO_ERROR;
    }

    LKNG_LOGGER_DEBUG("(Audio/ALSA) Setting up ALSA simple element ID\n");
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, element);

    _mixers[i].mixer_handle = handle;
    _mixers[i].element_id = snd_mixer_find_selem(handle, sid);
  }

  return LKNG_AUDIO_SUCCESS;
}

lkng_audio_result_t lkng_audio_backend_mute(void) {
  LKNG_LOGGER_DEBUG("(Audio/ALSA) Muting all mixers...\n");
  for (int i = 0; i < _mixer_count; i++) {
    snd_mixer_elem_t *element = _mixers[i].element_id;

    if (snd_mixer_selem_has_playback_switch(element))
      snd_mixer_selem_set_playback_switch_all(element, 0);
    else
      LKNG_LOGGER_WARN(
          "(Audio/ALSA) Mixer doesn't have playback switch, skipping...\n");
  }

  return LKNG_AUDIO_SUCCESS;
}

lkng_audio_result_t lkng_audio_backend_unmute(void) {

  LKNG_LOGGER_DEBUG("(Audio/ALSA) Unmuting all mixers...\n");
  for (int i = 0; i < _mixer_count; i++) {
    snd_mixer_elem_t *element = _mixers[i].element_id;

    if (snd_mixer_selem_has_playback_switch(element))
      snd_mixer_selem_set_playback_switch_all(element, 1);
    else
      LKNG_LOGGER_WARN(
          "(Audio/ALSA) Mixer doesn't have playback switch, skipping...\n");
  }

  return LKNG_AUDIO_SUCCESS;
}

void lkng_audio_backend_free(void) {
  // close all mixer devices
  for (int i = 0; i < _mixer_count; i++) {
    LKNG_LOGGER_DEBUG("(Audio/ALSA) Closing all mixer devices\n");
    snd_mixer_close(_mixers[i].mixer_handle);

    _mixers[i].mixer_handle = NULL;
  }

  LKNG_LOGGER_DEBUG("(Audio/ALSA) Cleaning up resources...\n");
  if (_mixers) {
    free(_mixers);
  } else {
    LKNG_LOGGER_DEBUG("(Audio/ALSA) Nothing to clean up.\n");
  }
}
