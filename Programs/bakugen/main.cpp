//------------------------------------------------------------------------------
//
//	爆！幻想郷	10.03.14~10.03.23
//                       
//------------------------------------------------------------------------------

#include "DxLib.h"
#include "extern.h"
#include "graph.h"
#include "para.h"
#include "map.h"
#include "player.h"
#include "bomb.h"
#include "item.h"
#include "spell.h"
#include "stg.h"
#include "menu.h"


void MainGame();
void Result();
void Pause();

void starts(){
//起動時のフルスクリーンモード変更
        int flag;
        flag=MessageBox(
                NULL ,
                TEXT("フルスクリーンモードで起動しますか？") ,
                TEXT("爆！幻想郷") , 
                MB_YESNO | MB_ICONQUESTION );
        if(flag==IDNO)
                ChangeWindowMode( TRUE );
	return;
}

void GameLoad(){
	Map.type = settingC_carsol[0];
	ILoad();
	PLoad();
	MLoad();
	BLoad();
	SpLoad();
	StLoad();
	EfLoad();

	play_bgm(settingC_carsol[1]);
	float x[4],y[4];
	bool flag[4]={false,false,false,false};
	x[0] = (X_NUM_TO_ZAHYO(2)+X_NUM_TO_ZAHYO(1))/2.0;
	y[0] = (Y_NUM_TO_ZAHYO(2)+Y_NUM_TO_ZAHYO(1))/2.0-3;
	x[1] = (X_NUM_TO_ZAHYO(18)+X_NUM_TO_ZAHYO(17))/2.0;
	y[1] = (Y_NUM_TO_ZAHYO(12)+Y_NUM_TO_ZAHYO(11))/2.0-3;
	x[2] = (X_NUM_TO_ZAHYO(2)+X_NUM_TO_ZAHYO(1))/2.0;
	y[2] = (Y_NUM_TO_ZAHYO(12)+Y_NUM_TO_ZAHYO(11))/2.0-3;
	x[3] = (X_NUM_TO_ZAHYO(18)+X_NUM_TO_ZAHYO(17))/2.0;
	y[3] = (Y_NUM_TO_ZAHYO(2)+Y_NUM_TO_ZAHYO(1))/2.0-3;
	for(int i=0;i<4;i++){
		int rand;
		while(1){
			rand = get_rand(4);
			if(flag[rand]==false){
				flag[rand] = true;
				break;
			}
		}
		Player[i].make(x[rand],y[rand],Player[i].chara,Player[i].bMan);
	}	
	bTimeStop = false;
	bSecondSun = false;
	Para.time_count = (90+30*SAVE.MatchTime)*60;
	//Para.time_count = 3601;
	Para.start_count = 240;
	Gcount = 0;
	Rcount = 0;
	Rcount2 = 0;
	Pcount = 0;

	return;
}

void Load(){
	SLoad();
	MuLoad();
	GLoad();
	MeLoad();
	GameLoad();
	for(int i=0;i<4;i++){
		Player[i].bMan = true;
		Player[i].level = 1;
	}
	play_bgm(0);
	scene = TITLE;
	replay_play = false;
	replay_play_num = 0;
	
	return;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
        SetWindowText("爆！幻想郷　ver1.00a");        
	SetWindowIconID(101);
	starts();
        //ChangeWindowMode( TRUE );
        if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//初期化と裏画面化
        Load();

	do{
		ClearDrawScreen();
		CheckPushKey();
		
		switch(scene){
			case GAME:	if(Pcount>0)	Pause();
					else if(Rcount==0&&Para.time_count>0)	MainGame();
					else		Result();
					break;
			case TITLE:	MeMain();	break;
			case SELECT_REPLAY:	MeMain();	break;
			case OPTION:	MeMain();	break;
			case SETTINGA:	MeMain();	break;
			case SETTINGB:	MeMain();	break;
			case SETTINGC:	MeMain();	break;
		}
		
		//PlaySound();
		Fps();
		SnapShot();
		SCheckPlayTime();
		ScreenFlip();
	}while(scene!=END&&ProcessMessage()==0&&!(c_key[KEY_INPUT_F4]>0&&(c_key[KEY_INPUT_LALT]>0||c_key[KEY_INPUT_RALT]>0)));

	SSave();
        DxLib_End();
        return 0 ;              // ソフトの終了
}

