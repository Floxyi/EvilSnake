#include "../include/sound_manager.h"

#include <raylib.h>

#include "../include/game_utils.h"

const int SoundManager::SOUND_EAT = 1;
const int SoundManager::SOUND_EXPLOSION = 2;
const int SoundManager::SOUND_START = 3;

SoundManager::SoundManager() { InitAudioDevice(); }

SoundManager::~SoundManager()
{
    for (auto &soundPair : sounds) {
        UnloadSound(soundPair.second);
    }
    CloseAudioDevice();
}

SoundManager &SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::initSounds()
{
    sounds[SOUND_EAT] = LoadSound(TextFormat("%ssounds/eat.wav", GameUtils::getAssetPath().c_str()));
    sounds[SOUND_EXPLOSION] = LoadSound(TextFormat("%ssounds/explosion.wav", GameUtils::getAssetPath().c_str()));
    sounds[SOUND_START] = LoadSound(TextFormat("%ssounds/start.wav", GameUtils::getAssetPath().c_str()));
}

void SoundManager::play(int soundId)
{
    auto soundMap = sounds.find(soundId);
    if (soundMap != sounds.end()) {
        PlaySound(soundMap->second);
    }
}
