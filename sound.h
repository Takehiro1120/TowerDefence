#ifndef SOUND_H_
#define SOUND_H_

#include "DxLib.h"
#include "defines.h"
#include <string>
#include <map>


class Sound{
private:
	int musicVolume;
	std::map<std::string,int> soundList;
public:
	Sound(){
		musicVolume = 50;
		loadSounds();
	}
	void loadASound(std::string name){
		int handle;
		std::string filename = "sound/" + name + ".mp3";
		handle = LoadSoundMem(filename.c_str());
		if(handle == -1){
			return;
		}
		soundList[name] =  handle;
	}
	void loadSounds(){
		loadASound("field");
		loadASound("shoot");
	}
	void playBGM(std::string bgmName){
		if(CheckSoundFile() || soundList.count(bgmName)==0){
			StopSoundFile();
		}
		ChangeNextPlayVolumeSoundMem(musicVolume,soundList[bgmName]);
		PlaySoundMem(soundList[bgmName],DX_PLAYTYPE_LOOP);
	}
	void playSE(std::string bgmName){
		if(soundList.count(bgmName) == 0) return;
		ChangeNextPlayVolumeSoundMem(50,soundList[bgmName]);
		PlaySoundMem(soundList[bgmName],DX_PLAYTYPE_BACK);
	}

};

#endif