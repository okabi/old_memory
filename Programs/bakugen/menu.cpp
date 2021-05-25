#include "menu.h"
#include "map.h"
#include "player.h"

list<EFFECTDATA> MeEffect;

int menu_count;
int title_carsol;
int select_re_count;
int select_re_count2;
int option_count;
int option_carsol;
int settingA_count;
int settingA_carsol;
int settingB_count;
int settingB_carsol[4];
bool settingB_flag[4];//設定終わってる？
int settingC_count;
int settingC_count2;
int settingC_carsol[2];

void MeLoad();
void MeMain();
void MeBackDraw();
void MeMenuDraw();
void MeMenuSelect();
void MeSelect_Replay();
void MeOption();
void KeyToChar(int key,char *buffer);
void MeSettingA();
void MeSettingB();
void MeSettingC();
void MeEfMake(float x,float y,int img,int pattern);
void MeEfDraw();
void MeEfMove(list<EFFECTDATA>::iterator &it);

void MeLoad(){
	MeEffect.clear();
	for(int i=0;i<100;i++)	MeEfMake(get_rand(640),get_rand(480),0,0);
	title_carsol = 0;
	menu_count = 0;
	option_count = 0;
	option_carsol = 0;
	settingC_carsol[0] = 0;
	settingC_carsol[1] = 0;

	return;
}

void MeMain(){
	MeBackDraw();
	MeEfDraw();
	MeMenuDraw();
	if(scene==TITLE)	MeMenuSelect();
	if(scene==SELECT_REPLAY)MeSelect_Replay();
	if(scene==OPTION)	MeOption();
	if(scene==SETTINGA)	MeSettingA();
	if(scene==SETTINGB)	MeSettingB();
	if(scene==SETTINGC)	MeSettingC();
	
	menu_count++;
	return;
}

void MeBackDraw(){
	if(menu_count<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*menu_count);
		DrawRotaGraphF(320,240,1.0+0.1*(float)(30-menu_count),0,gMenu[0],TRUE,FALSE);
	}
	else{
		float x=320,y=120;
		float back_y = 240+150*sin(Radian(menu_count/6.0,TRUE));
		if(menu_count<60){
			x = 320;
			y = 120+120*cos(Radian(3*(menu_count-30),TRUE));
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(menu_count-30));
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		}
		DrawRotaGraphF(320,back_y,1.0,0,gMenuBack,TRUE,FALSE);
		char message[128];
		wsprintf(message , "ver1.00a");
		DrawFormatString(0,468,GetColor(255,255,255),message);
		wsprintf(message , "2010 (C)opyright okabi. All rights reserved.");
		int size = GetDrawStringWidth(message,128);
		int size2 = GetDrawStringWidth("60.00 fps",128);
		DrawFormatString(640-size-size2,468,GetColor(255,255,255),message);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawRotaGraphF(x,y,1.0,0,gMenu[0],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ADD,50);
		DrawRotaGraphF(x,y,2.0+sin(Radian(menu_count,TRUE)),0,gMenu[0],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ADD,50);
		DrawRotaGraphF(x,y,2.0,Radian(menu_count/2,TRUE),gMenu[0],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ADD,50);
		DrawRotaGraphF(x,y,2.0,Radian(-menu_count/2,TRUE),gMenu[0],TRUE,FALSE);
	}
	
	return;
}

void MeMenuDraw(){
	for(int i=0;i<4;i++){
		float x = 320+10*sin(Radian(menu_count+60*i,TRUE));
		float y = 300+30*i;
		if(menu_count<90)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,8.5*(menu_count-60));
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(title_carsol!=i)	SetDrawBright(150,150,150);
		DrawRotaGraphF(x,y,1.0,0,gMenu[i+1],TRUE,FALSE);
		SetDrawBright(255,255,255);
	}

	return;
}

void MeMenuSelect(){
	if(menu_count<60)	return;
	int bomb=0,spell=0,up=0,down=0,left=0,right=0;
	int title_num = 4;
	for(int i=0;i<4;i++){
		bomb += c_pad[i][SAVE.Key_Bomb[i]];
		spell += c_pad[i][SAVE.Key_Spell[i]];
		up += c_pad[i][PAD_UP];
		down += c_pad[i][PAD_DOWN];
		left += c_pad[i][PAD_LEFT];
		right += c_pad[i][PAD_RIGHT];
	}
	bomb += c_key[KEY_INPUT_Z];
	spell += c_key[KEY_INPUT_X];
	up += c_key[KEY_INPUT_UP];
	down += c_key[KEY_INPUT_DOWN];
	left += c_key[KEY_INPUT_LEFT];
	right += c_key[KEY_INPUT_RIGHT];
	
	if(down==1||(down>=30&&down%10==0)){
		play_sound(1);
		title_carsol++;
		title_carsol = title_carsol % title_num;
	}
	else if(up==1||(up>=30&&up%10==0)){
		play_sound(1);
		title_carsol--;
		title_carsol = (title_carsol+title_num) % title_num;
	}
	if(bomb==1){
		play_sound(0);
		if(title_carsol==0){
			change_scene(SETTINGA);
		}
		if(title_carsol==1){
			select_re_count = 0;
			select_re_count2 = 0;
			change_scene(SELECT_REPLAY);
		}
		if(title_carsol==2){
			option_count = 0;
			option_carsol = 0;
			change_scene(OPTION);
		}
		if(title_carsol==3){
			change_scene(END);
		}
	}
	else if(spell==1){
		play_sound(2);
		title_carsol = title_num-1;
	}

	return;
}

