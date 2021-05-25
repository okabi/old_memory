#include "menu.h"
#include "map.h"
#include "player.h"
#include "net.h"

list<EFFECTDATA> MeEffect;

int menu_count;
int title_carsol;
int select_re_count;
int select_re_count2;
int result_count;
int result_carsol;
int result2_count;
int result2_carsol;
int option_count;
int option_carsol;
int netsettingA_count;
int netsettingA_carsol[2];
int netsettingB_count;
int netsettingB_seleca;
int netsettingB_carsol[9];
int settingA_count;
int settingA_carsol;
int settingB_count;
int settingB_carsol[4];
bool settingB_flag[4];//�ݒ�I����Ă�H
int settingC_count;
int settingC_count2;
int settingC_carsol[3];

void MeLoad();
void MeMain();
void MeBackDraw();
void MeMenuDraw();
void MeMenuSelect();
void MeSelect_Replay();
void MeResult();
void MeResult2();
void MeOption();
void KeyToChar(int key,char *buffer);
void MeNetSettingA();
void MeNetSettingB();
void MeSettingA();
void MeSettingB();
void MeSettingC();
void MeEfMake(float x,float y,int img,int pattern);
void MeEfDraw();
void MeEfMove(list<EFFECTDATA>::iterator &it);

void MeLoad(){
	MeEffect.clear();
	for(int i=0;i<100;i++)	MeEfMake(get_rand(640), get_rand(520),0,0);
	title_carsol = 0;
	menu_count = 0;
	result_count = 0;
	result_carsol = 0;
	result2_count = 0;
	result2_carsol = 0;
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
	else if(scene==SELECT_REPLAY)MeSelect_Replay();
	else if(scene==RESULT)	MeResult();
	else if(scene==RESULT2)	MeResult2();
	else if(scene==OPTION)	MeOption();
	else if(scene==SETTINGA)	MeSettingA();
	else if(scene==SETTINGB)	MeSettingB();
	else if(scene==SETTINGC)	MeSettingC();
	else if(scene==NETSETTINGA)	MeNetSettingA();
	else if(scene==NETSETTINGB)	MeNetSettingB();
	
	menu_count++;
	return;
}

void MeBackDraw(){
	if(menu_count<120){
		if(menu_count<60)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*menu_count);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		const int graph_size = 87;
		static int graph[graph_size];
		float large = 1.0 + 0.02*(120-menu_count);
		if(menu_count==0){
			for(int i=0;i<graph_size;i++){
				graph[i] = DerivationGraph(0,i,239,1,gMenu[0]);
			}
		}
		for(int i=0;i<graph_size;i++){
			float wave = (120-menu_count)*sin(Radian(5*menu_count+12*i,TRUE));
			if(menu_count>=120)	wave = 0;
			DrawRotaGraphF(320+wave,240-graph_size*large/2.0+large*i,large,0,graph[i],TRUE,FALSE);
		}
	}
	else{
		float x=320,y=120;
		float back_y = 240+150*sin(Radian(menu_count/6.0,TRUE));
		float flash_num = 2.125*(menu_count-120);
		if(menu_count<240){
			x = 320;
			y = 120+120*cos(Radian(0.75*(menu_count-120),TRUE));
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash_num);
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			flash_num = 255;
		}
		DrawRotaGraphF(320,back_y,1.0,0,gMenuBack,TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash_num/3.0);
		DrawBox(0,0,640,480,GetColor(100,100,255),TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash_num);
		char message[128];
		wsprintf(message , "ver0.94a");
		DrawFormatString(0,468,GetColor(255,255,255),message);
		wsprintf(message , "2010 (C)opyright okabi. All rights reserved.");
		int size = GetDrawStringWidth(message,128);
		int size2 = GetDrawStringWidth("60.00 fps",128);
		DrawFormatString(640-size,468,GetColor(255,255,255),message);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawRotaGraphF(x,y,1.0,0,gMenu[0],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ADD,flash_num/5.1);
		DrawRotaGraphF(x,y,2.0+sin(Radian(menu_count,TRUE)),0,gMenu[0],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ADD,flash_num/5.1);
		DrawRotaGraphF(x,y,2.0,Radian(menu_count/2,TRUE),gMenu[0],TRUE,FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ADD,flash_num/5.1);
		DrawRotaGraphF(x,y,2.0,Radian(-menu_count/2,TRUE),gMenu[0],TRUE,FALSE);
	}
	
	return;
}

void MeMenuDraw(){
	for(int i=0;i<6;i++){
		float x = 320+10*sin(Radian(menu_count+60*i,TRUE));
		float y = 300+30*i;
		if(menu_count<240)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,2.125*(menu_count-120));
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(title_carsol!=i)	SetDrawBright(150,150,150);
		DrawRotaGraphF(x,y,1.0,0,gMenu[i+1],TRUE,FALSE);
		SetDrawBright(255,255,255);
	}

	return;
}

void MeMenuSelect(){
	if(menu_count<240)	return;
	int bomb=0,spell=0,up=0,down=0,left=0,right=0;
	int title_num = 6;
	for(int i=0;i<4;i++){
		int check_num = -1;
		if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
		else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
		else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
		else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
		if(check_num!=-1){
			bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
			spell += c_pad[check_num][SAVE.Key_Spell[i]];
			up += c_pad[check_num][PAD_UP];
			down += c_pad[check_num][PAD_DOWN];
			left += c_pad[check_num][PAD_LEFT];
			right += c_pad[check_num][PAD_RIGHT];
		}
	}
	bomb += c_key[KEY_INPUT_Z];
	bomb += c_key[KEY_INPUT_RETURN];
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
			change_scene(NETSETTINGA);
		}
		if(title_carsol==2){
			select_re_count = 0;
			select_re_count2 = 0;
			change_scene(SELECT_REPLAY);
		}
		if(title_carsol==3){
			result_count = 0;
			result_carsol = 0;
			change_scene(RESULT);
		}
		if(title_carsol==4){
			option_count = 0;
			option_carsol = 0;
			change_scene(OPTION);
		}
		if(title_carsol==5){
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
				wsprintf(message , "No.%2d %02d/%s/%02d  winner:%-20s  %2dmatches",i+1, Replay[i].year%2000, message2, Replay[i].day, Replay[i].name[Replay[i].last_winner], Replay[i].match);
			}
			else{
				wsprintf(message , "No.%2d --/---/--  winner:%-20s  --matches",i+1, "----------------");
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
				int check_num = -1;
				if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
				if(check_num!=-1){
					bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
					spell += c_pad[check_num][SAVE.Key_Spell[i]];
					up += c_pad[check_num][PAD_UP];
					down += c_pad[check_num][PAD_DOWN];
					left += c_pad[check_num][PAD_LEFT];
					right += c_pad[check_num][PAD_RIGHT];
				}
			}
			bomb += c_key[KEY_INPUT_Z];
			bomb += c_key[KEY_INPUT_RETURN];
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
		wsprintf(message , "�㉺�L�[�Ń��v���C��I�����邱��");
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
			settingC_carsol[1] = Replay[replay_play_num].bgm[0];
			settingC_carsol[2] = Replay[replay_play_num].bgm[1];
			for(int i=0;i<4;i++){
				Player[i].chara = Replay[replay_play_num].player[i];
				Player[i].color = Replay[replay_play_num].player_color[i];
				Player[i].bMan = Replay[replay_play_num].bMan[i];
			}
			SAVE.MatchNum = Replay[replay_play_num].matchnum;
			SAVE.MatchTime = Replay[replay_play_num].matchtime;
			rand_seed = Replay[replay_play_num].rand_seed;
			GameLoad();
			replay_play = true;
			change_scene(GAME);
		}
		select_re_count2++;
	}
	select_re_count ++;

	return;
}

