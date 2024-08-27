#include "AudioComponent.h"
#include "Audio/AudioSource.h"
#include "Audio/AudioClip.h"
#include "Audio/Audio.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Resource/ResourceManager.h"
#include "Engine.h"

FACTORY_REGISTER(AudioComponent)

AudioComponent::AudioComponent(const AudioComponent& other)
{
    soundName = other.soundName;
    playOnStart = other.playOnStart;
    loop = other.loop;
    volume = other.volume;
    pitch = other.pitch;

    if (other._audioSource)
    {
        _audioSource = std::make_unique<AudioSource>(*other._audioSource.get());
    }
}

void AudioComponent::Initialize()
{
    if (!_audioSource && !soundName.empty())
    {
        auto audioClip = ResourceManager::Instance().Get<AudioClip>(soundName, owner->scene->engine->GetAudio());
        _audioSource = std::make_unique<AudioSource>(audioClip);
    }
}

void AudioComponent::Update(float dt)
{
    if (playOnStart)
    {
        playOnStart = false;
        Play();
    }
}

void AudioComponent::Play()
{
    if (_audioSource) _audioSource->Play(owner->scene->engine->GetAudio(), loop, volume, pitch);
}

void AudioComponent::Play(bool loop, float volume, float pitch)
{
    if (_audioSource) _audioSource->Play(owner->scene->engine->GetAudio(), loop, volume, pitch);
}

bool AudioComponent::IsPlaying()
{
    return (_audioSource->IsPlaying());
}

void AudioComponent::Stop()
{
    if (_audioSource) _audioSource->Stop();
}

void AudioComponent::Pause(bool pause)
{
    if (_audioSource) _audioSource->Pause(pause);
}

void AudioComponent::SetVolume(float volume)
{
    
    if (IsPlaying()) this->volume = volume;
}

void AudioComponent::SetPitch(float pitch)
{
    if (IsPlaying()) this->pitch = pitch;
}

void AudioComponent::Read(const json_t& value)
{
    READ_DATA(value, playOnStart);
    READ_DATA(value, loop);
    READ_DATA(value, volume);
    READ_DATA(value, pitch);
    READ_DATA(value, soundName);

}

void AudioComponent::Write(json_t& value)
{
}