void MeSelect_Replay(){
	if(select_re_count<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		float x = 11*select_re_count;
		float y = 8*select_re_count;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<REPLAY_NUM;i++){
			char message[128];
			char message2[8];
			if(Replay[i].exist==true){
				if(Replay[i].month==1)	wsprintf(message2 , "Jan");
				if(Replay[i].month==2)	wsprintf(message2 , "Feb");
				if(Replay[i].month==3)	wsprintf(message2 , "Mar");
				if(Replay[i].month==4)	wsprintf(message2 , "Apr");
				if(Replay[i].month==5)	wsprintf(message2 , "May");
				if(Replay[i].month==6)	wsprintf(message2 , "Jun");
				if(Replay[i].month==7)	wsprintf(message2 , "Jul");
				if(Replay[i].month==8)	wsprintf(message2 , "Aug");
				if(Replay[i].month==9)	wsprintf(message2 , "Sep");
				if(Replay[i].month==10)	wsprintf(message2 , "Oct");
				if(Replay[i].month==11)	wsprintf(message2 , "Nov");
				if(Replay[i].month==12)	wsprintf(message2 , "Dec");
				wsprintf(message , "No.%2d %02d/%s/%02d  %2d:%02d:%02d ~ %2d:%02d:%02d  %2dmatches",i+1, Replay[i].year%2000, message2, Replay[i].day, Replay[i].hour[0], Replay[i].minute[0], Replay[i].second[0], Replay[i].hour[1], Replay[i].minute[1], Replay[i].second[1], Replay[i].match);
			}
			else{
				wsprintf(message , "No.%2d --/---/--  --:--:-- ~ --:--:--  --matches",i+1);
			}
			int size = GetDrawStringWidthToHandle(message,128,font_default);
			if(i==replay_play_num)	SetDrawBright(255,255,255);
			else			SetDrawBright(100,100,100);
			DrawSt(320-size/2,60+18*i,GetColor(255,255,255),0,font_default,message);
		}
		SetDrawBright(255,255,255);
		if(select_re_count2==0){
			int bomb=0,spell=0,up=0,down=0,left=0,right=0;
			int select_replay_num = REPLAY_NUM;
			for(int i=0;i<4;i++){
				bomb += c_pad[i][SAVE.Key_Bomb[i]];
				spell += c_pad[i][SAVE.Key_Spell[i]];
				up += c_pad[i][PAD_UP];
				down += c_pad[i][PAD_DOWN];
				left += c_pad[i][PAD_LEFT];
				right += c_pad[i][PAD_RIGHT];
			}
			bomb += c_key[KEY_INPUT_Z];
			spell += c_key[KEY_INPUT_X];
			up += c_key[KEY_INPUT_UP];
			down += c_key[KEY_INPUT_DOWN];
			left += c_key[KEY_INPUT_LEFT];
			right += c_key[KEY_INPUT_RIGHT];
			
			if(down==1||(down>=30&&down%10==0)){
				play_sound(1);
				replay_play_num++;
				replay_play_num = replay_play_num % select_replay_num;
			}
			else if(up==1||(up>=30&&up%10==0)){
				play_sound(1);
				replay_play_num--;
				replay_play_num = (replay_play_num+select_replay_num) % select_replay_num;
			}
			if(bomb==1){
				play_sound(0);
				if(Replay[replay_play_num].exist==true){
					select_re_count2 = 1;
					stop_bgm();
				}
			}
			else if(spell==1){
				play_sound(2);
				change_scene(TITLE);
			}
		}
		char message[64];
		wsprintf(message , "上下キーでリプレイを選択すること");
		int size = GetDrawStringWidthToHandle(message,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);
		SetDrawBright(255,255,255);
	}

	if(select_re_count2>0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*select_re_count2);
		DrawBox(0,0,640,480,0,TRUE);
		if(select_re_count2==50){
			settingC_carsol[0] = Replay[replay_play_num].stage;
			settingC_carsol[1] = Replay[replay_play_num].bgm;
			rand_seed = Replay[replay_play_num].rand_seed;
			for(int i=0;i<4;i++){
				Player[i].chara = Replay[replay_play_num].player[i];
				Player[i].bMan = Replay[replay_play_num].bMan[i];
			}
			SAVE.MatchNum = Replay[replay_play_num].matchnum;
			SAVE.MatchTime = Replay[replay_play_num].matchtime;
			GameLoad();
			replay_play = true;
			change_scene(GAME);
		}
		select_re_count2++;
	}
	select_re_count ++;

	return;
}

