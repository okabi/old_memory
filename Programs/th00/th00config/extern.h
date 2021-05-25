#ifndef __EXTERN_H__
#define __EXTERN_H__

#include "DxLib.h"
#define C_KEY_NUM 256

struct CONFIGDATA{
	char	fps,
		drawmode,
		bgmmode;
};

CONFIGDATA Config;
int c_key[256];

void CheckPushKey();

inline void CheckPushKey(){
//何フレームの間ボタンが押されているか。0は押されていない。
	char check[C_KEY_NUM];
	GetHitKeyStateAll(check);
	for(int i=0;i<C_KEY_NUM;i++){
		if(check[i]==1)	c_key[i]++;
		else		c_key[i] = 0; 
	}
	
	return;
}

#endif