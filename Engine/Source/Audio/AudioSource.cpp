#include "AudioSource.h"
#include "AudioClip.h"
#include "Audio.h"
#include "Engine.h"
#include <iostream>
#include <fmod.hpp>
#include <fmod_errors.h>

bool AudioSource::Play(Audio& audio, bool loop, float volume, float pitch)
{
    _audioClip->_sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
    FMOD_RESULT result = audio._audio->playSound(_audioClip->_sound, 0, false, &_channel);
    if (result != FMOD_OK)
    {
        std::cerr << "Error playing sound: " << FMOD_ErrorString(result);
        return false;
    }
    SetVolume(volume);
    SetPitch(pitch);
    return true;
}

void AudioSource::Stop()
{
    if (IsPlaying()) _channel->stop();
}

void AudioSource::Pause(bool pause)
{
    FMOD_RESULT result = _channel->setPaused(pause);
        if (result != FMOD_OK)
        {
            std::cerr << "Error pausing sound: " << FMOD_ErrorString(result);
        }
}

bool AudioSource::IsPlaying()
{
    bool isPlaying;
    FMOD_RESULT result = _channel->isPlaying(&isPlaying);
        if (result != FMOD_OK)
        {
            std::cerr << "Error is playing sound: " << FMOD_ErrorString(result);
        }
    return isPlaying;
}

bool AudioSource::SetVolume(float volume)
{
    FMOD_RESULT result = _channel->setVolume(volume);
        if (result != FMOD_OK)
        {
            std::cerr << "Error setting volume: " << FMOD_ErrorString(result);
            return false;
        }
    return true;
}

bool AudioSource::SetPitch(float pitch)
{
    FMOD_RESULT result = _channel->setPitch(pitch);
        if (result != FMOD_OK)
        {
            std::cerr << "Error setting pitch: " << FMOD_ErrorString(result);
            return false;
        }
    return true;
}