void MainGame(){
	repeat_max = 10;
	repeat = 9;
	if(Gcount<169&&replay_play==true&&(c_key[KEY_INPUT_LCONTROL]>0||c_key[KEY_INPUT_RCONTROL]>0)){
		repeat = 0;
	}
	for(;repeat<repeat_max;repeat++){
	MDraw();
	EDraw();
	BDraw();
	IDraw();
	BEfDraw();
	PMain();
	StMain();
	SpDraw();
	EfDraw();
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()==0){
			if(Para.start_count==0)	Player[i].control();
		}
		else if(Player[i].get_condition()==2){
			if(Para.start_count==0)	Player[i].miso_control();
		}
		Player[i].replay_main();
	}
	replay_count++;
	SReplay.element_num++;
	for(list<SHOTDATA>::iterator it=Shot.begin();it!=Shot.end();++it){
		for(int i=0;i<PLAYER_NUM;i++){
			if(Player[i].get_condition()==0&&bTimeStop==false){
				float px,py;
				Player[i].get_xy(&px,&py);
				float sx = px - (*it).x;
				float sy = py - (*it).y;
				if(sqrt(sx*sx+sy*sy)<(*it).atari){
					Player[i].change_condition(1);
					it = Shot.erase(it);
					it--;
					continue;			
				}
			}
		}
	}
	if(bTimeStop==true){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
		DrawBox(0,0,640,480,GetColor(100,100,100),TRUE);
		for(int i=0;i<PLAYER_NUM;i++){
			if(Player[i].get_condition()==0&&Player[i].get_chara()==SAKUYA){
				Player[i].draw();
			}
		}
	}
	if(Para.time_count==3600){
		play_sound(9);
		for(int i=0;i<PLAYER_NUM;i++){
			if(Player[i].get_condition()==2||Player[i].get_condition()==1)	Player[i].change_condition(4);
			Player[i].bomb_num = 0;
		}
		Bomb.clear();
		Item.clear();
		Exp.clear();
		Effect.clear();
		BackEffect.clear();
		bSecondSun = false;
		for(int i=1;i<LARGE_X-1;i++){
			for(int a=1;a<LARGE_Y-1;a++){
				Map.field[i][a] = 0;
			}
		}
		EnMake();
	}
	if(3540<Para.time_count&&Para.time_count<=3600){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Para.time_count-3540));
		DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
	}
	ParaMain();
	if(Para.start_count>180){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*(Para.start_count-180));
		DrawBox(0,0,640,480,0,TRUE);
	}
	if(Para.start_count>0){
		Para.start_count--;
		int num = 0;
		int flash = 0;
		float large;
		if(150<Para.start_count&&Para.start_count<210){
			num = 3;
			if(180<Para.start_count){
				flash = 255-8.5*(Para.start_count%60);
				large = 4.0 + 0.4*(float)(Para.start_count%60);
			}
			else{
				flash = 255;
				large = 4.0;
			}
		}
		else if(90<Para.start_count){
			num = 2;
			if(120<Para.start_count){
				flash = 255-8.5*(Para.start_count%60);
				large = 4.0 + 0.4*(float)(Para.start_count%60);
			}
			else{
				flash = 255;
				large = 4.0;
			}
		}
		else if(30<Para.start_count){
			num = 1;
			if(60<Para.start_count){
				flash = 255-8.5*(Para.start_count%60);
				large = 4.0 + 0.4*(float)(Para.start_count%60);
			}
			else{
				flash = 255;
				large = 4.0;
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,flash);
		DrawRotaGraphF(320,240,large,0,gNumber[num],TRUE,FALSE);
		if(Para.start_count%60==0){
			if(Para.start_count<=60)	play_sound(8);
			else				play_sound(7);
		}
		if(Para.start_count<180){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			for(int i=0;i<4;i++){
				char message[7];
				if(Player[i].bMan==true)	wsprintf(message , "PLAYER%d",i+1);
				else				wsprintf(message , "COM%d   ",i+1);
				float x,y;
				Player[i].get_xy(&x,&y);
				x -= 38;
				y += 30;
				draw_string(x,y,7,message);
			}
		}
	}
	int living = 0;
	bool wait_flag = false;
	for(int i=0;i<PLAYER_NUM;i++){
		if(Player[i].get_condition()==0)	living ++;
		else if(Player[i].get_condition()==1||Player[i].get_condition()==3)	wait_flag = true;
	}
	if(Para.time_count==1){
		for(int i=0;i<PLAYER_NUM;i++){
			if(Player[i].get_condition()==0)	Player[i].victory++;
		}
		Rcount = 1;
		Gcount = 0;
		GetDrawScreenGraph(0,0,640,480,gSnap);
	}
	else if(living<=1&&wait_flag==false){
		Gcount++;
		if(Gcount==180){
			for(int i=0;i<PLAYER_NUM;i++){
				if(Player[i].get_condition()==0)	Player[i].victory++;
			}
			Rcount = 1;
			Gcount = 0;
			GetDrawScreenGraph(0,0,640,480,gSnap);
		}
	}
	else{
		Gcount = 0;
	}
	}

	int pause=0;
	for(int i=0;i<4;i++){
		pause += c_pad[i][SAVE.Key_Pause[i]];
	}
	pause += c_key[KEY_INPUT_ESCAPE];
	if(pause==1){
		play_sound(16);
		Pcount = 1;
		GetDrawScreenGraph(0,0,640,480,gSnap); 
	}	

	return;
}