void MeOption(){
	if(option_count<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		float x = 11*option_count;
		float y = 8*option_count;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		char message[64];
		char message2[64];
		int time[3];
		time[0] = SAVE.PlayTime/3600;
		time[1] = (SAVE.PlayTime-time[0]*3600)/60;
		time[2] = (SAVE.PlayTime-time[0]*3600-time[1]*60)/1;
		wsprintf(message , "総起動時間　%d:%02d:%02d",time[0],time[1],time[2]);
		DrawSt(350,200,GetColor(255,255,255),0,font_default,message);
		wsprintf(message2 , "プレイ回数　%d回",SAVE.PlayCount);
		DrawSt(350,220,GetColor(255,255,255),0,font_default,message2);
		if(option_carsol==0){
			wsprintf(message , "ＢＧＭ音量を設定します(0～100)");
			wsprintf(message2 , "工場設定: 100");
		}
		else if(option_carsol==1){
			wsprintf(message , "効果音音量を設定します(0～100)");
			wsprintf(message2 , "工場設定: 50");
		}
		else if(option_carsol==22){
			wsprintf(message , "試合数を設定します(1～5)");
			wsprintf(message2 , "工場設定: 3");
		}
		else if(option_carsol==23){
			wsprintf(message , "試合時間を設定します(90秒～300秒)");
			wsprintf(message2 , "工場設定: 150秒");
		}
		else if(option_carsol==24){
			wsprintf(message , "全ての設定を工場設定に戻します");
			wsprintf(message2 , "");
		}
		else if(option_carsol==25){
			wsprintf(message , "タイトルに戻ります");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==1){
			wsprintf(message , "入力装置を設定します");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==2){
			wsprintf(message , "ボム・決定キーを設定します");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==3){
			wsprintf(message , "スペルカード・キャンセルキーを");
			wsprintf(message2 , "設定します");
		}
		else if((option_carsol-2)%5==4){
			wsprintf(message , "ポーズキーを設定します");
			wsprintf(message2 , "");
		}
		DrawSt(350,250,GetColor(150,150,255),0,font_default,message);
		DrawSt(350,265,GetColor(150,150,255),0,font_default,message2);
		for(int i=0;i<26;i++){
			float x = 80;
			float y = 10 + 18*i;
			float x2 = 230;
			float x3 = 130;
			float x4 = 230;
			if(i==option_carsol){
				SetDrawBright(255,255,255);
			}
			else{
				SetDrawBright(150,150,150);
			}
			for(int a=0;a<64;a++){
				message[a] = '\0';
				message2[a] = '\0';
			}
			if(i==0){
				wsprintf(message , "BGM");
				draw_string(x,y,64,message);
				int num[3];
				num[0] = SAVE.Bgm/100;
				num[1] = (SAVE.Bgm-num[0]*100)/10;
				num[2] = (SAVE.Bgm-num[0]*100-num[1]*10)/1;
				wsprintf(message2 , "%d%d%d", num[0],num[1],num[2]);
				draw_string(x2,y,64,message2);
			}
			else if(i==1){
				wsprintf(message , "SOUND");
				draw_string(x,y,64,message);
				int num[3];
				num[0] = SAVE.Sound/100;
				num[1] = (SAVE.Sound-num[0]*100)/10;
				num[2] = (SAVE.Sound-num[0]*100-num[1]*10)/1;
				wsprintf(message2 , "%d%d%d", num[0],num[1],num[2]);
				draw_string(x2,y,64,message2);
			}
			else if(i==22){
				wsprintf(message , "MATCH NUM");
				draw_string(x,y,64,message);
				wsprintf(message2 , "%d", SAVE.MatchNum);
				draw_string(x2,y,64,message2);
			}
			else if(i==23){
				wsprintf(message , "MATCH TIME");
				draw_string(x,y,64,message);
				int time = 90 + SAVE.MatchTime*30;
				wsprintf(message2 , "%d", time);
				draw_string(x2,y,64,message2);
			}
			else if(i==24){
				wsprintf(message , "DEFAULT");
				draw_string(x,y,64,message);
			}
			else if(i==25){
				wsprintf(message , "QUIT");
				draw_string(x,y,64,message);
			}
			else if((i-2)%5==0){
				SetDrawBright(255,50,50);
				wsprintf(message , "KEYCONFIG %dP",(i-2)/5+1);
				draw_string(x,y,64,message);
			}
			else if((i-2)%5==1){
				wsprintf(message , "INPUTTER");
				draw_string(x3,y,64,message);
				if(SAVE.Key_Type[(i-2)/5]==DX_INPUT_PAD1)	wsprintf(message2 , "PAD1");
				if(SAVE.Key_Type[(i-2)/5]==DX_INPUT_PAD2)	wsprintf(message2 , "PAD2");
				if(SAVE.Key_Type[(i-2)/5]==DX_INPUT_PAD3)	wsprintf(message2 , "PAD3");
				if(SAVE.Key_Type[(i-2)/5]==DX_INPUT_PAD4)	wsprintf(message2 , "PAD4");
				if(SAVE.Key_Type[(i-2)/5]==DX_INPUT_KEY)	wsprintf(message2 , "KEYBOARD");
				draw_string(x4,y,64,message2);
			}
			else if((i-2)%5==2){
				wsprintf(message , "BOMB");
				draw_string(x3,y,64,message);
				if(SAVE.Key_Type[(i-2)/5]!=DX_INPUT_KEY){
					KeyToChar(SAVE.Key_Bomb[(i-2)/5],message2);
				}
				draw_string(x4,y,64,message2);
			}
			else if((i-2)%5==3){
				wsprintf(message , "SPELL");
				draw_string(x3,y,64,message);
				if(SAVE.Key_Type[(i-2)/5]!=DX_INPUT_KEY){
					KeyToChar(SAVE.Key_Spell[(i-2)/5],message2);
				}
				draw_string(x4,y,64,message2);
			}
			else if((i-2)%5==4){
				wsprintf(message , "PAUSE");
				draw_string(x3,y,64,message);
				if(SAVE.Key_Type[(i-2)/5]!=DX_INPUT_KEY){
					KeyToChar(SAVE.Key_Pause[(i-2)/5],message2);
				}
				draw_string(x4,y,64,message2);
			}
		}
		
		int bomb=0,spell=0,up=0,down=0,left=0,right=0;
		int option_num = 26;
		for(int i=0;i<4;i++){
			bomb += c_pad[i][SAVE.Key_Bomb[i]];
			spell += c_pad[i][SAVE.Key_Spell[i]];
			up += c_pad[i][PAD_UP];
			down += c_pad[i][PAD_DOWN];
			left += c_pad[i][PAD_LEFT];
			right += c_pad[i][PAD_RIGHT];
		}
		bomb += c_key[KEY_INPUT_Z];
		spell += c_key[KEY_INPUT_X];
		up += c_key[KEY_INPUT_UP];
		down += c_key[KEY_INPUT_DOWN];
		left += c_key[KEY_INPUT_LEFT];
		right += c_key[KEY_INPUT_RIGHT];
		
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			option_carsol++;
			option_carsol = option_carsol % option_num;
			if(option_carsol<22&&(option_carsol-2)%5==0)	option_carsol++;
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			option_carsol--;
			option_carsol = (option_carsol+option_num) % option_num;
			if(option_carsol<22&&(option_carsol-2)%5==0)	option_carsol--;
		}
		if(left==1||(left>=30&&left%10==0)){
			play_sound(1);
			if(option_carsol==0){
				if(SAVE.Bgm>0)	SAVE.Bgm -= 5;
				change_volume_bgm(255.0*SAVE.Bgm*0.01);		
			}
			else if(option_carsol==1){
				if(SAVE.Sound>0)	SAVE.Sound -= 5;
				change_volume_sound(255.0*SAVE.Sound*0.01);		
			}
			else if(option_carsol==22){
				if(SAVE.MatchNum>1)	SAVE.MatchNum --;
			}
			else if(option_carsol==23){
				if(SAVE.MatchTime>0)	SAVE.MatchTime --;
			}
			else if(option_carsol>=24){}
			else if((option_carsol-2)%5==1){
				if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD1)		SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_KEY;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD2)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD1;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD3)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD2;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD4)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD3;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_KEY)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD4;
			}
		}
		else if(right==1||(right>=30&&right%10==0)){
			play_sound(1);
			if(option_carsol==0){
				if(SAVE.Bgm<100)	SAVE.Bgm += 5;
				change_volume_bgm(255.0*SAVE.Bgm*0.01);		
			}
			else if(option_carsol==1){
				if(SAVE.Sound<100)	SAVE.Sound += 5;
				change_volume_sound(255.0*SAVE.Sound*0.01);		
			}
			else if(option_carsol==22){
				if(SAVE.MatchNum<5)	SAVE.MatchNum ++;
			}
			else if(option_carsol==23){
				if(SAVE.MatchTime<7)	SAVE.MatchTime ++;
			}
			else if(option_carsol>=24){}
			else if((option_carsol-2)%5==1){
				if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD1)		SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD2;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD2)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD3;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD3)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD4;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD4)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_KEY;
				else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_KEY)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD1;
			}
		}
		if(bomb==1){
			play_sound(0);
			if(option_carsol==24){
				for(int i=0;i<4;i++){
					SAVE.Key_Bomb[i] = PAD_A;
					SAVE.Key_Spell[i] = PAD_B;
					SAVE.Key_Pause[i] = PAD_START;
				}
				SAVE.Key_Type[0] = DX_INPUT_PAD1;
				SAVE.Key_Type[1] = DX_INPUT_PAD2;
				SAVE.Key_Type[2] = DX_INPUT_PAD3;
				SAVE.Key_Type[3] = DX_INPUT_PAD4;
				SAVE.Bgm = 100;
				SAVE.Sound = 50;
				SAVE.MatchNum = 3;
				SAVE.MatchTime = 2;
				change_volume_bgm(255.0*SAVE.Bgm*0.01);		
				change_volume_sound(255.0*SAVE.Sound*0.01);		
			}
			else if(option_carsol==25){
				play_sound(16);
				change_scene(TITLE);
			}
		}
		if(option_carsol>2&&option_carsol<22&&(option_carsol-2)%5>=2){
			int check_num = 0;
			if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD4)	check_num = 3;
			for(int i=0;i<10;i++){
				if(c_pad[check_num][i+4]==1){
					play_sound(0);
					if((option_carsol-2)%5==2)	SAVE.Key_Bomb[(option_carsol-2)/5] = i+4;
					if((option_carsol-2)%5==3)	SAVE.Key_Spell[(option_carsol-2)/5] = i+4;
					if((option_carsol-2)%5==4)	SAVE.Key_Pause[(option_carsol-2)/5] = i+4;
					break;
				}
			}
		}
		if(option_carsol==1&&option_count%60==0){
			play_sound(5);
		}
	}
	SetDrawBright(255,255,255);
	option_count ++;

	return;
}

