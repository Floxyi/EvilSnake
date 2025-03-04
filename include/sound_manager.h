#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <unordered_map>

#include "raylib.h"

class SoundManager
{
   public:
    static SoundManager &getInstance();

    void initSounds();
    void play(int soundId);

    static const int SOUND_EAT;
    static const int SOUND_EXPLOSION;
    static const int SOUND_START;
    static const int SOUND_CAMERA;

   private:
    SoundManager();
    ~SoundManager();

    SoundManager(const SoundManager &) = delete;
    SoundManager &operator=(const SoundManager &) = delete;

    std::unordered_map<int, Sound> sounds;
};

#endif
