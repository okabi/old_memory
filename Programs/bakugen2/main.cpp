//------------------------------------------------------------------------------
//
//	爆！幻想郷Ⅱ	10.07.20~
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
#include "net.h"


void MainGame();
void Result();
void Pause();
void Debug();

void starts(){
//起動時のフルスクリーンモード変更
        int flag;
        flag=MessageBox(
                NULL ,
                TEXT("フルスクリーンモードで起動しますか？") ,
                TEXT("爆！幻想郷Ⅱ") , 
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

	if(scene!=TITLE)	play_bgm(settingC_carsol[1],settingC_carsol[2]);
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
	for(int i=0;i<ILLUSION_NUM;i++){
		Illusion[i].player_num = -1;
		Illusion[i].bIllusion = true;
	}
	for(int i=0;i<4;i++){
		int rand;
		while(1){
			rand = get_rand(4);
			if(flag[rand]==false){
				flag[rand] = true;
				break;
			}
		}
		Player[i].make(x[rand],y[rand],Player[i].chara,Player[i].color,Player[i].bMan);
		Player[i].bFirstDeath = true;
	}	
	shake_x = 0;
	shake_y = 0;
	HangonType = -1;
	HangonLife = 0;
	TimeStopType = 0;
	bTimeStop = false;
	bSecondSun = false;
	if(Map.type==3)	bIceStream = true;
	else		bIceStream = false;
	bTreasure = false;
	TreasureCount = 0;
	bYukari = false;
	bAICheck = false;
	Hanten = -1;
	MapFlash = -1;
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
	scene = TITLE;
	SLoad();
	MuLoad();
	GLoad();
	MeLoad();
	GameLoad();
	NetWork.Load();
	for(int i=0;i<4;i++){
		Player[i].bMan = true;
		Player[i].level = 1;
	}
	for(int i=0;i<DIRECTORY_NUM;i++){
		for(int j=0;j<BGM_NUM[i];j++){
			if(strcmp(BgmName[i][j],"53ミニッツの青い海")==0){
				play_bgm(i,j);
			} 
		}
	}
	replay_play = false;
	replay_play_num = 0;
	
	return;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
        SetWindowText("爆！幻想郷Ⅱ　ver0.94a");        
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
			case RESULT:	MeMain();	break;
			case RESULT2:	MeMain();	break;
			case OPTION:	MeMain();	break;
			case SETTINGA:	MeMain();	break;
			case SETTINGB:	MeMain();	break;
			case SETTINGC:	MeMain();	break;
			case NETSETTINGA:MeMain();	break;
			case NETSETTINGB:MeMain();	break;
		}
		if(title_carsol==1&&scene!=TITLE){
			NetWork.DrawGuest();
		}
		bOnline = false;
		if(title_carsol==1){
			for(int i=0;i<MAX_CONNECT;i++){
				if(NetWork.GetConnectTcp(i)!=-1){
					bOnline = true;
					break;
				}
			}
		}
		if(bOnline==true){
			if(SAVE.Key_Type[0]==DX_INPUT_KEY&&c_key[KEY_INPUT_F1]==1){
				if(NetWork.bChat==true)	NetWork.bChat = false;
				else			NetWork.bChat = true;
			}
			NetWork.ChatFunction();
		}
		
		//PlaySound();
		SnapShot();
		if(scene==GAME)	Fps();
		//Debug();
		SCheckPlayTime();
		ScreenFlip();
	}while(scene!=END&&ProcessMessage()==0&&!(c_key[KEY_INPUT_F4]>0&&(c_key[KEY_INPUT_LALT]>0||c_key[KEY_INPUT_RALT]>0)));

	SSave();
        DxLib_End();
        return 0 ;              // ソフトの終了
}

