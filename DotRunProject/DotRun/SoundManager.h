#pragma once

#include "fmod.hpp"
#define SOUND_BGM_MENU 0
#define SOUND_BGM_SETTING 1
#define SOUND_BGM_HOWTO 2
#define SOUND_BGM_GAME 3
#define SOUND_BGM_4 4
#define NAME_BGM_MENU "sound/Wii_Shop_Channel_Music_8-BIT.mp3"
#define NAME_BGM_SETTING "sound/Wii_Shop_Channel_Music_8-BIT.mp3"
#define NAME_BGM_HOWTO "sound/Ghost_Fight_8_Bit_Remix_-_Undertale.mp3"
#define NAME_BGM_GAME "sound/Crash_Gourmet_Race_8-Bit_Remix_-_Kirby_Super_Star.mp3"
#define NAME_BGM_4 "sound/singing.wav"

#define SOUND_EFFECT_BUTTON 10
#define SOUND_EFFECT_GAMEOVER 11
#define SOUND_EFFECT_JUMP 12
#define SOUND_EFFECT_DASH 13
#define SOUND_EFFECT_BREAK 14
#define NAME_EFFECT_BUTTON "sound/608432__plasterbrain-ui-select-enter.flac"
#define NAME_EFFECT_GAMEOVER "sound/Kirbys_Dream_Land_2A03_8-Bit_OST_-_Game_Over.mp3"
#define NAME_EFFECT_JUMP "sound/518130__se2001__8-bit-jump-2.wav"
#define NAME_EFFECT_DASH "sound/521999__kastenfrosch__whoosh-dash.wav"
#define NAME_EFFECT_BREAK "sound/391961__ssierra1202__wood-destruction.wav"

class SoundManager
{
private:
    SoundManager();
    SoundManager(const SoundManager& ref) {}
    SoundManager& operator = (const SoundManager& ref) {}
    ~SoundManager();

    FMOD::System* system;
    FMOD::Sound* sound[32];
    FMOD::Channel* bgmChannel;
    FMOD::Channel* effectChannel[31];
    void* extradriverdata;

public:
    static SoundManager& getInstance();

    void stopAll();
    void stopAllBGM();
    void play(int soundNum);
};