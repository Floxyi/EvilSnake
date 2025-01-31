#include "../include/SoundManager.h"

SoundManager::SoundManager() { InitAudioDevice(); }

SoundManager::~SoundManager() {
  for (auto &soundPair : sounds) {
    UnloadSound(soundPair.second);
  }
  CloseAudioDevice();
}

void SoundManager::load(const std::string &name, const std::string &filePath) {
  if (sounds.find(name) == sounds.end()) {
    Sound newSound = LoadSound(filePath.c_str());
    sounds[name] = newSound;
  }
}

void SoundManager::play(const std::string &name) {
  if (sounds.find(name) != sounds.end()) {
    PlaySound(sounds[name]);
  }
}
