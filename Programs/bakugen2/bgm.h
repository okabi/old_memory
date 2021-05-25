#ifndef _BGM_H_
#define _BGM_H_

#include "DxLib.h"
#include <math.h>
#include <vector>
#include <list.h>
#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
#include "extern.h"

#define MAX_DIRECTORY_NUM 100
#define MAX_BGM_NUM 100
#define MAX_TITLE_NUM 128
#define SOUND_NUM 25

extern int DIRECTORY_NUM;
extern int BGM_NUM[MAX_DIRECTORY_NUM];
extern int Bgm[MAX_DIRECTORY_NUM][MAX_BGM_NUM];
extern char BgmName[MAX_DIRECTORY_NUM][MAX_BGM_NUM][MAX_TITLE_NUM];
extern char DirectoryName[MAX_DIRECTORY_NUM][MAX_TITLE_NUM];
extern vector<int> Sound;
extern int now_playing_directory;
extern int now_playing;
extern int volume;
extern void MuLoad();
extern void play_sound(int);
extern void play_sound_pan(int,int);
extern void play_bgm(int,int);
extern void stop_bgm();
extern void change_volume_bgm(int);
extern void change_volume_sound(int);

#endif