void KeyToChar(int key,char *buffer){
	for(int i=0;i<10;i++){
		if(key==i+4){
			wsprintf(buffer , "%d",i+1);
		}
	}
	return;	
}

void MeSettingA(){
	if(settingA_count<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
		float x = 11*settingA_count;
		float y = 8*settingA_count;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
		DrawBox(0,0,640,480,0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<PLAYER_NUM;i++){
			char message[64];
			char message2[64];
			char message3[64];
			char message4[64];
			for(int a=0;a<64;a++){
				message[a] = '\0';
				message2[a] = '\0';
				message3[a] = '\0';
				message4[a] = '\0';
			}
			float x = 150;
			float y = 100 + 50*i;
			float x2 = 250;
			float x3 = 300;
			if(settingA_carsol==i)	SetDrawBright(255,200,200);
			else			SetDrawBright(155,100,100);
			wsprintf(message , "Player%d",i+1);
			draw_string(x,y,64,message);
			if(settingA_carsol==i){
				if(Player[i].bMan==true)	SetDrawBright(255,255,255);
				else				SetDrawBright(150,150,150);
			}
			else{
				if(Player[i].bMan==true)	SetDrawBright(180,180,180);
				else				SetDrawBright(100,100,100);
			}
			wsprintf(message2 , "MAN");
			draw_string(x2,y,64,message2);
			if(settingA_carsol==i){
				if(Player[i].bMan==false)	SetDrawBright(255,255,255);
				else				SetDrawBright(150,150,150);
			}
			else{
				if(Player[i].bMan==false)	SetDrawBright(180,180,180);
				else				SetDrawBright(100,100,100);
			}
			wsprintf(message3 , "COM");
			draw_string(x3,y,64,message3);
			if(settingA_carsol==i){
				if(Player[i].bMan==false)	SetDrawBright(255,0,0);
				else				SetDrawBright(150,0,0);
			}
			else{
				if(Player[i].bMan==false)	SetDrawBright(180,0,0);
				else				SetDrawBright(100,0,0);
			}
			if(Player[i].level==0)	wsprintf(message4 , "EASY");
			if(Player[i].level==1)	wsprintf(message4 , "NORMAL");
			if(Player[i].level==2)	wsprintf(message4 , "HARD");
			if(Player[i].level==3)	wsprintf(message4 , "LUNATIC");
			draw_string(x3+40,y,64,message4);
		}
		char message[64];
		wsprintf(message , "レベル変更はＣＯＭ上で左右キー。次へ進むには決定キーを押す");
		int size = GetDrawStringWidthToHandle(message,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);

		if(settingA_count!=30){	
			int bomb=0,spell=0,up=0,down=0,left=0,right=0;
			int settingA_num = 4;
			for(int i=0;i<4;i++){
				bomb += c_pad[i][SAVE.Key_Bomb[i]];
				spell += c_pad[i][SAVE.Key_Spell[i]];
				up += c_pad[i][PAD_UP];
				down += c_pad[i][PAD_DOWN];
				left += c_pad[i][PAD_LEFT];
				right += c_pad[i][PAD_RIGHT];
			}
			bomb += c_key[KEY_INPUT_Z];
			spell += c_key[KEY_INPUT_X];
			up += c_key[KEY_INPUT_UP];
			down += c_key[KEY_INPUT_DOWN];
			left += c_key[KEY_INPUT_LEFT];
			right += c_key[KEY_INPUT_RIGHT];
			
			if(down==1||(down>=30&&down%10==0)){
				play_sound(1);
				settingA_carsol++;
				settingA_carsol = settingA_carsol % settingA_num;
			}
			else if(up==1||(up>=30&&up%10==0)){
				play_sound(1);
				settingA_carsol--;
				settingA_carsol = (settingA_carsol+settingA_num) % settingA_num;
			}
			if(left==1||(left>=30&&left%10==0)){
				play_sound(1);
				if(Player[settingA_carsol].bMan==false&&Player[settingA_carsol].level>0)	Player[settingA_carsol].level--;
				else	Player[settingA_carsol].bMan = true;
			}
			else if(right==1||(right>=30&&right%10==0)){
				play_sound(1);
				if(Player[settingA_carsol].bMan==false&&Player[settingA_carsol].level<3)	Player[settingA_carsol].level++;
				Player[settingA_carsol].bMan = false;
			}
			if(bomb==1){
				play_sound(0);
				change_scene(SETTINGB);
			}
			if(spell==1){
				play_sound(2);
				change_scene(TITLE);
			}
		}
	}

	SetDrawBright(255,255,255);
	settingA_count++;
	
	return;
}

