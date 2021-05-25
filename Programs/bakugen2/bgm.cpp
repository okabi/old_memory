#include "bgm.h"

int DIRECTORY_NUM;
int BGM_NUM[MAX_DIRECTORY_NUM];
int Bgm[MAX_DIRECTORY_NUM][MAX_BGM_NUM];
char BgmName[MAX_DIRECTORY_NUM][MAX_BGM_NUM][MAX_TITLE_NUM];
char DirectoryName[MAX_DIRECTORY_NUM][MAX_TITLE_NUM];
vector<int> Sound;
int now_playing_directory;
int now_playing;
int volume;
void MuLoad();
void play_sound(int);
void play_sound_pan(int,int);
void play_bgm(int,int);
void stop_bgm();
void change_volume_bgm(int);
void change_volume_sound(int);

void MuLoad(){
//最初に一回だけ呼び出される
	Sound.clear();
	try{
		SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
		DIRECTORY_NUM = 0;
		for(int i=0;i<MAX_DIRECTORY_NUM;i++){
			BGM_NUM[i] = 0;
			for(int j=0;j<MAX_BGM_NUM;j++){
				Bgm[i][j] = -1;
				for(int a=0;a<MAX_TITLE_NUM;a++){
					BgmName[i][j][a] = '\0';
				}
			}
		}
		FILE *fp;
		fp = fopen("bgm/log.txt","w");
		HANDLE	hFind;
		WIN32_FIND_DATA	FindData;
		if ( (hFind = FindFirstFile( "bgm/*",&FindData )) != INVALID_HANDLE_VALUE ) {
			while(TRUE){
				if(FindData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY){
					if(FindData.cFileName[0]!='.'){
						wsprintf(DirectoryName[DIRECTORY_NUM], "%s",FindData.cFileName);
						char log[128];
						wsprintf(log,"%sを検索します\n",FindData.cFileName);
						fputs(log,fp);
						HANDLE	hFind2;
						WIN32_FIND_DATA	FindData2;
						char add[128];
						wsprintf(add,"bgm/%s/*.wav",FindData.cFileName);
						if((hFind2=FindFirstFile(add,&FindData2))!=INVALID_HANDLE_VALUE){
							while(TRUE){
								wsprintf(log,"\t%s\n",FindData2.cFileName);
								fputs(log,fp);
								for(int i=0;i<MAX_TITLE_NUM;i++){
									if(FindData2.cFileName[i]!='.')	BgmName[DIRECTORY_NUM][BGM_NUM[DIRECTORY_NUM]][i] = FindData2.cFileName[i];
									else					break;
								}
								BGM_NUM[DIRECTORY_NUM] ++;
								if (FindNextFile(hFind2,&FindData2)==FALSE)	break;
							}	
						}
						FindClose(hFind2);
						wsprintf(add,"bgm/%s/*.mp3",FindData.cFileName);
						if((hFind2=FindFirstFile(add,&FindData2))!=INVALID_HANDLE_VALUE){
							while(TRUE){
								wsprintf(log,"\t%s\n",FindData2.cFileName);
								fputs(log,fp);
								for(int i=0;i<MAX_TITLE_NUM;i++){
									if(FindData2.cFileName[i]!='.')	BgmName[DIRECTORY_NUM][BGM_NUM[DIRECTORY_NUM]][i] = FindData2.cFileName[i];
									else					break;
								}
								BGM_NUM[DIRECTORY_NUM] ++;
								if (FindNextFile(hFind2,&FindData2)==FALSE)	break;
							}	
						}
						FindClose(hFind2);
						DIRECTORY_NUM++;
					}
				}
				if ( FindNextFile( hFind,&FindData ) == FALSE )	break;
			}
		}
		FindClose( hFind );
		fputs("\nファイル検索を終了しました",fp);
		fclose(fp);
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
				case 17:file = "data/se/spellbonus.wav";//連爆成功
					break;
				case 18:file = "data/se/slash.wav";//妖夢スペルカード
					break;
				case 19:file = "data/se/dokuro.wav";
					break;
				case 20:file = "data/se/e_kira.wav";
					break;
				case 21:file = "data/se/nuclear.wav";
					break;
				case 22:file = "data/se/netbegin.wav";
					break;
				case 23:file = "data/se/chat.wav";
					break;
				case 24:file = "data/se/miss.wav";
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
	now_playing_directory = -1;
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

void play_bgm(int directory,int num){
	try{
		if(directory<0||directory>=DIRECTORY_NUM||num<0||num>=BGM_NUM[directory]){
			directory = 0;
			num = 0;
			throw(directory);
		}
		if(directory!=now_playing_directory||num!=now_playing){
			StopSoundMem(Bgm[now_playing_directory][now_playing]);
			StopMusic();
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			if(Bgm[directory][num]==-1){
				try{
					HANDLE	hFind;
					WIN32_FIND_DATA	FindData;
					int now_d = 0;
					if ((hFind = FindFirstFile( "bgm/*",&FindData )) != INVALID_HANDLE_VALUE ) {
						while(TRUE){
							if(FindData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY){
								if(FindData.cFileName[0]!='.'){
									int now_m = 0;
									char log[128];
									HANDLE	hFind2;
									WIN32_FIND_DATA	FindData2;
									char add[128];
									wsprintf(add,"bgm/%s/*.wav",FindData.cFileName);
									if((hFind2=FindFirstFile(add,&FindData2))!=INVALID_HANDLE_VALUE&&(now_d<directory||now_m<=num)){
										while(TRUE){
											if(now_d==directory&&now_m==num){	
												char fi[128];
												wsprintf(fi,"bgm/%s/%s",FindData.cFileName,FindData2.cFileName);
												Bgm[directory][num] = LoadSoundMem(fi);
												if( Bgm[directory][num] == -1)	throw(355);
											}
											now_m ++;
											if (FindNextFile(hFind2,&FindData2)==FALSE)	break;
										}	
									}
									FindClose(hFind2);
									wsprintf(add,"bgm/%s/*.mp3",FindData.cFileName);
									if((hFind2=FindFirstFile(add,&FindData2))!=INVALID_HANDLE_VALUE&&(now_d<directory||now_m<=num)){
										while(TRUE){
											if(now_d==directory&&now_m==num){	
												char fi[128];
												wsprintf(fi,"bgm/%s/%s",FindData.cFileName,FindData2.cFileName);
												Bgm[directory][num] = LoadSoundMem(fi);
												if( Bgm[directory][num] == -1)	throw(FindData2.cFileName);
											}
											now_m ++;
											if (FindNextFile(hFind2,&FindData2)==FALSE)	break;
										}	
									}
									FindClose(hFind2);
									now_d++;
								}
							}
							if ( FindNextFile( hFind,&FindData ) == FALSE )	break;
						}
					}
					FindClose( hFind );
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
			PlaySoundMem(Bgm[directory][num],DX_PLAYTYPE_LOOP);
			change_volume_bgm(255*SAVE.Bgm*0.01);
			now_playing_directory = directory;
			now_playing = num;
		}
	}
	catch(int n){
		char message[128];
		wsprintf(message , "ERROR:SMu_PlayBgm\nBGM_NUM指定番号が異常\n directory:%d",n);
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
	}
	catch(char s[]){
		char message[128];
		wsprintf(message , "ERROR:SMu_PlayBgm\nBGM_NUM指定番号が異常\n %s",s);
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
	StopSoundMem(Bgm[now_playing_directory][now_playing]);
	now_playing = -1;
	return;
}

void change_volume_bgm(int vol){
	for(int i=0;i<DIRECTORY_NUM;i++){
		for(int j=0;j<BGM_NUM[i];j++){
			ChangeVolumeSoundMem(vol,Bgm[i][j]);
		}
	}
	return;
}

void change_volume_sound(int vol){
	for(int i=0;i<Sound.size();i++){
		ChangeVolumeSoundMem(vol,Sound.at(i));
	}
	return;
}