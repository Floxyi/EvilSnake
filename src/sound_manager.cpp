/**
 * @file sound_manager.cpp
 * @brief Implementation of the SoundManager class for the Evil Snake game
 *
 * This file manages game sound effects, including loading, playing, and cleanup of sounds.
 */

#include "../include/sound_manager.h"

#include <raylib.h>

#include "../include/game_utils.h"

/**
 * @brief Sound effect identifiers
 */
const int SoundManager::SOUND_EAT = 1;
const int SoundManager::SOUND_EXPLOSION = 2;
const int SoundManager::SOUND_START = 3;
const int SoundManager::SOUND_CAMERA = 4;

/**
 * @brief Constructs the SoundManager and initializes the audio device.
 */
SoundManager::SoundManager() { InitAudioDevice(); }

/**
 * @brief Destroys the SoundManager, unloading all sounds and closing the audio device.
 */
SoundManager::~SoundManager()
{
    for (auto &soundPair : sounds) {
        UnloadSound(soundPair.second);
    }
    CloseAudioDevice();
}

/**
 * @brief Gets the singleton instance of the SoundManager.
 *
 * @return Reference to the SoundManager instance.
 */
SoundManager &SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

/**
 * @brief Loads sound effects into memory.
 *
 * Retrieves asset paths and loads sound files for in-game events.
 */
void SoundManager::initSounds()
{
    sounds[SOUND_EAT] = LoadSound(TextFormat("%ssounds/eat.wav", GameUtils::getAssetPath().c_str()));
    sounds[SOUND_EXPLOSION] = LoadSound(TextFormat("%ssounds/explosion.wav", GameUtils::getAssetPath().c_str()));
    sounds[SOUND_START] = LoadSound(TextFormat("%ssounds/start.wav", GameUtils::getAssetPath().c_str()));
    sounds[SOUND_CAMERA] = LoadSound(TextFormat("%ssounds/camera.mp3", GameUtils::getAssetPath().c_str()));
}

/**
 * @brief Plays a specified sound effect.
 *
 * @param soundId The ID of the sound to play.
 */
void SoundManager::play(int soundId)
{
    auto soundMap = sounds.find(soundId);
    if (soundMap != sounds.end()) {
        PlaySound(soundMap->second);
    }
}