void MeSettingB(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	DrawBox(0,0,640,480,0,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	for(int i=0;i<PLAYER_NUM;i++){
		char message[7][64];
		float x = 50;
		float y = 50 + 100*i;
		float x2 = 150;
		float y2 = y-20;
		float x3 = 250;
		float y3 = y-40;
		for(int a=0;a<4;a++){
			if(settingB_carsol[a]==i){
				char me[2];
				wsprintf(me , "%d",a+1);
				SetDrawBright(100,100,255);
				draw_string(30,y,1,me);
				SetDrawBright(255,255,255);
				break;
			}
		}
		if(Player[i].bMan==true)	wsprintf(message[0] , "Player%d",i+1);
		else				wsprintf(message[0] , "COM%d   ",i+1);
		draw_string(x,y,7,message[0]);
		if(Player[i].get_chara()<FACE_GRAPH_NUM){
			DrawGraph(x2,y2,gFace[Player[i].get_chara()],TRUE);
		}
		if(Player[i].get_chara()==REIMU){
			wsprintf(message[1] , "博麗 霊夢");
			wsprintf(message[2] , "移動スピード：３");
			wsprintf(message[3] , "ゲージ増加度：４");
			wsprintf(message[4] , "スペルカード：「夢想封印」");
			wsprintf(message[5] , "敵を追尾するボムを３つ設置する");
			wsprintf(message[6] , "");
		}
		else if(Player[i].get_chara()==MARISA){
			wsprintf(message[1] , "霧雨 魔理沙");
			wsprintf(message[2] , "移動スピード：５");
			wsprintf(message[3] , "ゲージ増加度：３");
			wsprintf(message[4] , "スペルカード：「マスタースパーク」");
			wsprintf(message[5] , "自分の向いている方向に極太レーザーを放つ");
			wsprintf(message[6] , "");
		}
		else if(Player[i].get_chara()==SAKUYA){
			wsprintf(message[1] , "十六夜 咲夜");
			wsprintf(message[2] , "移動スピード：４");
			wsprintf(message[3] , "ゲージ増加度：３");
			wsprintf(message[4] , "スペルカード：「ジャック・ザ・リッパー」");
			wsprintf(message[5] , "一定時間、咲夜以外の時間が止まる");
			wsprintf(message[6] , "また、４方向に炸裂するボムを仕込む");
		}
		else if(Player[i].get_chara()==REMILIA){
			wsprintf(message[1] , "レミリア・スカーレット");
			wsprintf(message[2] , "移動スピード：３");
			wsprintf(message[3] , "ゲージ増加度：２");
			wsprintf(message[4] , "スペルカード：「全世界ナイトメア」");
			wsprintf(message[5] , "一定時間、世界が紅くなる");
			wsprintf(message[6] , "レミリアはこの攻撃によるダメージを受けない");
		}
		else if(Player[i].get_chara()==FRANDRE){
			wsprintf(message[1] , "フランドール・スカーレット");
			wsprintf(message[2] , "移動スピード：４");
			wsprintf(message[3] , "ゲージ増加度：２");
			wsprintf(message[4] , "スペルカード：「そして誰もいなくなるか？」");
			wsprintf(message[5] , "設置されているボムを最大火力で、");
			wsprintf(message[6] , "全て爆発させる");
		}
		else{
			wsprintf(message[1] , "ランダムセレクト");
			wsprintf(message[2] , "移動スピード：？");
			wsprintf(message[3] , "ゲージ増加度：？");
			wsprintf(message[4] , "スペルカード：「？？？？」");
			wsprintf(message[5] , "");
			wsprintf(message[6] , "");
		}
		for(int a=0;a<6;a++){
			int color = GetColor(255,255,255);
			if(a==0)	color = GetColor(255,200,200);
			DrawSt(x3,y3+15*a,color,0,font_default,message[a+1]);
		}
	}

	for(int i=0;i<4&&settingB_count!=0;i++){
		int bomb=0,spell=0,up=0,down=0,left=0,right=0;
		int settingB_num = FACE_GRAPH_NUM+1;
		int check_num = -1;
		if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
		else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
		else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
		else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
		if(check_num!=-1){
			bomb = c_pad[check_num][SAVE.Key_Bomb[i]];
			spell = c_pad[check_num][SAVE.Key_Spell[i]];
			up = c_pad[check_num][PAD_UP];
			down = c_pad[check_num][PAD_DOWN];
			left = c_pad[check_num][PAD_LEFT];
			right = c_pad[check_num][PAD_RIGHT];
		}
		else{
			bomb = c_key[KEY_INPUT_Z];
			spell = c_key[KEY_INPUT_X];
			up = c_key[KEY_INPUT_UP];
			down = c_key[KEY_INPUT_DOWN];
			left = c_key[KEY_INPUT_LEFT];
			right = c_key[KEY_INPUT_RIGHT];
		}
		if(settingB_carsol[i]>=0){
			if(left==1||(left>=30&&left%10==0)){
				play_sound(1);
				Player[settingB_carsol[i]].chara--;
				Player[settingB_carsol[i]].chara = (Player[settingB_carsol[i]].chara+settingB_num) % settingB_num;
			}
			if(right==1||(right>=30&&right%10==0)){
				play_sound(1);
				Player[settingB_carsol[i]].chara++;
				Player[settingB_carsol[i]].chara = Player[settingB_carsol[i]].chara % settingB_num;
			}
			if(bomb==1){
				play_sound(0);
				if(Player[settingB_carsol[i]].chara==FACE_GRAPH_NUM){
					Player[settingB_carsol[i]].chara = get_rand(FACE_GRAPH_NUM-1);
				}
				settingB_flag[settingB_carsol[i]] = true; 
				settingB_carsol[i] = -1;
				bool end = true;
				for(int a=0;a<4;a++){
					bool flag = true;
					for(int b=0;b<4;b++){
						if(settingB_flag[a]==true||settingB_carsol[b]==a){
							flag = false;
							break;
						}
					}
					if(flag==true){
						settingB_carsol[i] = a;
						break;	
					}
				}
				for(int a=0;a<4;a++){
					if(settingB_flag[a]==false){
						end = false;
						break;
					}
				}
				if(end==true){
					change_scene(SETTINGC);
				}
			}
		}
		if(spell==1||c_key[KEY_INPUT_X]==1){
			play_sound(2);
			change_scene(SETTINGA);
			break;
		}
	}
	char message[64];
	wsprintf(message , "左右キーでキャラを選択すること");
	int size = GetDrawStringWidthToHandle(message,64,font_default);
	SetDrawBright(255,255,255);
	DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);
	SetDrawBright(255,255,255);
	settingB_count++;
	
	return;
}

