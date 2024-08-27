#include "AudioSource.h"
#include "AudioClip.h"
#include "Audio.h"

#include <iostream>

AudioClip::~AudioClip()
{
    if (!_sound) delete(_sound);
}

bool AudioClip::Create(std::string name, ...)
{
    va_list args;
    va_start(args, name);
    Audio& audio = va_arg(args, Audio);
    va_end(args);
    return Load(name, audio);
}

bool AudioClip::Load(const std::string& filename, Audio& audio)
{
    audio._audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &_sound);
    if (!_sound)
    {
        std::cerr << "Could not load sound: " << filename << std::endl;
        return false;
    }
    return true;
}
