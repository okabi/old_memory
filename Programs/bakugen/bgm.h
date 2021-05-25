#ifndef _BGM_H_
#define _BGM_H_

#include "DxLib.h"
#include <math.h>
#include <vector>
#include <list.h>
#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
#include "extern.h"

#define MAX_BGM_NUM 100
#define SOUND_NUM 17

extern int BGM_NUM;
extern int Bgm[MAX_BGM_NUM];
extern vector<int> Sound;
extern int now_playing;
extern int volume;
extern void MuLoad();
extern void play_sound(int);
extern void play_sound_pan(int,int);
extern void play_bgm(int);
extern void stop_bgm();
extern void change_volume_bgm(int);
extern void change_volume_sound(int);

#endif