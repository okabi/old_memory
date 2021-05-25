#include "bgm.h"

int BGM_NUM;
int Bgm[MAX_BGM_NUM];
vector<int> Sound;
int now_playing;
int volume;
void MuLoad();
void play_sound(int);
void play_sound_pan(int,int);
void play_bgm(int);
void stop_bgm();
void change_volume_bgm(int);
void change_volume_sound(int);

void MuLoad(){
//最初に一回だけ呼び出される
	BGM_NUM = 0;
	Sound.clear();
	try{
		SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
		for(int i=0;i<MAX_BGM_NUM;i++){
			Bgm[i] = -1;
		}
		for(int i=0;i<MAX_BGM_NUM;i++){
			char path[128];
			wsprintf(path , "data/bgm/%d.mp3",i);
			if(PathFileExists(path)==false){
				break;
			}
			else{
				BGM_NUM++;
			}
		}
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
		char *file;
		for(int i=0;i<SOUND_NUM;i++){
			switch(i){
				case 0:	file = "data/se/ok.wav";
					break;
				case 1:	file = "data/se/carsol.wav";
					break;
				case 2:	file = "data/se/cancel.wav";
					break;
				case 3:	file = "data/se/p_shot.wav";//ボム設置
					break;
				case 4:	file = "data/se/exp.wav";
					break;
				case 5:	file = "data/se/p_death.wav";
					break;
				case 6:	file = "data/se/p_powerup.wav";//アイテム取得
					break;
				case 7:	file = "data/se/count1.wav";
					break;
				case 8:	file = "data/se/count2.wav";
					break;
				case 9:	file = "data/se/alert.wav";
					break;
				case 10:file = "data/se/e_shot3.wav";
					break;
				case 11:file = "data/se/catin.wav";
					break;
				case 12:file = "data/se/p_gage.wav";
					break;
				case 13:file = "data/se/p_laser.wav";
					break;
				case 14:file = "data/se/e_charge.wav";
					break;
				case 15:file = "data/se/extend.wav";
					break;
				case 16:file = "data/se/pause.wav";
					break;
			}
			Sound.push_back(LoadSoundMem(file));
			if(Sound.at(i)==-1)	throw(file);
		}
		change_volume_sound(255.0*SAVE.Sound*0.01);
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

void play_sound(int num){
//num番の効果音を鳴らす
	//StopSoundMem(Sound.at(num));
	PlaySoundMem(Sound.at(num),DX_PLAYTYPE_BACK);
	return;
}

void play_sound_pan(int num,int pan){
//num番の効果音を鳴らす
	SetPanSoundMem(pan,Sound.at(num));
	PlaySoundMem(Sound.at(num),DX_PLAYTYPE_BACK);
	//SetPanSoundMem(0,Sound.at(num));
	return;
}

void play_bgm(int num){
//num番のBGM_NUMを鳴らす
	try{
		if(num<0||num>=BGM_NUM)	num = BGM_NUM-1;
		if(num!=now_playing){
			StopSoundMem(Bgm[now_playing]);
			StopMusic();
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			if(Bgm[num]==-1){
				try{
					char fi[128];
					wsprintf(fi , "data/bgm/%d.mp3" , num);
					Bgm[num] = LoadSoundMem(fi);
					if( Bgm[num] == -1)	throw(fi);
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
			PlaySoundMem(Bgm[num],DX_PLAYTYPE_LOOP);
			change_volume_bgm(255*SAVE.Bgm*0.01);
			now_playing = num;
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:SMu_PlayBgm\nBGM_NUM指定番号が異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	
	return;	
}

void stop_bgm(){
	StopSoundMem(Bgm[now_playing]);
	now_playing = -1;
	return;
}

void change_volume_bgm(int vol){
	for(int i=0;i<BGM_NUM;i++){
		ChangeVolumeSoundMem(vol,Bgm[i]);
	}
	return;
}

void change_volume_sound(int vol){
	for(int i=0;i<Sound.size();i++){
		ChangeVolumeSoundMem(vol,Sound.at(i));
	}
	return;
}