void MeSettingC(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	DrawBox(0,0,640,480,0,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	char message[4][64];
	float y = 200;
	wsprintf(message[0] , "STAGE");
	SetDrawBright(255,100,100);
	draw_string(100,y,5,message[0]);
	for(int i=0;i<64;i++){
		message[1][i] = '\0';
	}
	if(settingC_carsol[0]<MAP_NUM){
		wsprintf(message[1] , "%s",MapData[settingC_carsol[0]].name);
		SetDrawBright(255,255,255);
	}
	else{
		wsprintf(message[1] , "??RANDOM SELECT??");
		SetDrawBright(255,255,200);
	}
	draw_string(200,y,64,message[1]);
	y = 250;
	wsprintf(message[2] , "BGM");
	SetDrawBright(255,100,100);
	draw_string(100,y,3,message[2]);
	for(int i=0;i<64;i++){
		message[3][i] = '\0';
	}
	if(settingC_carsol[1]<BGM_NUM){
		wsprintf(message[3] , "%d",settingC_carsol[1]);
		SetDrawBright(255,255,255);
	}
	else{
		wsprintf(message[3] , "??RANDOM SELECT??");
		SetDrawBright(255,255,200);
	}
	draw_string(200,y,64,message[3]);

	if(settingC_count!=0&&settingC_count2==0){	
		int bomb=0,spell=0,up=0,down=0,left=0,right=0;
		int settingC_num[2] = {MAP_NUM+1,BGM_NUM+1};
		for(int i=0;i<4;i++){
			bomb += c_pad[i][SAVE.Key_Bomb[i]];
			spell += c_pad[i][SAVE.Key_Spell[i]];
			up += c_pad[i][PAD_UP];
			down += c_pad[i][PAD_DOWN];
			left += c_pad[i][PAD_LEFT];
			right += c_pad[i][PAD_RIGHT];
		}
		bomb += c_key[KEY_INPUT_Z];
		spell += c_key[KEY_INPUT_X];
		up += c_key[KEY_INPUT_UP];
		down += c_key[KEY_INPUT_DOWN];
		left += c_key[KEY_INPUT_LEFT];
		right += c_key[KEY_INPUT_RIGHT];
		
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			settingC_carsol[1]++;
			settingC_carsol[1] = settingC_carsol[1] % settingC_num[1];
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			settingC_carsol[1]--;
			settingC_carsol[1] = (settingC_carsol[1]+settingC_num[1]) % settingC_num[1];
		}
		if(left==1||(left>=30&&left%10==0)){
			play_sound(1);
			settingC_carsol[0]--;
			settingC_carsol[0] = (settingC_carsol[0]+settingC_num[0]) % settingC_num[0];
		}
		else if(right==1||(right>=30&&right%10==0)){
			play_sound(1);
			settingC_carsol[0]++;
			settingC_carsol[0] = settingC_carsol[0] % settingC_num[0];
		}
		if(bomb==1){
			play_sound(0);
			settingC_count2 = 1;
			stop_bgm();
		}
		if(spell==1){
			play_sound(2);
			change_scene(SETTINGB);
		}
	}
	
	char me[64];
	wsprintf(me , "ステージとＢＧＭを選択すること");
	int size = GetDrawStringWidthToHandle(me,64,font_default);
	SetDrawBright(255,255,255);
	DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,me);
	SetDrawBright(255,255,255);
	settingC_count++;
	if(settingC_count2>0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*settingC_count2);
		DrawBox(0,0,640,480,0,TRUE);
		if(settingC_count2==50){
			if(settingC_carsol[0]==MAP_NUM)	settingC_carsol[0] = get_rand(MAP_NUM-1);
			if(settingC_carsol[1]==BGM_NUM)	settingC_carsol[1] = get_rand(BGM_NUM-1);
			SReplay.rand_seed = rand_seed;
			GameLoad();
			replay_play = false;
			change_scene(GAME);
		}
		settingC_count2++;
	}
	
	return;
}