void MainGame(){
	int usernum = 0;
	for(int i=0;i<4;i++){
		if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
			usernum++;
		}
	}
	if(replay_play==true)	usernum = 0;
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
		if(Player[i].get_condition()==0&&i==HangonType){
			if(Para.start_count==0)	Player[i].hangon_control();
		}
		else if(Player[i].get_condition()==0){
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
			if(i!=HangonType&&Player[i].get_condition()==0&&bTimeStop==false){
				float px,py;
				Player[i].get_xy(&px,&py);
				float sx = px - (*it).x;
				float sy = py - (*it).y;
				if(sqrt(sx*sx+sy*sy)<(*it).atari){
					if(usernum>=2){
						if(Player[i].bMan==true&&SAVE.User[i]!=-1){
							if(!(bOnline==true&&i!=NetWork.NFD[0].player_num))	Profile[SAVE.User[i]].danmaku_num++;
						}
						if(HangonType>=0&&Player[HangonType].bMan==true&&SAVE.User[HangonType]!=-1){
							if(!(bOnline==true&&HangonType!=NetWork.NFD[0].player_num))	Profile[SAVE.User[HangonType]].kill_num++;
						}
					}
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
			if(Player[i].get_condition()==0&&(Player[i].get_chara()==SAKUYA||Player[i].bTime==true)){
				Player[i].draw();
			}
		}
	}
	else{
		TimeStopType = 0;	
	}
	if(Para.time_count==3600){
		if(usernum>=2){
			for(int i=0;i<4;i++){
				if(Player[i].bMan==true&&SAVE.User[i]!=-1){
					if(!(bOnline==true&&i!=NetWork.NFD[0].player_num))	Profile[SAVE.User[i]].sadon_match_num++;
					if(!(bOnline==true&&i!=NetWork.NFD[0].player_num)){
						if(Player[i].get_condition()==0)	Profile[SAVE.User[i]].sadon_num++;
					}
				}
			}
		}
		
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
		if(Player[i].get_condition()==0||Player[i].get_condition()==-1)	living ++;
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
	if(bOnline==true){
		for(int i=0;i<4;i++){
			if(NetWork.NGD.input[i]&4)	pause ++;
		}
	}
	else{
		for(int i=0;i<4;i++){
			pause += c_pad[i][SAVE.Key_Pause[i]];
		}
		pause += c_key[KEY_INPUT_ESCAPE];
	}
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
			for(int a=0;a<SAVE.MatchNum;a++){
				int color;
				if(a<Player[i].victory)	color = GetColor(255,255,200);	
				else			color = GetColor(30,30,0);	
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
			if(Rcount==150){
				for(int i=0;i<4;i++){
					if(Player[i].get_condition()==0){
						SReplay.winner[SReplay.match-1] = i;
						break;
					}			
				}
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
					for(int i=0;i<4;i++){
						if(Player[i].victory==SAVE.MatchNum){
							SReplay.last_winner = i;
							break;
						}
					}
					//リプレイ保存しますか？
					save_num = 0;
					if(replay_play==true){
						change_scene(TITLE);
						DeleteGraph(gSnap);	
						gSnap = MakeGraph(640,480);	
					}
					else{
						int usernum = 0;
						for(int i=0;i<4;i++){
							if((Player[i].bMan==true&&SAVE.User[i]!=-1)||(bOnline==true&&netsettingB_carsol[i]<NetWork.NFD[0].connect_num+1)){
								usernum++;
							}
						}
						if(replay_play==true)	usernum = 0;
						if(usernum>=2){
							for(int i=0;i<4;i++){
								if(Player[i].bMan==true&&SAVE.User[i]!=-1&&!(bOnline==true&&i!=NetWork.NFD[0].player_num)){
									Profile[SAVE.User[i]].match_num++;
									Profile[SAVE.User[i]].chara_num[Player[i].chara]++;
									if(Player[i].victory==SAVE.MatchNum){
										Profile[SAVE.User[i]].win_num++;
										int plus = 0;
										for(int j=0;j<4;j++){
											if(i!=j&&Player[j].bMan==true&&SAVE.User[j]!=-1){
												int m = (500 + Profile[SAVE.User[j]].rate - Profile[SAVE.User[i]].rate)/10.0;
												plus += m;
											}
										}
										plus /= usernum-1;
										if(plus<0)	plus = 0;
										if(Profile[SAVE.User[i]].match_num<=30)	plus *= 2;
										if(Profile[SAVE.User[i]].match_num<=50)	plus *= 1.5;
										Profile[SAVE.User[i]].rate += plus;
									}
									else if(!(bOnline==true&&i!=NetWork.NFD[0].player_num)){
										int rank = 0;
										for(int j=0;j<4;j++){
											if(i!=j&&Player[i].victory<=Player[j].victory)	rank++;
										}
									 	Profile[SAVE.User[i]].lose_num[rank-1]++;
										int minus = 0;
										for(int j=0;j<4;j++){
											if(i!=j&&Player[j].bMan==true&&SAVE.User[j]!=-1){
												int m = (Profile[SAVE.User[i]].rate - Profile[SAVE.User[j]].rate - 100.0)/10.0;
												if(Player[j].victory==SAVE.MatchNum)	m *= 3;
												minus += m;
											}
										}
										minus /= usernum-1;
										if(minus<=0)	minus = 1;
										minus *= (float)rank*0.8;
										if(Profile[SAVE.User[i]].match_num<30)		minus *= 2.5;
										else if(Profile[SAVE.User[i]].match_num<50)	minus *= 2.0;
										else if(Profile[SAVE.User[i]].match_num<100)	minus *= 1.5;
										Profile[SAVE.User[i]].rate -= minus;
									}
									if(!(bOnline==true&&i!=NetWork.NFD[0].player_num)){
										if(Profile[SAVE.User[i]].rate>Profile[SAVE.User[i]].max_rate){
											Profile[SAVE.User[i]].max_rate = Profile[SAVE.User[i]].rate;
										}
									}
								}
							}
						}
						Rcount2 = 1;
						Rcount--;
					}			
				}
			}
			else{
				GameLoad();
				SReplay.start_count[SReplay.match] = replay_count;
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
		float x = 170;
		float y = 150;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		SetDrawBright(255,255,200);
		char me[6];
		sprintf(me,"PAUSE");
		draw_string(x,y,6,me);
		SetDrawBright(255,255,255);
		for(int i=0;i<2;i++){
			if(carsol==i)	SetDrawBright(255,255,255);
			else		SetDrawBright(100,100,100);
			x = 200;
			y = 200 + 40*i;
			if(bOnline==true){
				if(i==0)	wsprintf(message , "ゲームを再開する");
				else		wsprintf(message , "最初の設定に戻る");
			}
			else{
				if(i==0)	wsprintf(message , "ゲームを再開する");
				else		wsprintf(message , "タイトルに戻る");
			}
			DrawSt(x,y,GetColor(255,255,255),0,font_default,message);
		}
		SetDrawBright(255,255,255);
		for(int i=0;i<PLAYER_NUM;i++){
			char message[64];
			float x = 300;
			float y = 280 + 20*i;
			if(Player[i].bMan==true)	wsprintf(message , "Player%d",i+1);
			else				wsprintf(message , "COM%d   ",i+1);
			draw_string(x,y,7,message);
			for(int a=0;a<SAVE.MatchNum;a++){
				int color;
				if(a<Player[i].victory)	color = GetColor(255,255,200);	
				else			color = GetColor(30,30,0);	
				DrawSt(x+100+15*a,y,color,0,font_default,"★");
			}
		}
		int bomb=0,spell=0,up=0,down=0,left=0,right=0,pause=0;
		int carsol_num = 2;
		if(bOnline==true){
			for(int i=0;i<PLAYER_NUM;i++){
				if(NetWork.NGD.input[i]&1)	bomb ++;
				else			bomb = 0;
				if(NetWork.NGD.input[i]&2)	spell ++;
				else			spell = 0;
				if(NetWork.NGD.input[i]&4)	pause ++;
				else			pause = 0;
				if(NetWork.NGD.input[i]&8)	up ++;
				else			up = 0;
				if(NetWork.NGD.input[i]&16)	down ++;
				else			down = 0;
				if(NetWork.NGD.input[i]&32)	left ++;
				else			left = 0;
				if(NetWork.NGD.input[i]&64)	right ++;
				else			right = 0;
			}
		}
		else{
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
			bomb += c_key[KEY_INPUT_RETURN];
			spell += c_key[KEY_INPUT_X];
			up += c_key[KEY_INPUT_UP];
			down += c_key[KEY_INPUT_DOWN];
			left += c_key[KEY_INPUT_LEFT];
			right += c_key[KEY_INPUT_RIGHT];
			pause += c_key[KEY_INPUT_ESCAPE];
		}
		
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

void Debug(){
	/*
	DrawFormatString(0,0,GetColor(255,255,255),"DIRECTORY_NUM:%d",DIRECTORY_NUM);
	int i;
	for(i=0;i<DIRECTORY_NUM;i++){
		DrawFormatString(0,10+10*i,GetColor(255,255,255),"BGM_NUM[%d]:%d",i,BGM_NUM[i]);
	}
	DrawFormatString(0,10+10*i+10,GetColor(255,255,255),"now_playing:(%d,%d)",now_playing_directory,now_playing);
	*/
	if(c_key[KEY_INPUT_U]==1){
		Player[0].level_plus();
	}
	if(c_key[KEY_INPUT_M]==1){
		Player[0].spell_level = 1;
	}
	if(c_key[KEY_INPUT_J]==1){
		Player[0].gage_plus(10000);
	}
	if(c_key[KEY_INPUT_D]==1){
		if(Player[0].dokuro_count==0){
			int a = get_rand(10);
			if(a==0&&(Player[0].dokuro&1)==0)		Player[0].dokuro += 1;
			else if(a==1&&(Player[0].dokuro&2)==0)		Player[0].dokuro += 2;
			else if(a==2&&(Player[0].dokuro&4)==0)		Player[0].dokuro += 4;
			else if(a==3&&(Player[0].dokuro&8)==0)		Player[0].dokuro += 8;
			else if(a==4&&(Player[0].dokuro&16)==0)		Player[0].dokuro += 16;
			else if(a==5&&(Player[0].dokuro&32)==0)		Player[0].dokuro += 32;
			else if(a==6&&(Player[0].dokuro&64)==0)		Player[0].dokuro += 64;
			else if(a==7&&(Player[0].dokuro&128)==0)	Player[0].dokuro += 128;
			else if(a==8&&(Player[0].dokuro&256)==0)	Player[0].dokuro += 256;
			else if(a==9&&(Player[0].dokuro&512)==0)	Player[0].dokuro += 512;
			else if(a==10&&(Player[0].dokuro&1024)==0)	Player[0].dokuro += 1024;
			Player[0].dokuro_count = 1;
		}
		else{
			Player[0].dokuro_count = 0;
			Player[0].dokuro = 0;
		}
	}
	if(c_key[KEY_INPUT_W]==1){
		play_sound(11);
		Player[0].set_spell_count(1);
		float x,y;
		Player[0].get_xy(&x,&y);
		while(1){
			int rand = get_rand(36);
			if(rand==9 || rand==21){}
			if(rand==8){
				SpMake(x,y,0,0,-1,true);
				SpMake(x,y,8,0,-1,true);
				SpMake(x,y,9,0,-1,true);
				break;
			}
			else{
				SpMake(x,y,rand,0,-1,true);
				break;
			}
		}
	}							
	if(c_key[KEY_INPUT_Q]==1){
		for(int i=0;i<4;i++){
			if(Player[i].bMan==false&&Player[i].get_condition()!=-1){
				Player[i].change_condition(-1);
				break;
			}
		}
	}
	if(c_key[KEY_INPUT_S]==1){
		if(Para.time_count>3601)	Para.time_count = 3601;
		else				Para.time_count /= 2;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);                 
	DrawFormatString(0,0,GetColor(255,255,255),"デバッグモードON");

	return;
}