void MeResult(){
	if(result_count<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		float x = 11*result_count;
		float y = 8*result_count;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
	}
	else{
		static int ranking[PROFILE_NUM];
		static int rank_num;
		static int rank_top;
		static int rank_end;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(result_count==30){
			for(int i=0;i<PROFILE_NUM;i++){
				ranking[i] = -1;
			}
			rank_num = 0;
			rank_top = 0;
			rank_end = 19;
			for(int i=0;i<PROFILE_NUM;i++){
				if(Profile[i].exist==true){
					ranking[rank_num] = i;
					rank_num++;
				}
			}
			while(1){
				bool flag = true;
				for(int i=0;i<PROFILE_NUM-1;i++){
					if(ranking[i]==-1||ranking[i+1]==-1)	break;
					if(Profile[ranking[i]].rate<Profile[ranking[i+1]].rate){
						int swap = ranking[i];
						ranking[i] = ranking[i+1];
						ranking[i+1] = swap;
						flag = false;
					}
				}
				if(flag==true)	break;
			}
		}
		for(int i=0;i<rank_end-rank_top+1;i++){
			if(i+rank_top==result_carsol){
				SetDrawBright(255,255,255);
			}
			else{
				SetDrawBright(100,100,100);
			}
			char message[128];
		
			wsprintf(message , "%2d: %-30s Rate.---- ID.----",i+1+rank_top, "----------------");
			int size = GetDrawStringWidthToHandle(message,64,font_default);
			int xplus = 320-size/2;
			wsprintf(message , "%2d: ",i+1+rank_top);
			int size2 = GetDrawStringWidthToHandle(message,64,font_default);
			wsprintf(message , "%-30s ","----------------");
			int size3 = GetDrawStringWidthToHandle(message,64,font_default);
			wsprintf(message , "Rate.---- ");
			int size4 = GetDrawStringWidthToHandle(message,64,font_default);

			wsprintf(message , "%2d: ",i+1+rank_top);
			DrawSt(xplus,100+15*i,GetColor(255,255,255),0,font_default,message);
			xplus += size2;
			if(i+rank_top<rank_num)	wsprintf(message , "%-30s ",Profile[ranking[i+rank_top]].name);
			else			wsprintf(message , "%-30s ","----------------");
			DrawSt(xplus,100+15*i,GetColor(255,255,255),0,font_default,message);
			size = GetDrawStringWidthToHandle(message,64,font_default);
			xplus += size3;
			if(i+rank_top<rank_num)	wsprintf(message , "Rate.%4d ",Profile[ranking[i+rank_top]].rate);
			else			wsprintf(message , "Rate.---- ");
			DrawSt(xplus,100+15*i,GetColor(255,255,255),0,font_default,message);
			size = GetDrawStringWidthToHandle(message,64,font_default);
			xplus += size4;
			if(i+rank_top<rank_num)	wsprintf(message , "ID.%04x",Profile[ranking[i+rank_top]].ID);
			else			wsprintf(message , "ID.----");
			DrawSt(xplus,100+15*i,GetColor(255,255,255),0,font_default,message);
			/*
			if(i+rank_top<rank_num)	wsprintf(message , "%2d: %-30s Rate.%4d ID.%04x",i+1+rank_top, Profile[ranking[i+rank_top]].name, Profile[ranking[i+rank_top]].rate, Profile[ranking[i+rank_top]].ID);
			else		wsprintf(message , "%2d: %-30s Rate.---- ID.----",i+1+rank_top, "----------------");
			int size = GetDrawStringWidthToHandle(message,64,font_default);
			DrawSt(320-size/2,100+15*i,GetColor(255,255,255),0,font_default,message);
			*/
		}
		SetDrawBright(255,255,255);
		
		int bomb=0,spell=0,up=0,down=0,left=0,right=0;
		int result_num = rank_num;
		for(int i=0;i<4;i++){
			int check_num = -1;
			if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
			if(check_num!=-1){
				bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
				spell += c_pad[check_num][SAVE.Key_Spell[i]];
				up += c_pad[check_num][PAD_UP];
				down += c_pad[check_num][PAD_DOWN];
				left += c_pad[check_num][PAD_LEFT];
				right += c_pad[check_num][PAD_RIGHT];
			}
		}
		bomb += c_key[KEY_INPUT_Z];
		bomb += c_key[KEY_INPUT_RETURN];
		spell += c_key[KEY_INPUT_X];
		up += c_key[KEY_INPUT_UP];
		down += c_key[KEY_INPUT_DOWN];
		left += c_key[KEY_INPUT_LEFT];
		right += c_key[KEY_INPUT_RIGHT];
		
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			result_carsol++;
			result_carsol = result_carsol % result_num;
			if(result_carsol>rank_end){
				rank_top++;
				rank_end++;
			}
			if(result_carsol<rank_top){
				rank_end = rank_end-rank_top;
				rank_top = 0;
			}
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			result_carsol--;
			result_carsol = (result_carsol+result_num) % result_num;
			if(result_carsol>rank_end){
				rank_top = rank_num-1-(rank_end-rank_top);
				rank_end = rank_num-1;
			}
			if(result_carsol<rank_top){
				rank_top--;
				rank_end--;
			}
		}
		if(bomb==1){
			play_sound(0);
			result2_carsol = ranking[result_carsol];
			result2_count = 0;
			change_scene(RESULT2);
		}
		if(spell==1){
			play_sound(2);
			change_scene(TITLE);
		}
		char message[64];
		wsprintf(message , "�{���L�[�ŏڍׂ�����B�X�y���L�[�Ń^�C�g���ɖ߂�");
		int size = GetDrawStringWidthToHandle(message,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);
		SetDrawBright(255,255,255);
	}
	result_count ++;

	return;
}