void MeEfMake(float x,float y,int img,int pattern){
	EFFECTDATA P;
	P.bDelete = false;
	P.bBlend = true;
	P.x = x;
	P.y = y;
	P.large = 1.0;
	P.angle = 0;
	P.move_x = 0;
	P.move_y = 0;
	P.speed = 0;
	P.img = gEffect[img];
	P.count = 0;
	P.pattern = pattern;
	P.flash = 255;
	P.red = 255;
	P.green = 255;
	P.blue = 255;
	for(int i=0;i<8;i++){
		P.f_hanyou[i] = 0;
		P.i_hanyou[i] = 0;
	}
	MeEffect.push_back(P);

	return;
}

void MeEfDraw(){
	for(list<EFFECTDATA>::iterator it=MeEffect.begin();it!=MeEffect.end();++it){
		MeEfMove(it);
		if((*it).bDelete==true){
			it = MeEffect.erase(it);
			it--;
			continue;			
		}
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		if((*it).bBlend==true)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(*it).flash);
		else			SetDrawBlendMode(DX_BLENDMODE_ADD,(*it).flash);
		SetDrawBright((*it).red,(*it).green,(*it).blue);
		DrawRotaGraphF((*it).x+shake_x,(*it).y+shake_y,(*it).large,(*it).angle,(*it).img,TRUE,FALSE);
		SetDrawBright(255,255,255);
	}

	return;
}

void MeEfMove(list<EFFECTDATA>::iterator &it){
	int c = (*it).count;
	int p = (*it).pattern;
	if(p==0){//メニューの白い光
		if(c==0){
			(*it).speed = 0.5+0.1*get_rand(15);
			(*it).f_hanyou[0] = 0.1;
			(*it).large = 0.1*(1+get_rand(9));
			(*it).move_x = cos(Radian(get_rand(360),TRUE));
			(*it).move_y = sin(Radian(get_rand(360),TRUE));
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 255;
		}
		if(menu_count<30){
			(*it).flash = 0;
		}
		else if(menu_count<60){
			(*it).flash = 4.25*(menu_count-30);
		}
		else if(c<60){
			(*it).flash = 2.1 * c;
		}
		else{
			(*it).flash = 127;
		}
		(*it).red = 255*sin(Radian(c/6,TRUE));
		(*it).green = 255*sin(Radian(2*c/6,TRUE));
		(*it).blue = 255*sin(Radian(3*c/6,TRUE));
		if((*it).x<-60||(*it).y<-60||(*it).x>700||(*it).y>540){
			(*it).bDelete = true;
			MeEfMake(get_rand(640),get_rand(480),0,0);
		}
	}


	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).count++;
	
        return;
}