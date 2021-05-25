#include "bgm.h"
#include "extern.h"

int BGM[BGM_NUM];
vector<int> Sound;
int now_playing;
int volume;

void MuLoad();
void MuPlaySound(int);
void MuPlayBgm(int);
void MuStopBgm();
void MuPauseBgm();
void MuReturnBgm();
void MuChangeVolumeBgm(int);
void MuChangeVolumeSound(int);

void MuLoad(){
//最初に一回だけ呼び出される
	Sound.clear();
	try{
		SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
		for(int i=0;i<BGM_NUM;i++){
			BGM[i] = -1;
		}
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
		char file[128];
		for(int i=0;i<SOUND_NUM;i++){
			switch(i){
				case 0:	sprintf(file, "data/se/carsol.wav");	break;
				case 1:	sprintf(file, "data/se/ok.wav");	break;
				case 2:	sprintf(file, "data/se/cancel.wav");	break;
				case 3:	sprintf(file, "data/se/p_death.wav");	break;
				case 4:	sprintf(file, "data/se/p_shot.wav");	break;
				case 5:	sprintf(file, "data/se/pause.wav");	break;
				case 6:	sprintf(file, "data/se/e_damage1.wav");	break;
				case 7:	sprintf(file, "data/se/e_damage2.wav");	break;
				case 8:	sprintf(file, "data/se/e_death1.wav");	break;
				case 9:	sprintf(file, "data/se/p_gage.wav");	break;
				case 10:sprintf(file, "data/se/p_laser.wav");	break;
				case 11:sprintf(file, "data/se/slash.wav");	break;
				case 12:sprintf(file, "data/se/dokuro.wav");	break;
				case 13:sprintf(file, "data/se/e_option.wav");	break;
				case 14:sprintf(file, "data/se/p_item.wav");	break;
				case 15:sprintf(file, "data/se/e_laser.wav");	break;
				case 16:sprintf(file, "data/se/count1.wav");	break;
				case 17:sprintf(file, "data/se/count2.wav");	break;
				case 18:sprintf(file, "data/se/e_shot1.wav");	break;
				case 19:sprintf(file, "data/se/e_death2.wav");	break;
				case 20:sprintf(file, "data/se/e_charge.wav");	break;
				case 21:sprintf(file, "data/se/e_shot2.wav");	break;
				case 22:sprintf(file, "data/se/e_shot3.wav");	break;
				case 23:sprintf(file, "data/se/e_kira.wav");	break;
				case 24:sprintf(file, "data/se/catin.wav");	break;
				case 25:sprintf(file, "data/se/e_laser2.wav");	break;
				case 26:sprintf(file, "data/se/cardget.wav");	break;
				case 27:sprintf(file, "data/se/ufo.wav");	break;
				case 28:sprintf(file, "data/se/invalid.wav");	break;
				case 29:sprintf(file, "data/se/e_damage3.wav");	break;
				case 30:sprintf(file, "data/se/extend.wav");	break;
				case 31:sprintf(file, "data/se/e_laser3.wav");	break;
				case 32:sprintf(file, "data/se/alert.wav");	break;
				case 33:sprintf(file, "data/se/explosion.wav");	break;
				case 34:sprintf(file, "data/se/graze.wav");	break;
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

void MuPlaySound(int num){
//num番の効果音を鳴らす
	StopSoundMem(Sound.at(num));
	PlaySoundMem(Sound.at(num),DX_PLAYTYPE_BACK);
	return;
}

void MuPlayBgm(int num){
//num番のBGMを鳴らす
	try{
		if(num<0||num>=BGM_NUM)	throw(1);
		if(num!=now_playing){
			if(now_playing>=0)	StopSoundMem(BGM[now_playing]);
			StopMusic();
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			if(BGM[num]==-1){
				try{
					char fi[128];
					wsprintf(fi , "bgm/%d.mp3" , num);
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
			volume = SAVE.Bgm;
			PlaySoundMem(BGM[num],DX_PLAYTYPE_LOOP);
			MuChangeVolumeBgm(255*volume*0.01);
			now_playing = num;
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR%d:MuPlayBgm\nBGM指定番号が異常",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	
	return;	
}

void MuStopBgm(){
	StopSoundMem(BGM[now_playing]);
	now_playing = -1;
	return;
}

void MuPauseBgm(){
	StopSoundMem(BGM[now_playing]);
	return;
}

void MuReturnBgm(){
	PlaySoundMem(BGM[now_playing],DX_PLAYTYPE_LOOP,FALSE);
	return;
}

void MuChangeVolumeBgm(int vol){
	for(int i=0;i<BGM_NUM;i++){
		ChangeVolumeSoundMem(vol,BGM[i]);
	}
	return;
}

void MuChangeVolumeSound(int vol){
	for(int i=0;i<Sound.size();i++){
		if(i==0 || i==1 || i==2 || i==4 || i==8)	ChangeVolumeSoundMem(vol*0.2,Sound.at(i));	
		else if(i==6 || i==7)	ChangeVolumeSoundMem(vol*0.4,Sound.at(i));	
		else if(i==22 || i==24 || i==25 || i==29 || i==30 || i==32)	ChangeVolumeSoundMem(vol*1.0,Sound.at(i));	
		else				ChangeVolumeSoundMem(vol*0.6,Sound.at(i));
	}
	return;
}