void MeResult2(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
	DrawBox(0,0,640,480,0,TRUE);
	if(1){
		if(result2_count<50){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*result2_count);		
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);		
		}
		char message[128];
		int chara_sum=0;
		for(int i=0;i<PLAYER_GRAPH_NUM;i++)	chara_sum += Profile[result2_carsol].chara_num[i];
		for(int i=0;i<12+PLAYER_GRAPH_NUM;i++){
			SetDrawBright(255,255,255);
			switch(i){
				case 0:
					SetDrawBright(255,150,150);
					wsprintf(message, "�v���C���[���F%s",Profile[result2_carsol].name);
					break;
				case 1:
					if(1){
						char me[32];
						if(Profile[result2_carsol].rate<3500)		wsprintf(me,"�g����");
						else if(Profile[result2_carsol].rate<4000)	wsprintf(me,"�ы�");
						else if(Profile[result2_carsol].rate<4500)	wsprintf(me,"�d��");
						else if(Profile[result2_carsol].rate<5000)	wsprintf(me,"�������d��");
						else if(Profile[result2_carsol].rate<5200)	wsprintf(me,"���ł̗d��");
						else if(Profile[result2_carsol].rate<5400)	wsprintf(me,"�Ώ�̕X��");
						else if(Profile[result2_carsol].rate<5600)	wsprintf(me,"�ؐl����");
						else if(Profile[result2_carsol].rate<5800)	wsprintf(me,"�m���Ɠ��A�̏���");
						else if(Profile[result2_carsol].rate<6000)	wsprintf(me,"�g���ق̃��C�h");
						else if(Profile[result2_carsol].rate<6500)	wsprintf(me,"�i���ɍg���c����");
						else if(Profile[result2_carsol].rate<7000)	wsprintf(me,"�����̖�");
						else						wsprintf(me,"�V��");
						wsprintf(message, "���[�g�F%4d�@�̍��F%s�@�@�h�c�F%04x",Profile[result2_carsol].rate, me, Profile[result2_carsol].ID);
					}
					break;
				case 2:
					if(1){
						int num[3];
						num[0] = Profile[result2_carsol].playtime/3600;
						num[1] = (Profile[result2_carsol].playtime-num[0]*3600)/60;
						num[2] = Profile[result2_carsol].playtime-num[0]*3600-num[1]*60;
						wsprintf(message, "�v���C���ԁF %2d:%02d:%02d",num[0], num[1], num[2]);
					}
					break;
				case 3:
					wsprintf(message, "�����񐔁F%d�@�@�����F%d��@�Q�ʁF%d��@�R�ʁF%d��@�S�ʁF%d��",Profile[result2_carsol].match_num, Profile[result2_carsol].win_num, Profile[result2_carsol].lose_num[0], Profile[result2_carsol].lose_num[1], Profile[result2_carsol].lose_num[2]);
					break;
				case 4:
					if(Profile[result2_carsol].match_num==0)	wsprintf(message, "�����F0.0��");
					else	sprintf(message, "�����F%.1f��",(float)Profile[result2_carsol].win_num/(float)Profile[result2_carsol].match_num*100.0);
					break;
				case 5:
					wsprintf(message, "���S�܂ł̕��όo�ߎ��ԁF%d�b",Profile[result2_carsol].death_average);
					break;
				case 6:
					if(Profile[result2_carsol].sadon_match_num==0)	wsprintf(message, "�T�h���f�X�܂Ő����c���Ă���m���F0.0��");
					else	sprintf(message, "�T�h���f�X�܂Ő����c���Ă���m���F%.1f��",(float)Profile[result2_carsol].sadon_num/(float)Profile[result2_carsol].sadon_match_num*100.0);
					break;
				case 7:
					wsprintf(message, "�������v���C���[���F%d�l",Profile[result2_carsol].kill_num);
					break;
				case 8:
					wsprintf(message, "�݂��{���ő������v���C���[���F%d�l",Profile[result2_carsol].miso_kill_num);
					break;
				case 9:
					wsprintf(message, "���E�񐔁F%d��@�@���S�񐔁F%d��@�@�e����e�񐔁F%d��",Profile[result2_carsol].killme_num, Profile[result2_carsol].death_num, Profile[result2_carsol].danmaku_num);
					break;
				case 10:
					if(Profile[result2_carsol].death_num==0)	wsprintf(message, "���ŗ��F0.0���@�@�e����e���F0.0��");
					else	sprintf(message, "���ŗ��F%.1f���@�@�e����e���F%.1f��",(float)Profile[result2_carsol].killme_num/(float)Profile[result2_carsol].death_num*100.0, (float)Profile[result2_carsol].danmaku_num/(float)Profile[result2_carsol].death_num*100.0);
					break;
				case 11:
					if(1){
						char me[32];
						if(Profile[result2_carsol].max_rate<3500)	wsprintf(me,"�g����");
						else if(Profile[result2_carsol].max_rate<4000)	wsprintf(me,"�ы�");
						else if(Profile[result2_carsol].max_rate<4500)	wsprintf(me,"�d��");
						else if(Profile[result2_carsol].max_rate<5000)	wsprintf(me,"�������d��");
						else if(Profile[result2_carsol].max_rate<5200)	wsprintf(me,"���ł̗d��");
						else if(Profile[result2_carsol].max_rate<5400)	wsprintf(me,"�Ώ�̕X��");
						else if(Profile[result2_carsol].max_rate<5600)	wsprintf(me,"�ؐl����");
						else if(Profile[result2_carsol].max_rate<5800)	wsprintf(me,"�m���Ɠ��A�̏���");
						else if(Profile[result2_carsol].max_rate<6000)	wsprintf(me,"�g���ق̃��C�h");
						else if(Profile[result2_carsol].max_rate<6500)	wsprintf(me,"�i���ɍg���c����");
						else if(Profile[result2_carsol].max_rate<7000)	wsprintf(me,"�����̖�");
						else						wsprintf(me,"�V��");
						wsprintf(message, "�ō��A���񐔁F%d��@�@�ō����[�g�F%d(%s)",Profile[result2_carsol].max_renbaku, Profile[result2_carsol].max_rate, me);
					}
					break;
			}
			if(i<12)	DrawSt(50,100+18*i,GetColor(255,255,255),0,font_default,message);				
			if(i>=12&&chara_sum>0){
				if(i==12)	sprintf(message, "�@�얲�@�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==13)	sprintf(message, "�@�������@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==14)	sprintf(message, "�@���@�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==15)	sprintf(message, "�@���~���A�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==16)	sprintf(message, "�@�t�����h�[���F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==17)	sprintf(message, "�@�d���@�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==18)	sprintf(message, "�@�H�X�q�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==19)	sprintf(message, "�@���@�@�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==20)	sprintf(message, "�@��� �@ �@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==21)	sprintf(message, "�@�ɂƂ�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==22)	sprintf(message, "�@���c�@�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i==23)	sprintf(message, "�@��@�@�@�@�@�F%d��@%.1f��",Profile[result2_carsol].chara_num[i-12], (float)Profile[result2_carsol].chara_num[i-12]/(float)chara_sum*100.0);			
				if(i<=17)	DrawSt(50,100+18*i,GetColor(255,255,255),0,font_default,message);				
				else		DrawSt(300,100+18*(i-6),GetColor(255,255,255),0,font_default,message);				
			}
		}
		
		if(result2_count>=50){
			int bomb=0,spell=0,up=0,down=0,left=0,right=0;
			for(int i=0;i<4;i++){
				int check_num = -1;
				if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
				if(check_num!=-1){
					bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
					spell += c_pad[check_num][SAVE.Key_Spell[i]];
					up += c_pad[check_num][PAD_UP];
					down += c_pad[check_num][PAD_DOWN];
					left += c_pad[check_num][PAD_LEFT];
					right += c_pad[check_num][PAD_RIGHT];
				}
			}
			bomb += c_key[KEY_INPUT_Z];
			bomb += c_key[KEY_INPUT_RETURN];
			spell += c_key[KEY_INPUT_X];
			up += c_key[KEY_INPUT_UP];
			down += c_key[KEY_INPUT_DOWN];
			left += c_key[KEY_INPUT_LEFT];
			right += c_key[KEY_INPUT_RIGHT];
		
			if(bomb==1||spell==1){
				play_sound(2);
				change_scene(RESULT);
			}
		}
		wsprintf(message , "�{���E�X�y���L�[�Ŗ߂�");
		int size = GetDrawStringWidthToHandle(message,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);
		SetDrawBright(255,255,255);
	}
	result2_count ++;

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
		wsprintf(message , "���N�����ԁ@%d:%02d:%02d",time[0],time[1],time[2]);
		DrawSt(350,150,GetColor(255,255,255),0,font_default,message);
		wsprintf(message2 , "�v���C�񐔁@%d��",SAVE.PlayCount);
		DrawSt(350,170,GetColor(255,255,255),0,font_default,message2);
		if(option_carsol==0){
			wsprintf(message , "�a�f�l���ʂ�ݒ肵�܂�(0�`100)");
			wsprintf(message2 , "�H��ݒ�: 100");
		}
		else if(option_carsol==1){
			wsprintf(message , "���ʉ����ʂ�ݒ肵�܂�(0�`100)");
			wsprintf(message2 , "�H��ݒ�: 50");
		}
		else if(option_carsol==22){
			wsprintf(message , "��������ݒ肵�܂�(1�`5)");
			wsprintf(message2 , "�H��ݒ�: 3");
		}
		else if(option_carsol==23){
			wsprintf(message , "�������Ԃ�ݒ肵�܂�(90�b�`300�b)");
			wsprintf(message2 , "�H��ݒ�: 150�b");
		}
		else if(option_carsol==24){
			wsprintf(message , "�S�Ă̐ݒ���H��ݒ�ɖ߂��܂�");
			wsprintf(message2 , "");
		}
		else if(option_carsol==25){
			wsprintf(message , "�^�C�g���ɖ߂�܂�");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==0){
			wsprintf(message , "���[�U�[���w�肵�܂�");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==1){
			wsprintf(message , "���͑��u��ݒ肵�܂�");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==2){
			wsprintf(message , "�{���E����L�[��ݒ肵�܂�");
			wsprintf(message2 , "");
		}
		else if((option_carsol-2)%5==3){
			wsprintf(message , "�X�y���J�[�h�E�L�����Z���L�[��");
			wsprintf(message2 , "�ݒ肵�܂�");
		}
		else if((option_carsol-2)%5==4){
			wsprintf(message , "�|�[�Y�L�[��ݒ肵�܂�");
			wsprintf(message2 , "");
		}
		DrawSt(350,190,GetColor(150,150,255),0,font_default,message);
		DrawSt(350,205,GetColor(150,150,255),0,font_default,message2);
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
				if(i==option_carsol){
					SetDrawBright(255,50,50);
				}
				else{
					SetDrawBright(150,50,50);
				}
				wsprintf(message , "KEYCONFIG %dP",(i-2)/5+1);
				draw_string(x,y,64,message);
				char player[MAX_NAME];
				if(SAVE.User[(i-2)/5]==-1)	wsprintf(player,"�Q�X�g");
				else	wsprintf(player,"%s",Profile[SAVE.User[(i-2)/5]].name);
				DrawSt(250,y,GetColor(255,255,255),0,font_default,player);
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
			int check_num = -1;
			if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
			if(check_num!=-1){
				bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
				spell += c_pad[check_num][SAVE.Key_Spell[i]];
				up += c_pad[check_num][PAD_UP];
				down += c_pad[check_num][PAD_DOWN];
				left += c_pad[check_num][PAD_LEFT];
				right += c_pad[check_num][PAD_RIGHT];
			}
		}
		bomb += c_key[KEY_INPUT_Z];
		bomb += c_key[KEY_INPUT_RETURN];
		spell += c_key[KEY_INPUT_X];
		up += c_key[KEY_INPUT_UP];
		down += c_key[KEY_INPUT_DOWN];
		left += c_key[KEY_INPUT_LEFT];
		right += c_key[KEY_INPUT_RIGHT];
		
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			option_carsol++;
			option_carsol = option_carsol % option_num;
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			option_carsol--;
			option_carsol = (option_carsol+option_num) % option_num;
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
				while(1){
					int keynum=0, keynum2=0, keynum3=0, keynum4=0, keynum5=0;
					if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD1)		SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_KEY;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD2)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD1;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD3)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD2;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD4)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD3;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_KEY)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD4;
					for(int j=0;j<4;j++){
						if(SAVE.Key_Type[j]==DX_INPUT_KEY)	keynum++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD1)	keynum2++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD2)	keynum3++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD3)	keynum4++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD4)	keynum5++;
					}
					if(keynum<=1 && keynum2<=1 && keynum3<=1 && keynum4<=1 && keynum5<=1)	break;
				}
			}
			else if((option_carsol-2)%5==0){
				if(SAVE.User[(option_carsol-2)/5]>=0){
					for(;SAVE.User[(option_carsol-2)/5]>-1;){
						SAVE.User[(option_carsol-2)/5]--;
						if(Profile[SAVE.User[(option_carsol-2)/5]].exist==true){
							bool flag = true;
							for(int i=0;i<4;i++){
								if(SAVE.User[i]!=-1&&(option_carsol-2)/5!=i&&SAVE.User[(option_carsol-2)/5]==SAVE.User[i]){
									flag = false;
								}
							}
							if(flag==true)	break;	
						}
					}
				}
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
				while(1){
					int keynum=0, keynum2=0, keynum3=0, keynum4=0, keynum5=0;
					if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD1)		SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD2;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD2)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD3;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD3)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD4;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_PAD4)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_KEY;
					else if(SAVE.Key_Type[(option_carsol-2)/5]==DX_INPUT_KEY)	SAVE.Key_Type[(option_carsol-2)/5] = DX_INPUT_PAD1;
					for(int j=0;j<4;j++){
						if(SAVE.Key_Type[j]==DX_INPUT_KEY)	keynum++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD1)	keynum2++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD2)	keynum3++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD3)	keynum4++;
						if(SAVE.Key_Type[j]==DX_INPUT_PAD4)	keynum5++;
					}
					if(keynum<=1 && keynum2<=1 && keynum3<=1 && keynum4<=1 && keynum5<=1)	break;
				}
			}
			else if((option_carsol-2)%5==0){
				if(SAVE.User[(option_carsol-2)/5]<PROFILE_NUM-1){
					int def = SAVE.User[(option_carsol-2)/5];
					for(;SAVE.User[(option_carsol-2)/5]<PROFILE_NUM-1;){
						SAVE.User[(option_carsol-2)/5]++;
						if(Profile[SAVE.User[(option_carsol-2)/5]].exist==true){
							bool flag = true;
							for(int i=0;i<4;i++){
								if((option_carsol-2)/5!=i&&SAVE.User[(option_carsol-2)/5]==SAVE.User[i]){
									flag = false;
								}
							}
							if(flag==true)	break;
							else if(SAVE.User[(option_carsol-2)/5]==PROFILE_NUM-1){
								SAVE.User[(option_carsol-2)/5] = def;
								break;
							}
						}
					}
					if(Profile[SAVE.User[(option_carsol-2)/5]].exist==false)	SAVE.User[(option_carsol-2)/5] = def;	
				}
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

void MeNetSettingA(){
	if(netsettingA_count<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
		float x = 11*netsettingA_count;
		float y = 8*netsettingA_count;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
		if(netsettingA_count==0){
			NetWork.Reset();
		}
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
		DrawBox(0,0,640,480,0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<2;i++){
			char message[64];
			for(int a=0;a<64;a++){
				message[a] = '\0';
			}
			float x = 150;
			float x2 = 300;
			float y = 200 + 50*i;
			if(netsettingA_carsol[0]==i)	SetDrawBright(255,200,200);
			else				SetDrawBright(55,0,0);
			if(i==0)	wsprintf(message , "�N���C�A���g");
			else		wsprintf(message , "�T�[�o");
			DrawSt(x,y,GetColor(255,255,255),0,font_default,message);
			if(i==0){
				for(int j=0;j<4;j++){
					for(int a=0;a<3;a++){
						if(netsettingA_carsol[0]==i){
							if(netsettingA_carsol[1]==3*j+a)	SetDrawBright(255,255,255);
							else					SetDrawBright(100,100,100);
						}
						else{
							SetDrawBright(100,100,100);
						}
						char me2[2];
						wsprintf(me2 , "%d", NetWork.draw_IP[j][a]);
						DrawSt(x2,y,GetColor(255,255,255),0,font_default,me2);
						x2 += GetDrawStringWidthToHandle(me2,2,font_default);;
					}
					if(j!=3){
						char me2[2];
						SetDrawBright(100,100,100);
						wsprintf(me2 , ".");
						DrawSt(x2,y,GetColor(255,255,255),0,font_default,me2);
						x2 += GetDrawStringWidthToHandle(me2,2,font_default);;
					}
				}
				x2 += 20;
				for(int a=0;a<5;a++){
					if(netsettingA_carsol[0]==i){
						if(netsettingA_carsol[1]==12+a)	SetDrawBright(255,255,255);
						else				SetDrawBright(100,100,100);
					}
					else{
						SetDrawBright(100,100,100);
					}
					char me2[2];
					wsprintf(me2 , "%d", NetWork.draw_port[a]);
					DrawSt(x2,y,GetColor(255,255,255),0,font_default,me2);
					x2 += GetDrawStringWidthToHandle(me2,2,font_default);;
				}
			}
			else{
				for(int a=0;a<5;a++){
					if(netsettingA_carsol[0]==i){
						if(netsettingA_carsol[1]==12+a)	SetDrawBright(255,255,255);
						else				SetDrawBright(100,100,100);
					}
					else{
						SetDrawBright(100,100,100);
					}
					char me2[2];
					wsprintf(me2 , "%d", NetWork.draw_port[a]);
					DrawSt(x2,y,GetColor(255,255,255),0,font_default,me2);
					x2 += GetDrawStringWidthToHandle(me2,2,font_default);;
				}
			}
		}
		char message[64];
		wsprintf(message , "�N���C�A���g�E�T�[�o�̑I���B�h�o�A�h���X�E�|�[�g�ԍ��̕ύX���\");
		int size = GetDrawStringWidthToHandle(message,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);
		size = GetDrawStringWidthToHandle(LOG,128,font_default);
		DrawSt(320-size/2,350,GetColor(255,150,255),0,font_default,LOG);

		if(netsettingA_count!=30&&NetWork.wait_count==-1){	
			int bomb=0,spell=0,up=0,down=0,left=0,right=0;
			int netsettingA_num = 2;
			int check_num = -1;
			if(SAVE.Key_Type[0]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[0]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[0]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[0]==DX_INPUT_PAD4)	check_num = 3;
			if(check_num!=-1){
				bomb += c_pad[check_num][SAVE.Key_Bomb[0]];
				spell += c_pad[check_num][SAVE.Key_Spell[0]];
				up += c_pad[check_num][PAD_UP];
				down += c_pad[check_num][PAD_DOWN];
				left += c_pad[check_num][PAD_LEFT];
				right += c_pad[check_num][PAD_RIGHT];
			}
			bomb += c_key[KEY_INPUT_Z];
			bomb += c_key[KEY_INPUT_RETURN];
			spell += c_key[KEY_INPUT_X];
			up += c_key[KEY_INPUT_UP];
			down += c_key[KEY_INPUT_DOWN];
			left += c_key[KEY_INPUT_LEFT];
			right += c_key[KEY_INPUT_RIGHT];
			
			if(down==1||(down>=30&&down%10==0)){
				play_sound(1);
				if(netsettingA_carsol[1]==-1){
					netsettingA_carsol[0]++;
					netsettingA_carsol[0] = netsettingA_carsol[0] % netsettingA_num;
				}
				else if(netsettingA_carsol[1]<12){
					int i = netsettingA_carsol[1]/3;
					NetWork.draw_IP[i][netsettingA_carsol[1]-i*3]--;
					NetWork.draw_IP[i][netsettingA_carsol[1]-i*3] = (NetWork.draw_IP[i][netsettingA_carsol[1]-i*3]+10) % 10;
				}
				else{
					int i = netsettingA_carsol[1]-12;
					NetWork.draw_port[i]--;
					NetWork.draw_port[i] = (NetWork.draw_port[i]+10) % 10;
				}
			}
			else if(up==1||(up>=30&&up%10==0)){
				play_sound(1);
				if(netsettingA_carsol[1]==-1){
					netsettingA_carsol[0]--;
					netsettingA_carsol[0] = (netsettingA_carsol[0]+netsettingA_num) % netsettingA_num;
				}
				else if(netsettingA_carsol[1]<12){
					int i = netsettingA_carsol[1]/3;
					NetWork.draw_IP[i][netsettingA_carsol[1]-i*3]++;
					NetWork.draw_IP[i][netsettingA_carsol[1]-i*3] = NetWork.draw_IP[i][netsettingA_carsol[1]-i*3] % 10;
				}
				else{
					int i = netsettingA_carsol[1]-12;
					NetWork.draw_port[i]++;
					NetWork.draw_port[i] = NetWork.draw_port[i] % 10;
				}
			}
			if(left==1||(left>=30&&left%10==0)){
				play_sound(1);
				if(netsettingA_carsol[0]==0&&netsettingA_carsol[1]>-1)		netsettingA_carsol[1]--;
				else if(netsettingA_carsol[0]==1&&netsettingA_carsol[1]>12)	netsettingA_carsol[1]--;
				else if(netsettingA_carsol[0]==1)	netsettingA_carsol[1] = -1;
			}
			else if(right==1||(right>=30&&right%10==0)){
				play_sound(1);
				if(netsettingA_carsol[0]==1&&netsettingA_carsol[1]==-1)		netsettingA_carsol[1] = 12;
				else if(netsettingA_carsol[1]<16)		netsettingA_carsol[1]++;
			}
			if(bomb==1&&SAVE.User[0]!=-1){
				play_sound(0);
				for(int i=0;i<MAX_LOG;i++){
					LOG[i] = '\0';
				}
				NetWork.wait_count = 0;
			}
			else if(bomb==1){
				play_sound(24);
			}
			if(spell==1){
				play_sound(2);
				change_scene(TITLE);
			}
		}
		else if(NetWork.wait_count>=0){
			if(netsettingA_carsol[0]==0)	NetWork.ClientFunction();
			else	NetWork.HostFunction();
		}
	}

	SetDrawBright(255,255,255);
	netsettingA_count++;
	
	return;
}

void MeNetSettingB(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	DrawBox(0,0,640,480,0,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	if(NetWork.host_num==-1){//�������z�X�g
		for(int i=0;i<8;i++){
			char message[64];
			char message2[64];
			for(int a=0;a<64;a++){
				message[a] = '\0';
				message2[a] = '\0';
			}
			float x = 150;
			float x2 = 250;
			float y = 100 + 40*i;
			if(netsettingB_seleca==i)	SetDrawBright(255,200,200);
			else				SetDrawBright(55,0,0);
			if(i<4)		wsprintf(message , "Player%d", i+1);
			else if(i==4)	wsprintf(message , "�X�e�[�W");
			else if(i==5)	wsprintf(message , "������");
			else if(i==6)	wsprintf(message , "��������");
			else if(i==7)	wsprintf(message , "�a�f�l");
			DrawSt(x,y,GetColor(255,255,255),0,font_default,message);
			if(i<4){
				if(NetWork.NFD[0].connect_num<=netsettingB_carsol[i])	wsprintf(message2 , "%s", NetWork.NFD[netsettingB_carsol[i]].name);
				else{
					char leve[8];
					if(netsettingB_carsol[i]-NetWork.NFD[0].connect_num==1)	wsprintf(leve, "Easy");
					if(netsettingB_carsol[i]-NetWork.NFD[0].connect_num==2)	wsprintf(leve, "Normal");
					if(netsettingB_carsol[i]-NetWork.NFD[0].connect_num==3)	wsprintf(leve, "Hard");
					if(netsettingB_carsol[i]-NetWork.NFD[0].connect_num==4)	wsprintf(leve, "Lunatic");
					wsprintf(message2 , "COM(%s)", leve);
				}
				if(NetWork.host_num==-1){
					wsprintf(NetWork.SB.name[i], "%s", message2);
                        	}
			}
			else if(i==4){
				if(netsettingB_carsol[i]<MAP_NUM){
					wsprintf(message2 , "%s",MapData[netsettingB_carsol[i]].name);
				}
				else{
					wsprintf(message2 , "??RANDOM SELECT??");
				}
			}
			else if(i==5){
				wsprintf(message2 , "%d�{���", SAVE.MatchNum);
			}
			else if(i==6){
				wsprintf(message2 , "%d�b", 90+SAVE.MatchTime*30);
			}
			else if(i==7){
				char music[128];
				if(netsettingB_carsol[i]>=0&&settingC_carsol[2]>=0){
					wsprintf(music , "%s",BgmName[netsettingB_carsol[i]][settingC_carsol[2]]);
				}
				else if(netsettingB_carsol[i]>=0){
					wsprintf(music , "�����_���i�u%s�v����j",DirectoryName[netsettingB_carsol[i]]);
				}
				else{
					wsprintf(music , "�����_��");
				}
				DrawSt(x2,y,GetColor(255,255,255),0,font_default,music);
			}
			if(i<7)	DrawSt(x2,y,GetColor(255,255,255),0,font_default,message2);
		}
		char me[64];
		wsprintf(me , "�T�[�o:�F�X���߂Ă��傤����");
		int size = GetDrawStringWidthToHandle(me,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,me);
		size = GetDrawStringWidthToHandle(LOG,128,font_default);
		DrawSt(320-size/2,350,GetColor(255,150,255),0,font_default,LOG);
	}
	else{//�������N���C�A���g
		for(int i=7;i<8;i++){
			char message[64];
			char message2[64];
			for(int a=0;a<64;a++){
				message[a] = '\0';
				message2[a] = '\0';
			}
			float x = 150;
			float x2 = 250;
			float y = 230;
			if(netsettingB_seleca==i)	SetDrawBright(255,200,200);
			else				SetDrawBright(55,0,0);
			if(i==7)	wsprintf(message , "�a�f�l");
			DrawSt(x,y,GetColor(255,255,255),0,font_default,message);
			if(i==7){
				char music[128];
				if(netsettingB_carsol[i]>=0&&settingC_carsol[2]>=0){
					wsprintf(music , "%s",BgmName[netsettingB_carsol[i]][settingC_carsol[2]]);
				}
				else if(netsettingB_carsol[i]>=0){
					wsprintf(music , "�����_���i�u%s�v����j",DirectoryName[netsettingB_carsol[i]]);
				}
				else{
					wsprintf(music , "�����_��");
				}
				DrawSt(x2,y,GetColor(255,255,255),0,font_default,music);
			}
			if(i<7)	DrawSt(x2,y,GetColor(255,255,255),0,font_default,message2);
		}
		char me[64];
		wsprintf(me , "�N���C�A���g:�a�f�l��I��");
		int size = GetDrawStringWidthToHandle(me,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,me);
		size = GetDrawStringWidthToHandle(LOG,128,font_default);
		DrawSt(320-size/2,400,GetColor(255,150,255),0,font_default,LOG);
	}	

	static int bomb;
	static int spell;
	static int up;
	static int down;
	static int left;
	static int right;
	//���͏�����
	if(netsettingB_count==0){
		bomb = 2;
		spell = 2;
		up = 0;
		down = 0;
		left = 0;
		right = 0;
	}
	else{
		//���͏���
		if((NetWork.bChat==true&&SAVE.Key_Type[0]==DX_INPUT_KEY)||NetWork.SB.bSettingBEnd[0]==true){
			bomb = 0;
			spell = 0;
			up = 0;
			down = 0;
			left = 0;
			right = 0;
		}
		else{
			int check_num = -1;
			if(SAVE.Key_Type[0]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[0]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[0]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[0]==DX_INPUT_PAD4)	check_num = 3;
			else					check_num = -1;
			if(check_num>=0){
				if(c_pad[check_num][SAVE.Key_Bomb[0]]>0)	bomb ++;
				else	bomb = 0;
				if(c_pad[check_num][SAVE.Key_Spell[0]]>0)	spell++;
				else	spell = 0;
				if(c_pad[check_num][PAD_UP]>0)		up++;
				else	up = 0;
				if(c_pad[check_num][PAD_DOWN]>0)	down++;
				else	down = 0;
				if(c_pad[check_num][PAD_LEFT]>0)	left++;
				else	left = 0;
				if(c_pad[check_num][PAD_RIGHT]>0)	right++;
				else	right = 0;
			}
			else{
				if(c_key[KEY_INPUT_Z]>0)	bomb++;
				else	bomb = 0;
				if(c_key[KEY_INPUT_X]>0)	spell++;
				else	spell = 0;
				if(c_key[KEY_INPUT_UP]>0)	up++;
				else	up = 0;
				if(c_key[KEY_INPUT_DOWN]>0)	down++;
				else	down = 0;
				if(c_key[KEY_INPUT_LEFT]>0)	left++;
				else	left = 0;
				if(c_key[KEY_INPUT_RIGHT]>0)	right++;
				else	right = 0;
			}
		}

	        int netsettingB_num = 8;
		if(NetWork.host_num!=-1)	netsettingB_num = 1;
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			if(NetWork.host_num==-1){
				netsettingB_seleca++;
				netsettingB_seleca = netsettingB_seleca % netsettingB_num;
			}
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			if(NetWork.host_num==-1){
				netsettingB_seleca--;
				netsettingB_seleca = (netsettingB_seleca+netsettingB_num) % netsettingB_num;
			}
		}
		if(left==1||(left>=30&&left%10==0)){
			play_sound(1);
			if(netsettingB_seleca<4){
				if(netsettingB_carsol[netsettingB_seleca]>NetWork.NFD[0].connect_num+1){
					netsettingB_carsol[netsettingB_seleca]--;
				}
				else{
					for(int i=netsettingB_carsol[netsettingB_seleca]-1; i>=0; i--){
						bool flag = true;
						for(int j=0; j<NetWork.NFD[0].connect_num+1; j++){
							if(i!=j && netsettingB_carsol[i]==netsettingB_carsol[j]){
								flag = false;
								break;
							}
						}
						if(flag==true){
							netsettingB_carsol[netsettingB_seleca] = i;
							break;
						}
					}
				}
			}
			else if(netsettingB_seleca<7){
				if(netsettingB_carsol[netsettingB_seleca]>0)		netsettingB_carsol[netsettingB_seleca]--;
				if(netsettingB_seleca==5){
					SAVE.MatchNum = netsettingB_carsol[netsettingB_seleca];
				}
				else if(netsettingB_seleca==6){
					SAVE.MatchTime = netsettingB_carsol[netsettingB_seleca];
				}
			}
			else if(netsettingB_seleca==7){
				if(netsettingB_carsol[7]>=0&&netsettingB_carsol[8]==-1){
					netsettingB_carsol[7]--;
				}
				else if(netsettingB_carsol[8]==0){
					if(netsettingB_carsol[7]==0){
						netsettingB_carsol[7] = DIRECTORY_NUM-1;
						netsettingB_carsol[8] = -1;
					}
					else{
						netsettingB_carsol[7]--;
						netsettingB_carsol[8] = BGM_NUM[netsettingB_carsol[7]]-1;
					}
				}
				else if(netsettingB_carsol[7]>=0){
					netsettingB_carsol[8]--;
				}
			}
		}
		else if(right==1||(right>=30&&right%10==0)){
			play_sound(1);
			if(netsettingB_seleca<4){
				if(netsettingB_carsol[netsettingB_seleca]<NetWork.NFD[0].connect_num+4){
					netsettingB_carsol[netsettingB_seleca]++;
					if(netsettingB_carsol[netsettingB_seleca]<NetWork.NFD[0].connect_num+1){
						for(; netsettingB_carsol[netsettingB_seleca]<NetWork.NFD[0].connect_num+1; netsettingB_carsol[netsettingB_seleca]++){
							bool flag = true;
							for(int j=0; j<NetWork.NFD[0].connect_num+1; j++){
								if(netsettingB_seleca!=j && netsettingB_carsol[netsettingB_seleca]==netsettingB_carsol[j]){
									flag = false;
									break;
								}
							}
							if(flag==true)	break;
						}
					}
				}
			}
			else if(netsettingB_seleca==4){
				if(netsettingB_carsol[netsettingB_seleca]<MAP_NUM)		netsettingB_carsol[netsettingB_seleca]++;
			}
			else if(netsettingB_seleca==5){
				if(netsettingB_carsol[netsettingB_seleca]<5){
					netsettingB_carsol[netsettingB_seleca]++;
					SAVE.MatchNum = netsettingB_carsol[netsettingB_seleca];
				}
			}
			else if(netsettingB_seleca==6){
				if(netsettingB_carsol[netsettingB_seleca]<7){
					netsettingB_carsol[netsettingB_seleca]++;
					SAVE.MatchTime = netsettingB_carsol[netsettingB_seleca];
				}
			}
			else if(netsettingB_seleca==7){
				if(netsettingB_carsol[7]<DIRECTORY_NUM-1&&netsettingB_carsol[8]==-1){
					netsettingB_carsol[7]++;
				}
				else if(netsettingB_carsol[8]==-1){
					netsettingB_carsol[7] = 0;
					netsettingB_carsol[8] = 0;
				}
				else if(netsettingB_carsol[8]==BGM_NUM[netsettingB_carsol[7]]-1){
					if(netsettingB_carsol[7]<DIRECTORY_NUM-1){
						netsettingB_carsol[7]++;
						netsettingB_carsol[8] = 0;
					}
				}
				else if(netsettingB_carsol[7]<DIRECTORY_NUM&&netsettingB_carsol[8]<BGM_NUM[netsettingB_carsol[7]]-1){
					netsettingB_carsol[8]++;
				}
			}
		}
		if(bomb==1||netsettingB_count==3600){
			play_sound(0);
			wsprintf(LOG,"���v���C���[���ݒ蒆�B���΂炭���҂���������...");
			NetWork.SB.bSettingBEnd[0] = true;
			if(NetWork.host_num!=-1){
				IPDATA P;
				P.d1 = NetWork.NFD[NetWork.host_num+1].IP[0];
				P.d2 = NetWork.NFD[NetWork.host_num+1].IP[1];
				P.d3 = NetWork.NFD[NetWork.host_num+1].IP[2];
				P.d4 = NetWork.NFD[NetWork.host_num+1].IP[3];
				NetWorkSendUDP(NetWork.connect_udp, P, NetWork.hostport, &NetWork.SB.bSettingBEnd[0], sizeof(bool));
			}
		}
		else if(spell==1){
			play_sound(2);
			for(int i=0;i<MAX_CONNECT;i++){
				if(NetWork.GetConnectTcp(i)!=-1){
					CloseNetWork(NetWork.connect_tcp[i]);
					NetWork.NFD[0].connect_num--;
					NetWork.connect_tcp[i] = -1;
				}
			}
			DeleteUDPSocket(NetWork.connect_udp);
			NetWork.connect_udp = -1;
			change_scene(TITLE);
		}
		if(NetWork.SB.bSettingBEnd[0]==true){
			if(NetWork.host_num==-1)	NetWork.GetInputFlag();	
			else				NetWork.SendInputFlag();	
		}	
		if(NetWork.SB.bSettingBEnd[1]==true){
			for(int i=0;i<7;i++)	netsettingB_carsol[i] = NetWork.SB.settingB[i];
			if(NetWork.host_num==-1){
				for(int i=0;i<PLAYER_NUM;i++){
					if(i<NetWork.NFD[0].connect_num+1){
						for(int j=0;j<MAX_CONNECT+1;j++){
							if(j==netsettingB_carsol[i]){
								NetWork.NFD[j].player_num = i;
								if(j!=0){
									IPDATA P;
									P.d1 = NetWork.NFD[j].IP[0];
									P.d2 = NetWork.NFD[j].IP[1];
									P.d3 = NetWork.NFD[j].IP[2];
									P.d4 = NetWork.NFD[j].IP[3];
									NetWorkSendUDP(NetWork.connect_udp, P, NetWork.hostport, &NetWork.NFD[j], sizeof(NETFIRSTDATA));
								}
							}
						}
					}
				}
				
			}
			else{
				while(NetWorkRecvUDP(NetWork.connect_udp, NULL, NULL, &NetWork.NFD[0], sizeof(NETFIRSTDATA), FALSE)!=sizeof(NETFIRSTDATA)){}
			}
			/*
			NETGAMEDATA Input;
			NetWork.GetInput(&Input);
			rand_seed = Input.rand_seed;
			if(netsettingB_carsol[4]==MAP_NUM)	netsettingB_carsol[4] = get_rand(MAP_NUM-1);
			if(netsettingB_carsol[7]==-1)	netsettingB_carsol[7] = get_rand(DIRECTORY_NUM-1);
			if(netsettingB_carsol[8]==-1)	netsettingB_carsol[8] = get_rand(BGM_NUM[netsettingB_carsol[7]]-1);
			settingC_carsol[0] = netsettingB_carsol[4];
			settingC_carsol[1] = netsettingB_carsol[7];
			settingC_carsol[2] = netsettingB_carsol[8];
			*/
			play_sound(0);
			for(int i=0;i<4;i++){
				if(netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)	Player[i].bMan = true;
				else	Player[i].bMan = false;
			}
			change_scene(SETTINGB);
		}
	}

	SetDrawBright(255,255,255);
	netsettingB_count++;
	char buffer[2]={'0','0'};
	if((3600-netsettingB_count)/60+1>9){
		int base = (3600-netsettingB_count)/60+1;
		buffer[0] = base/10;
		buffer[1] = base-buffer[0]*10;
		buffer[0] += 48;
		buffer[1] += 48;
		draw_string(640-11*2,0,2,buffer);
	}
	else if((3600-netsettingB_count)/60+1>0){
		int base = (3600-netsettingB_count)/60+1;
		buffer[0] = base+48;
		draw_string(640-11,0,1,buffer);
	}
	else{
		draw_string(640-11,0,1,buffer);
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
		wsprintf(message , "���x���ύX�͂b�n�l��ō��E�L�[�B���֐i�ނɂ͌���L�[������");
		int size = GetDrawStringWidthToHandle(message,64,font_default);
		SetDrawBright(255,255,255);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);

		if(settingA_count!=30){	
			int bomb=0,spell=0,pause=0,up=0,down=0,left=0,right=0;
			int settingA_num = 4;
			for(int i=0;i<4;i++){
				int check_num = -1;
				if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
				else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
				if(check_num!=-1){
					bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
					spell += c_pad[check_num][SAVE.Key_Spell[i]];
					up += c_pad[check_num][PAD_UP];
					down += c_pad[check_num][PAD_DOWN];
					left += c_pad[check_num][PAD_LEFT];
					right += c_pad[check_num][PAD_RIGHT];
				}
			}
			bomb += c_key[KEY_INPUT_Z];
			bomb += c_key[KEY_INPUT_RETURN];
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
	if(settingB_count==0){
		if(bOnline==true){
			for(int i=0;i<PLAYER_NUM;i++){
				Player[i].chara = 0;
				Player[i].color = 0;
			}
		}
		while(1){
			bool flag = true;
			for(int j=0;j<4;j++){
				for(int a=0;a<4;a++){
					if(j!=a&&Player[j].chara==Player[a].chara&&Player[j].color==Player[a].color){
						Player[a].color = (Player[a].color+1)%4;
						flag = false;
					}
				}
			}
			if(flag==true)	break;
		}
	}
	for(int a=0;a<4;a++){
		if(Player[a].chara<PLAYER_GRAPH_NUM)	DrawRotaGraphF(15,50+100*a,1.0,0,gPlayer[Player[a].chara][Player[a].color][7],TRUE,FALSE);
	}
	for(int i=0;i<PLAYER_NUM;i++){
		char message[7][64];
		float x = 50;
		float y = 50 + 100*i;
		float x2 = 150;
		float y2 = y-20;
		float x3 = 220;
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
		if(Player[i].bMan==true){
			if(bOnline==true){
				wsprintf(message[0] , "%s",NetWork.NFD[netsettingB_carsol[i]].name);
			}
			else{
				if(SAVE.User[i]==-1)	wsprintf(message[0] , "�Q�X�g");
				else	wsprintf(message[0] , "%s",Profile[SAVE.User[i]].name);
			}
			SetDrawBright(255,150,150);
		}
		else				wsprintf(message[0] , "COM%d   ",i+1);
		DrawSt(x,y,GetColor(255,255,255),0,font_default,message[0]);
		SetDrawBright(255,255,255);
		if(Player[i].get_chara()<FACE_GRAPH_NUM){
			DrawGraph(x2,y2,gFace[Player[i].get_chara()],FALSE);
		}
		if(Player[i].get_chara()==REIMU){
			wsprintf(message[1] , "���� �얲");
			wsprintf(message[2] , "�ړ��X�s�[�h:�R  �Q�[�W�����x:�R");
			wsprintf(message[3] , "Lv1:�u���z����v");
			wsprintf(message[4] , "Lv2:�u���z����E�U�v");
			wsprintf(message[5] , "Lv3:�u���z����E�Łv");
			wsprintf(message[6] , "�����ǔ�����{�����R�ݒu����");
		}
		else if(Player[i].get_chara()==MARISA){
			wsprintf(message[1] , "���J ������");
			wsprintf(message[2] , "�ړ��X�s�[�h:�T�@�Q�[�W�����x:�R");
			wsprintf(message[3] , "Lv1:�u�}�X�^�[�X�p�[�N�v");
			wsprintf(message[4] , "Lv2:�u�A�T�V���X�p�[�N�v");
			wsprintf(message[5] , "Lv3:�u�t�@�C�i���X�p�[�N�v");
			wsprintf(message[6] , "�����̌����Ă�������ɋɑ����[�U�[�����");
		}
		else if(Player[i].get_chara()==SAKUYA){
			wsprintf(message[1] , "�\�Z�� ���");
			wsprintf(message[2] , "�ړ��X�s�[�h:�S�@�Q�[�W�����x:�O");
			wsprintf(message[3] , "Lv1:�u�W���b�N�E�U�E���b�p�[�v");
			wsprintf(message[4] , "Lv2:�u�W���b�N�E�U�E���h�r���v");
			wsprintf(message[5] , "Lv3:�u�E�l�h�[���v");
			wsprintf(message[6] , "��莞�ԁA���ȊO�̎��Ԃ��~�܂�");
		}
		else if(Player[i].get_chara()==REMILIA){
			wsprintf(message[1] , "���~���A�E�X�J�[���b�g");
			wsprintf(message[2] , "�ړ��X�s�[�h:�R�@�Q�[�W�����x:�Q");
			wsprintf(message[3] , "Lv1:�u�S���E�i�C�g���A�v");
			wsprintf(message[4] , "Lv2:�u�~�b�h�i�C�g�f�B�U�X�^�[�v");
			wsprintf(message[5] , "Lv3:�u���~���A�X�g�[�J�[�v");
			wsprintf(message[6] , "��莞�ԁA���E���g���Ȃ�");
		}
		else if(Player[i].get_chara()==FRANDRE){
			wsprintf(message[1] , "�t�����h�[���E�X�J�[���b�g");
			wsprintf(message[2] , "�ړ��X�s�[�h:�S�@�Q�[�W�����x:�R");
			wsprintf(message[3] , "Lv1:�u�����ĒN�����Ȃ��Ȃ邩�H�v");
			wsprintf(message[4] , "Lv2:�u�����ĒN���ނ����ʂ��悢�v");
			wsprintf(message[5] , "Lv3:�u�S�X�T�N�̔g��v");
			wsprintf(message[6] , "�{�����ő�Η͂ŁA�S�Ĕ���������");
		}
		else if(Player[i].get_chara()==YOUMU){
			wsprintf(message[1] , "��� �d��");
			wsprintf(message[2] , "�ړ��X�s�[�h:�T�@�Q�[�W�����x:�P");
			wsprintf(message[3] , "Lv1:�u�d����S�̒f�H�v");
			wsprintf(message[4] , "Lv2:�u��S�R�{�̈�M�v");
			wsprintf(message[5] , "Lv3:�u�ƕ��_�M�a�v");
			wsprintf(message[6] , "�꒼�����a��A���̋O����ɔ��e��ݒu����");
		}
		else if(Player[i].get_chara()==YUYUKO){
			wsprintf(message[1] , "���s�� �H�X�q");
			wsprintf(message[2] , "�ړ��X�s�[�h:�S�@�Q�[�W�����x:�P");
			wsprintf(message[3] , "Lv1:�u�S�䋽�v");
			wsprintf(message[4] , "Lv2:�u���S�Ȃ�n���̍��v");
			wsprintf(message[5] , "Lv3:�u�������v");
			wsprintf(message[6] , "���̂Ƃ̔���������BLv3���c��1���Ŕ�������ƥ��");
		}
		else if(Player[i].get_chara()==YUKARI){
			wsprintf(message[1] , "���_ ��");
			wsprintf(message[2] , "�ړ��X�s�[�h:�S�@�Q�[�W�����x:�P");
			wsprintf(message[3] , "Lv1:�u���ƐÂ̋ύt�v");
			wsprintf(message[4] , "Lv2:�u���ƌ��̋��E�v");
			wsprintf(message[5] , "Lv3:�u���r�E�X�̕\���v");
			wsprintf(message[6] , "����r�炵�A�l�X�ȍ����������N����");
		}
		else if(Player[i].get_chara()==REISEN){
			wsprintf(message[1] , "���E�D�܉؉@�E�C�i�o");
			wsprintf(message[2] , "�ړ��X�s�[�h:�T�@�Q�[�W�����x:�Q");
			wsprintf(message[3] , "Lv1:�u���z�Ö��i�C���r�V�u���E�H�[���j�v");
			wsprintf(message[4] , "Lv2:�u���e�̕ǁi�C�����[�W�����E�H�[���j�v");
			wsprintf(message[5] , "Lv3:�u���e���a�i���i�t�@���g���j�v");
			wsprintf(message[6] , "��̔g���𑀂�A���o�𔭐�������");
		}
		else if(Player[i].get_chara()==NITORI){
			wsprintf(message[1] , "�͏� �ɂƂ�");
			wsprintf(message[2] , "�ړ��X�s�[�h:�S�@�Q�[�W�����x:�Q");
			wsprintf(message[3] , "Lv1:�u�X�s���E�U�E�{���o�[�v");
			wsprintf(message[4] , "Lv2:�u�I�v�e�B�J���J���t���[�W���v");
			wsprintf(message[5] , "Lv3:�u�̂с[��A�[���v");
			wsprintf(message[6] , "���w���ʁE�@�B�Ȃǋߑ�I�ȕ�����g�p����");
		}
		else if(Player[i].get_chara()==SANAE){
			wsprintf(message[1] , "�����J ���c");
			wsprintf(message[2] , "�ړ��X�s�[�h:�R�@�Q�[�W�����x:�T");
			wsprintf(message[3] , "Lv1:�u�V�̌b�݁v");
			wsprintf(message[4] , "Lv2:�u�T�����^�P�~�i�J�^�v");
			wsprintf(message[5] , "Lv3:�u�~���N���t���[�c�v");
			wsprintf(message[6] , "��q���`�̔\�͂ɂ���Ċ�Ղ��N����");
		}
		else if(Player[i].get_chara()==UTUHO){
			wsprintf(message[1] , "��G�H ��");
			wsprintf(message[2] , "�ړ��X�s�[�h:�Q�@�Q�[�W�����x:�S");
			wsprintf(message[3] , "Lv1:�u�d���f�Z���v");
			wsprintf(message[4] , "Lv2:�u�M�K�t���A�v");
			wsprintf(message[5] , "Lv3:�u�A�g�~�b�N�{���v");
			wsprintf(message[6] , "�j�Z���ɂ���Đ��ȗ͂������o��");
		}
		else{
			wsprintf(message[1] , "�����_���Z���N�g");
			wsprintf(message[2] , "�ړ��X�s�[�h:�H�@�Q�[�W�����x:�H");
			wsprintf(message[3] , "Lv1:�u�H�H�H�H�v");
			wsprintf(message[4] , "Lv2:�u�H�H�H�H�v");
			wsprintf(message[5] , "Lv3:�u�H�H�H�H�v");
			wsprintf(message[6] , "�H�H�H�H�H�H�H�H�H");
		}
		for(int a=0;a<6;a++){
			int color = GetColor(255,255,255);
			if(a==0)	color = GetColor(255,200,200);
			DrawSt(x3,y3+15*a,color,0,font_default,message[a+1]);
		}
	}

	NETGAMEDATA Input;
	if(bOnline==true){
		NetWork.GetInput(&Input);
	}
	for(int i=0;i<4&&settingB_count!=0;i++){
		int bomb=0,spell=0,pause=0,up=0,down=0,left=0,right=0;
		int settingB_num = FACE_GRAPH_NUM+1;
		if(bOnline==true){
			if(Input.input[i]&1)	bomb ++;
			else			bomb = 0;
			if(Input.input[i]&2)	spell ++;
			else			spell = 0;
			if(Input.input[i]&4)	pause ++;
			else			pause = 0;
			if(Input.input[i]&8)	up ++;
			else			up = 0;
			if(Input.input[i]&16)	down ++;
			else			down = 0;
			if(Input.input[i]&32)	left ++;
			else			left = 0;
			if(Input.input[i]&64)	right ++;
			else			right = 0;
		}
		else{
			int check_num = -1;
			if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
			if(check_num!=-1){
				bomb = c_pad[check_num][SAVE.Key_Bomb[i]];
				spell = c_pad[check_num][SAVE.Key_Spell[i]];
				pause = c_pad[check_num][SAVE.Key_Pause[i]];
				up = c_pad[check_num][PAD_UP];
				down = c_pad[check_num][PAD_DOWN];
				left = c_pad[check_num][PAD_LEFT];
				right = c_pad[check_num][PAD_RIGHT];
			}
			else{
				bomb += c_key[KEY_INPUT_Z];
				bomb += c_key[KEY_INPUT_RETURN];
				spell = c_key[KEY_INPUT_X];
				pause = c_key[KEY_INPUT_ESCAPE];
				up = c_key[KEY_INPUT_UP];
				down = c_key[KEY_INPUT_DOWN];
				left = c_key[KEY_INPUT_LEFT];
				right = c_key[KEY_INPUT_RIGHT];
			}
		}
		if(settingB_carsol[i]>=0){
			if(left==1||(left>=30&&left%10==0)){
				play_sound(1);
				Player[settingB_carsol[i]].chara--;
				Player[settingB_carsol[i]].chara = (Player[settingB_carsol[i]].chara+settingB_num) % settingB_num;
				Player[settingB_carsol[i]].color = 0;
			}
			if(right==1||(right>=30&&right%10==0)){
				play_sound(1);
				Player[settingB_carsol[i]].chara++;
				Player[settingB_carsol[i]].chara = Player[settingB_carsol[i]].chara % settingB_num;
				Player[settingB_carsol[i]].color = 0;
			}
			if(up==1||(up>=30&&up%10==0)){
				play_sound(1);
				while(1){
					bool flag = true;
					Player[settingB_carsol[i]].color--;
					Player[settingB_carsol[i]].color = (Player[settingB_carsol[i]].color+4) % 4;
					for(int a=0;a<4;a++){
						if(settingB_carsol[i]!=a&&Player[settingB_carsol[i]].chara==Player[a].chara&&Player[settingB_carsol[i]].color==Player[a].color){
							flag = false;
						}
					}
					if(flag==true)	break;
				}
			}
			if(down==1||(down>=30&&down%10==0)){
				play_sound(1);
				Player[settingB_carsol[i]].color++;
				Player[settingB_carsol[i]].color = Player[settingB_carsol[i]].color % 4;
				while(1){
					bool flag = true;
					for(int a=0;a<4;a++){
						if(settingB_carsol[i]!=a&&Player[settingB_carsol[i]].chara==Player[a].chara&&Player[settingB_carsol[i]].color==Player[a].color){
							flag = false;
							Player[settingB_carsol[i]].color++;
							Player[settingB_carsol[i]].color = Player[settingB_carsol[i]].color % 4;
						}
					}
					if(flag==true)	break;
				}
			}
			if(bomb==1||pause==1||(bOnline==true&&settingB_count>=3600)){
				if(pause==1)	Player[settingB_carsol[i]].chara = settingB_num - 1;
				play_sound(0);
				if(Player[settingB_carsol[i]].chara==FACE_GRAPH_NUM){
					Player[settingB_carsol[i]].chara = get_rand(FACE_GRAPH_NUM-1);
					Player[settingB_carsol[i]].color = 0;
				}
				while(1){
					bool flag = true;
					for(int a=0;a<4;a++){
						if(settingB_carsol[i]!=a&&Player[settingB_carsol[i]].chara==Player[a].chara&&Player[settingB_carsol[i]].color==Player[a].color){
							flag = false;
							Player[settingB_carsol[i]].color++;
							Player[settingB_carsol[i]].color = Player[settingB_carsol[i]].color % 4;
						}
					}
					if(flag==true)	break;
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
					if(bOnline==true){
						settingC_count2 = 1;
						stop_bgm();
					}
					else{
						change_scene(SETTINGC);
					}
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
	wsprintf(message , "���E:�L�����I�� �㉺:�J���[�I�� �|�[�Y:�����_��");
	int size = GetDrawStringWidthToHandle(message,64,font_default);
	SetDrawBright(255,255,255);
	DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message);
	SetDrawBright(255,255,255);
	settingB_count++;

	if(bOnline==true){
		char buffer[2]={'0','0'};
		if((3600-settingB_count)/60+1>9){
			int base = (3600-settingB_count)/60+1;
			buffer[0] = base/10;
			buffer[1] = base-buffer[0]*10;
			buffer[0] += 48;
			buffer[1] += 48;
			draw_string(640-11*2,0,2,buffer);
		}
		else if((3600-settingB_count)/60+1>0){
			int base = (3600-settingB_count)/60+1;
			buffer[0] = base+48;
			draw_string(640-11,0,1,buffer);
		}
		else{
			draw_string(640-11,0,1,buffer);
		}

		if(settingC_count2>0){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*settingC_count2);
			DrawBox(0,0,640,480,0,TRUE);
			if(settingC_count2==50){
				SReplay.rand_seed = rand_seed;
				GameLoad();
				replay_play = false;
				change_scene(GAME);
			}
			settingC_count2++;
		}
	}	
	
	return;
}

void MeSettingC(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	DrawBox(0,0,640,480,0,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	for(int a=0;a<4;a++){
		if(Player[a].chara<PLAYER_GRAPH_NUM)	DrawRotaGraphF(170+75*a,150,1.0,0,gPlayer[Player[a].chara][Player[a].color][7],TRUE,FALSE);
	}
	char message[3][64];
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
	//DrawSt(x3,y3+15*a,color,0,font_default,message[a+1]);
	char music[128];
	if(settingC_carsol[1]>=0&&settingC_carsol[2]>=0){
		wsprintf(music , "%s",BgmName[settingC_carsol[1]][settingC_carsol[2]]);
		SetDrawBright(255,255,255);
	}
	else if(settingC_carsol[1]>=0){
		wsprintf(music , "�����_���i�u%s�v����j",DirectoryName[settingC_carsol[1]]);
		SetDrawBright(255,255,200);
	}
	else{
		wsprintf(music , "�����_��");
		SetDrawBright(255,255,200);
	}
	DrawSt(200,y,GetColor(255,255,255),0,font_default,music);

	if(settingC_count!=0&&settingC_count2==0){	
		int bomb=0,spell=0,up=0,down=0,left=0,right=0;
		int settingC_num[2] = {MAP_NUM+1,DUMMY};
		for(int i=0;i<4;i++){
			int check_num = -1;
			if(SAVE.Key_Type[i]==DX_INPUT_PAD1)		check_num = 0;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD2)	check_num = 1;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD3)	check_num = 2;
			else if(SAVE.Key_Type[i]==DX_INPUT_PAD4)	check_num = 3;
			if(check_num!=-1){
				bomb += c_pad[check_num][SAVE.Key_Bomb[i]];
				spell += c_pad[check_num][SAVE.Key_Spell[i]];
				up += c_pad[check_num][PAD_UP];
				down += c_pad[check_num][PAD_DOWN];
				left += c_pad[check_num][PAD_LEFT];
				right += c_pad[check_num][PAD_RIGHT];
			}
		}
		bomb += c_key[KEY_INPUT_Z];
		bomb += c_key[KEY_INPUT_RETURN];
		spell += c_key[KEY_INPUT_X];
		up += c_key[KEY_INPUT_UP];
		down += c_key[KEY_INPUT_DOWN];
		left += c_key[KEY_INPUT_LEFT];
		right += c_key[KEY_INPUT_RIGHT];
		
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			if(settingC_carsol[1]<DIRECTORY_NUM-1&&settingC_carsol[2]==-1){
				settingC_carsol[1]++;
			}
			else if(settingC_carsol[2]==-1){
				settingC_carsol[1] = 0;
				settingC_carsol[2] = 0;
			}
			else if(settingC_carsol[2]==BGM_NUM[settingC_carsol[1]]-1){
				if(settingC_carsol[1]<DIRECTORY_NUM-1){
					settingC_carsol[1]++;
					settingC_carsol[2] = 0;
				}
			}
			else if(settingC_carsol[1]<DIRECTORY_NUM&&settingC_carsol[2]<BGM_NUM[settingC_carsol[1]]-1){
				settingC_carsol[2]++;
			}
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			if(settingC_carsol[1]>=0&&settingC_carsol[2]==-1){
				settingC_carsol[1]--;
			}
			else if(settingC_carsol[2]==0){
				if(settingC_carsol[1]==0){
					settingC_carsol[1] = DIRECTORY_NUM-1;
					settingC_carsol[2] = -1;
				}
				else{
					settingC_carsol[1]--;
					settingC_carsol[2] = BGM_NUM[settingC_carsol[1]]-1;
				}
			}
			else if(settingC_carsol[1]>=0){
				settingC_carsol[2]--;
			}
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
	wsprintf(me , "���E:�X�e�[�W �㉺:�a�f�l�@��I������");
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
			if(settingC_carsol[1]==-1)	settingC_carsol[1] = get_rand(DIRECTORY_NUM-1);
			if(settingC_carsol[2]==-1)	settingC_carsol[2] = get_rand(BGM_NUM[settingC_carsol[1]]-1);
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
	if(p==0){//���j���[�̔�����
		if(c==0){
			(*it).speed = 0.5+0.1*get_rand(15);
			(*it).f_hanyou[0] = 0.1;
			(*it).large = 0.1*(1+get_rand(9));
			(*it).move_x = cos(Radian(get_rand(360),TRUE));
			(*it).move_y = -1;
			(*it).bBlend = false;
			(*it).red = 255;
			(*it).green = 255;
			(*it).blue = 255;
			(*it).i_hanyou[0] = get_rand(360);
		}
		if(menu_count<120){
			(*it).flash = 0;
		}
		else if(menu_count<180){
			(*it).flash = 2.125*(menu_count-120);
		}
		else if(c<60){
			(*it).flash = 2.1 * c;
		}
		else{
			(*it).flash = 127;
		}
		(*it).move_x = cos(Radian(1.5*((*it).count+(*it).i_hanyou[0]),TRUE));
		(*it).red = 100*sin(Radian(c/6,TRUE));
		(*it).green = 100*sin(Radian(2*c/6,TRUE));
		(*it).blue = 255*sin(Radian(3*c/6,TRUE));
		if((*it).x<-60||(*it).y<-60||(*it).x>700||(*it).y>540){
			(*it).bDelete = true;
			MeEfMake(get_rand(640),500,0,0);
		}
	}


	(*it).x += (*it).move_x * (*it).speed;
	(*it).y += (*it).move_y * (*it).speed;
	(*it).count++;
	
        return;
}