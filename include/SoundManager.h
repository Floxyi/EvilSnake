#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "raylib.h"
#include <unordered_map>

class SoundManager {
public:
  static SoundManager &getInstance();

  void initSounds();
  void play(int soundId);

  static const int SOUND_EAT;
  static const int SOUND_EXPLOSION;
  static const int SOUND_START;

private:
  SoundManager();
  ~SoundManager();

  SoundManager(const SoundManager &) = delete;
  SoundManager &operator=(const SoundManager &) = delete;

  std::unordered_map<int, Sound> sounds;
};

#endif