void Result(){
	static int save_num=0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	DrawGraph(0,0,gSnap,FALSE);
	if(Rcount<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		float x = 11*Rcount;
		float y = 8*Rcount;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,0,TRUE);
		bool flag = false;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<PLAYER_NUM;i++){
			char message[64];
			float x = 200;
			float y = 200 + 50*i;
			if(Player[i].bMan==true)	wsprintf(message , "Player%d",i+1);
			else				wsprintf(message , "COM%d   ",i+1);
			draw_string(x,y,7,message);
			for(int a=0;a<Player[i].victory;a++){
				int color = GetColor(255,255,200);
				if(Player[i].get_condition()==0&&a==Player[i].victory-1)	color = GetColor(255,100,100);
				DrawSt(x+100+15*a,y,color,0,font_default,"★");
				if(Player[i].victory==SAVE.MatchNum){
					DrawSt(x-50,y,GetColor(255,200,200),0,font_default,"勝者！");
					flag = true;
				}
			}
		}
		if(Rcount<150){}
		else if(Rcount<210){
			if(Rcount==150&&flag==true){
				stop_bgm();
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,150+1.75*(Rcount-150));
			DrawBox(0,0,640,480,0,TRUE);
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			DrawBox(0,0,640,480,0,TRUE);
			if(flag==true){
				if(Rcount2==0){
					DATEDATA D;
					GetDateTime(&D);
					SReplay.hour[1] = D.Hour;
					SReplay.minute[1] = D.Min;
					SReplay.second[1] = D.Sec;
					//リプレイ保存しますか？
					save_num = 0;
					if(replay_play==true){
						change_scene(TITLE);
						DeleteGraph(gSnap);	
						gSnap = MakeGraph(640,480);	
					}
					else{
						Rcount2 = 1;
						Rcount--;
					}			
				}
			}
			else{
				GameLoad();
				Rcount = -1;
				SReplay.match++;
				DeleteGraph(gSnap);	
				gSnap = MakeGraph(640,480);
			}
		}
	}
	if(Rcount2>0){
		char message[4][64];
		wsprintf(message[0] , "Save Your Replay");
		int size = GetDrawStringWidthToHandle(message[0],64,font_default);
		DrawSt(320-size/2,200,GetColor(255,255,150),0,font_default,message[0]);

		wsprintf(message[1] , "No.%2d",save_num+1);
		size = GetDrawStringWidthToHandle(message[1],64,font_default);
		DrawSt(320-size/2,250,GetColor(255,255,255),0,font_default,message[1]);
		if(Replay[save_num].exist==true){
			wsprintf(message[2] , "※既にリプレイが存在します");
			size = GetDrawStringWidthToHandle(message[2],64,font_default);
			DrawSt(320-size/2,270,GetColor(255,100,100),0,font_default,message[2]);
		}	

		wsprintf(message[3] , "上下キーで保存番号選択、キャンセルキーで終了");
		size = GetDrawStringWidthToHandle(message[3],64,font_default);
		DrawSt(320-size/2,440,GetColor(150,150,255),0,font_default,message[3]);
		
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
			save_num++;
			save_num = save_num % select_replay_num;
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			save_num--;
			save_num = (save_num+select_replay_num) % select_replay_num;
		}
		if(bomb==1){
			play_sound(15);
			Replay[save_num] = SReplay;
			int Element = Replay[save_num].element_num;
			crypt(&Replay[save_num],sizeof(REPLAYDATA),0xF7);
			char name[64];
			wsprintf(name , "replay");
			if(PathIsDirectory(name)==false){
				CreateDirectory(name,NULL);
			}
			wsprintf(name , "replay/baku_%02d.rpy",save_num+1);
			FILE *fp;
			if((fp=fopen(name,"wb")) == NULL){
				char message[128];
				wsprintf(message , "Warning!\nリプレイの保存に失敗");
				MessageBox( 	NULL,
					message,
					"Error",
					MB_OK | 
					MB_ICONSTOP |
					MB_TOPMOST);
				return;
			}	
			fwrite(&Replay[save_num],sizeof(REPLAYDATA)-4*REPLAY_ELEMENT_NUM,1,fp);
			for(int i=0;i<Element;i++){
				for(int a=0;a<4;a++){
					fputc(Replay[save_num].replay_element[i][a],fp);
				}
			}
			fclose(fp);
			crypt(&Replay[save_num],sizeof(REPLAYDATA),0xF7);
			Rcount2 = 2;
		}
		else if(spell==1){
			play_sound(2);
			change_scene(TITLE);
		}

		if(Rcount2==2){
			change_scene(TITLE);
			DeleteGraph(gSnap);	
			gSnap = MakeGraph(640,480);	
		}		
	}

	Rcount++;	
	return;
}

