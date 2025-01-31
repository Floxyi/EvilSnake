#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "raylib.h"
#include <string>
#include <unordered_map>

class SoundManager {
public:
  SoundManager();
  ~SoundManager();

  void load(const std::string &name, const std::string &filePath);
  void play(const std::string &name);

private:
  std::unordered_map<std::string, Sound> sounds;
};

#endif
