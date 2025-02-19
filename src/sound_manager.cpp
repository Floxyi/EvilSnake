#include "../include/sound_manager.h"

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
    sounds[SOUND_EAT] = LoadSound("assets/sounds/eat.wav");
    sounds[SOUND_EXPLOSION] = LoadSound("assets/sounds/explosion.wav");
    sounds[SOUND_START] = LoadSound("assets/sounds/start.wav");
}

void SoundManager::play(int soundId)
{
    auto soundMap = sounds.find(soundId);
    if (soundMap != sounds.end()) {
        PlaySound(soundMap->second);
    }
}
