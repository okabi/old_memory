#ifndef __BGM_H__
#define __BGM_H__

#include "DxLib.h"
#include "STG.h"
#include <vector>

#define BGM_NUM 14
#define SOUND_NUM 23

using namespace std;

static int BGM[BGM_NUM];
static vector<int> Sound;
static int now_playing;
static int volume;

static void SMu_Load();
static void SMu_PlaySound(int);
static void SMu_PlayBgm(int);
static void SMu_StopBgm();
static void SMu_ChangeVolumeBgm(int);
static void SMu_ChangeVolumeSound(int);

struct CONFIGDATA{
	char	fps,
		drawmode,
		bgmmode;
};
CONFIGDATA Config;
int ConfigCount;

void SMu_Load(){
//最初に一回だけ呼び出される
	Sound.clear();
	try{
		SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
		for(int i=0;i<BGM_NUM;i++){
			if(Config.bgmmode==1){
				char fi[128];
				wsprintf(fi , "data/bgm/BGM/%d.mp3" , i+1);
				BGM[i] = LoadSoundMem(fi);
				if( BGM[i] == -1)	throw(fi);				
			}
			else{
				BGM[i] = -1;
			}
		}
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
		char *file = "data/bgm/se/enemy/shot.ogg";
		for(int i=0;i<SOUND_NUM;i++){
			switch(i){
				case 1:	file = "data/bgm/se/player/item.ogg";
					break;
				case 2:	file = "data/bgm/se/player/death.ogg";
					break;
				case 3:	file = "data/bgm/se/player/graze.ogg";
					break;
				case 4:	file = "data/bgm/se/player/gage.wav";
					break;
				case 5:	file = "data/bgm/se/player/decision.ogg";
					break;
				case 6:	file = "data/bgm/se/player/cancel.ogg";
					break;
				case 7:	file = "data/bgm/se/player/carsol.ogg";
					break;
				case 8:	file = "data/bgm/se/enemy/normalshot.ogg";
					break;
				case 9:	file = "data/bgm/se/enemy/shot.ogg";
					break;
				case 10:file = "data/bgm/se/enemy/shot2.ogg";
					break;
				case 11:file = "data/bgm/se/enemy/bel.ogg";
					break;
				case 12:file = "data/bgm/se/enemy/death2.ogg";
					break;
				case 13:file = "data/bgm/se/player/bomb.ogg";
					break;
				case 14:file = "data/bgm/se/player/up.ogg";
					break;
				case 15:file = "data/bgm/se/player/pause.ogg";
					break;
				case 16:file = "data/bgm/se/player/count.ogg";
					break;
				case 17:file = "data/bgm/se/player/spell.ogg";
					break;
				case 18:file = "data/bgm/se/enemy/death.ogg";
					break;
				case 19:file = "data/bgm/se/enemy/charge.ogg";
					break;
				case 20:file = "data/bgm/se/player/extend.wav";
					break;
				case 21:file = "data/bgm/se/enemy/laser.ogg";
					break;
				case 22:file = "data/bgm/se/player/shot.ogg";
					break;
			}
			Sound.push_back(LoadSoundMem(file));
			if(Sound.at(i)==-1)	throw(file);
		}
	}
	catch(char *file){
		char message[128];
		wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);

	}
	now_playing = -1;
	return;
}

void SMu_PlaySound(int num){
//num番の効果音を鳴らす
	StopSoundMem(Sound.at(num));
	PlaySoundMem(Sound.at(num),DX_PLAYTYPE_BACK);
	return;
}

void SMu_PlayBgm(int num){
//num番のBGMを鳴らす
	try{
		if(num<0||num>=BGM_NUM)	throw(1);
		if(num!=now_playing){
			StopSoundMem(BGM[now_playing]);
			StopMusic();
			if(Config.bgmmode==2){
				for(int i=0;i<BGM_NUM;i++){
					DeleteSoundMem(BGM[i]);
					BGM[i] = -1;
				}
			}
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			if(BGM[num]==-1){
				try{
					char fi[128];
					wsprintf(fi , "data/bgm/BGM/%d.mp3" , num+1);
					BGM[num] = LoadSoundMem(fi);
					if( BGM[num] == -1)	throw(fi);
				}
				catch(char *file){
					char message[128];
					wsprintf(message , "ファイルが見つかりません\n( %s )" , file);
					MessageBox( 	NULL,
						message,
						"Error",
						MB_OK | 
						MB_ICONSTOP |
						MB_TOPMOST);
				}
			}
			PlaySoundMem(BGM[num],DX_PLAYTYPE_LOOP);
			SMu_ChangeVolumeBgm(255*volume*0.01);
			if(num==9)	SetLoopPosSoundMem(72850,BGM[num]);
			now_playing = num;
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMu_PlayBgm\nBGM指定番号が異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	
	return;	
}

void SMu_StopBgm(){
	StopSoundMem(BGM[now_playing]);
	now_playing = -1;
	return;
}

void SMu_ChangeVolumeBgm(int vol){
	for(int i=0;i<BGM_NUM;i++){
		ChangeVolumeSoundMem(vol,BGM[i]);
	}
	return;
}

void SMu_ChangeVolumeSound(int vol){
	for(int i=0;i<Sound.size();i++){
		if(i==22)	ChangeVolumeSoundMem(vol*0.5,Sound.at(i));
		else		ChangeVolumeSoundMem(vol,Sound.at(i));
	}
	return;
}
#endif