void Pause(){
	static int carsol = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	DrawGraph(0,0,gSnap,FALSE);
	if(Pcount<30){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		float x = 11*Pcount;
		float y = 8*Pcount;
		DrawBox(320-x,240-y,320+x,240+y,0,TRUE);
		carsol = 0;
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,150);
		DrawBox(0,0,640,480,0,TRUE);
		bool flag = false;
		char message[64];
		float x = 200;
		float y = 100;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		/*
		SetDrawBright(255,255,200);
		char me[] = "PAUSE";
		draw_string(x,y,5,me);
		*/
		SetDrawBright(255,255,255);
		for(int i=0;i<2;i++){
			if(carsol==i)	SetDrawBright(255,255,255);
			else		SetDrawBright(100,100,100);
			x = 200;
			y = 200 + 40*i;
			if(i==0)	wsprintf(message , "ゲームを再開する");
			else		wsprintf(message , "タイトルに戻る");
			DrawSt(x,y,GetColor(255,255,255),0,font_default,message);
		}
		int bomb=0,spell=0,up=0,down=0,left=0,right=0,pause=0;
		int carsol_num = 2;
		for(int i=0;i<4;i++){
			bomb += c_pad[i][SAVE.Key_Bomb[i]];
			spell += c_pad[i][SAVE.Key_Spell[i]];
			up += c_pad[i][PAD_UP];
			down += c_pad[i][PAD_DOWN];
			left += c_pad[i][PAD_LEFT];
			right += c_pad[i][PAD_RIGHT];
			pause += c_pad[i][SAVE.Key_Pause[i]];
		}
		bomb += c_key[KEY_INPUT_Z];
		spell += c_key[KEY_INPUT_X];
		up += c_key[KEY_INPUT_UP];
		down += c_key[KEY_INPUT_DOWN];
		left += c_key[KEY_INPUT_LEFT];
		right += c_key[KEY_INPUT_RIGHT];
		pause += c_key[KEY_INPUT_ESCAPE];
		
		if(down==1||(down>=30&&down%10==0)){
			play_sound(1);
			carsol++;
			carsol = carsol % carsol_num;
		}
		else if(up==1||(up>=30&&up%10==0)){
			play_sound(1);
			carsol--;
			carsol = (carsol+carsol_num) % carsol_num;
		}
		if(bomb==1){
			play_sound(0);
			if(carsol==1){
				stop_bgm();
				change_scene(TITLE);
			}
			else		Pcount = -1;
		}
		if(spell==1 || pause==1){
			Pcount = -1;
		}
	}
	if(Pcount==-1){
		DeleteGraph(gSnap);	
		gSnap = MakeGraph(640,480);
	}
	SetDrawBright(255,255,255);
        Pcount++;	
	return;
}