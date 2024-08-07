#include "SoundManager.h"
#include "fmod.hpp"

SoundManager::SoundManager() 
{
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	system->createSound(NAME_BGM_MENU, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_MENU]);
	system->createSound(NAME_BGM_SETTING, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_SETTING]);
	system->createSound(NAME_BGM_HOWTO, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_HOWTO]);
	system->createSound(NAME_BGM_GAME, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_GAME]);
	system->createSound(NAME_BGM_4, FMOD_LOOP_NORMAL, 0, &sound[SOUND_BGM_4]);

	system->createSound(NAME_EFFECT_BUTTON, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_BUTTON]);
	system->createSound(NAME_EFFECT_GAMEOVER, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_GAMEOVER]);
	system->createSound(NAME_EFFECT_JUMP, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_JUMP]);
	system->createSound(NAME_EFFECT_DASH, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_DASH]);
	system->createSound(NAME_EFFECT_BREAK, FMOD_LOOP_OFF, 0, &sound[SOUND_EFFECT_BREAK]);
}

SoundManager::~SoundManager()
{
	system->release();
	//delete system;
	//delete[] sound;
	//delete bgmChannel;
	//delete effectChannel;
	//delete extradriverdata;
}

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::stopAll()
{
	bgmChannel->stop();
	for (int i = 0; i < 31; i++) {
		effectChannel[i]->stop();
	}
}

void SoundManager::stopAllBGM()
{
	bgmChannel->stop();
}

void SoundManager::play(int soundNum) {
	if (SOUND_BGM_MENU <= soundNum && soundNum <= SOUND_BGM_4) {
		bool isPlaying;
		bgmChannel->isPlaying(&isPlaying);
		if (isPlaying) {
			bgmChannel->stop();
		}
		system->playSound(sound[soundNum], 0, false, &bgmChannel);
	}

	if (SOUND_EFFECT_BUTTON <= soundNum && soundNum <= SOUND_EFFECT_BREAK) {
		for (int i = 0; i < 31; i++) {
			bool isPlaying = true;
			effectChannel[i]->isPlaying(&isPlaying);
			if (!isPlaying) {
				system->playSound(sound[soundNum], 0, false, &effectChannel[i]);
				break;
			}
		}
	}
}