#pragma once
#include <tchar.h>


///
extern void AUDIO_PlayAudio(const char* _audioFileName, float lastingSeconds); //FX¿ë
extern void AUDIO_PlayAudioLoop(const char* audioFileName); //BGM¿ë
extern void AUDIO_StopAllAudio();


//1-100
void AUDIO_SetBgmVolume(int vol);
void AUDIO_SetEffectVolume(int vol);
int AUDIO_GetBgmVolume();
int AUDIO_GetEffectVolume();




