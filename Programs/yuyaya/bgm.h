#ifndef __BGM_H__
#define __BGM_H__

#include "DxLib.h"
#include <math.h>
#include <vector>
#include <list.h>
#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
#define BGM_NUM 15
#define SOUND_NUM 35

using namespace std;

extern int BGM[BGM_NUM];
extern vector<int> Sound;
extern int now_playing;
extern int volume;

extern void MuLoad();
extern void MuPlaySound(int);
extern void MuPlayBgm(int);
extern void MuStopBgm();
extern void MuPauseBgm();
extern void MuReturnBgm();
extern void MuChangeVolumeBgm(int);
extern void MuChangeVolumeSound(int);

#endif
