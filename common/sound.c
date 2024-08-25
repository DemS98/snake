#include <stdio.h>
#include <stdbool.h>
#include "SDL3/SDL_audio.h"
#include "SDL3_mixer/SDL_mixer.h"

static Mix_Chunk *eat_sound, *death_sound;
static bool device_error;

void init_sound() {
    SDL_AudioSpec spec = {.format = SDL_AUDIO_S16LE, .channels = 2, .freq = 44100};

    // Opens default audio device
    // If return value != 0, there's a device open error
    device_error = Mix_OpenAudio(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);

    if (device_error) {
        fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    // Loads sfx wavs
    
    eat_sound = Mix_LoadWAV("resources/eat.wav");
    if (eat_sound == NULL) {
        fprintf(stderr, "Cannot load eat sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    death_sound = Mix_LoadWAV("resources/death.wav");
    if (death_sound == NULL) {
        fprintf(stderr, "Cannot load death sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void play_eat_sound() {
    if (!device_error && eat_sound != NULL) {
        Mix_PlayChannel(-1, eat_sound, 0);
    } 
}

void play_death_sound() {
    if (!device_error && death_sound != NULL) {
        Mix_PlayChannel(-1, death_sound, 0);
    } 
}

void destroy_sound() {
    if (!device_error && eat_sound != NULL) {
        Mix_FreeChunk(eat_sound);
    }

    if (!device_error && death_sound != NULL) {
        Mix_FreeChunk(death_sound);
    }

    if (!device_error) {
        Mix_CloseAudio();
    }
}