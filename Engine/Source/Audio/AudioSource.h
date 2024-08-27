#pragma once
#include "AudioClip.h"
#include <fmod.hpp>

class AudioSource
{
public:
	AudioSource() = default;
	AudioSource(res_t<AudioClip> audioClip) : _audioClip{ audioClip } { }
	~AudioSource() = default;
	bool Play(class Audio& audio, bool loop = false, float volume = 1, float pitch = 1);
	void Stop();
	void Pause(bool pause = true);
	void SetAudioClip(res_t<AudioClip> audioClip) { _audioClip = audioClip; }
	bool IsPlaying();
	bool SetVolume(float volume);
	bool SetPitch(float pitch);

private:
	res_t<AudioClip> _audioClip;
	FMOD::Channel* _channel{ nullptr };
};