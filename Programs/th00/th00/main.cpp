//------------------------------------------------------------------------------
//
//	th00	09.03.30 ~ 09.09.22
//		ver1.5	09.11.05 ~ 09.11.30
//                       
//------------------------------------------------------------------------------

#include "extern.h"
#include "STG.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
        SetWindowText("東方大往生　～ the Eastern Indolent Life.　ver1.51a");        
	SetWindowIconID(101);
	starts();
        //ChangeWindowMode( TRUE );
        if( DxLib_Init() == -1 ) return -1; // ＤＸライブラリ初期化処理 エラーが起きたら終了
	SLoad();
	SReset();

	do{
		main_loop = 1;
		main_draw = 0;
		for(loop_count=0;loop_count<main_loop;loop_count++){
			int count = loop_count;
			loop_count = main_loop-1-count;
			if(Game.scene==SHOOTING&&PlayerControlFlag!=0){
				if(c_key[KEY_INPUT_LCONTROL]>0)	main_loop = 5;
			}
			if((Game.scene==SHOOTING&&PlayerControlFlag!=0) || (FlagSlow==true)){
				if((c_key[KEY_INPUT_RCONTROL]>0) || (FlagSlow==true)){
					main_loop = 1;
					if(SkipCount%3!=0)	main_draw = 1;
				}
			}
			if(main_draw==0){
				volume = SAVE.BGM;
				frame = 60;
				ClearDrawScreen();
				switch(Game.scene){
					case TITLE:		SMe_Title();		break;
					case SELECT_LEVEL:	SMe_SelectLevel();	break;
					case SELECT_PLAYER:	SMe_SelectPlayer();	break;
					case SELECT_WEAPON:	SMe_SelectWeapon();	break;
					case REPLAY:		SMe_Replay();		break;
					case RESULT:		SMe_Result();		break;
					case MUSIC_ROOM:	SMe_MusicRoom();	break;
					case OPTION:		SMe_Option();		break;
					case KEY_CONFIG:	SMe_KeyConfig();	break;
					case SHOOTING:		Smain();		break;
					case ENDING:		SEnd_Main();		break;
					case STAFFROLE:		SSR_Main();		break;
				}
				CheckPushKey();
				Game.game_count++;
			}
			SkipCount++;
			loop_count = count;		
		}		
		SSoundEffect();
		SCheckPlayTime();
		//Debug();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(Game.scene==SHOOTING)	FpsDraw();
		SnapShot();
		if(ConfigCount%(Config.drawmode+1)==Config.drawmode){
			ScreenFlip();
		}
		Fps();
		ConfigCount++;
	}while(Game.scene!=END&&ProcessMessage()==0&&!(c_key[KEY_INPUT_F4]>0&&(c_key[KEY_INPUT_LALT]>0||c_key[KEY_INPUT_RALT]>0)));
	SSave();	
        DxLib_End();
        return 0 ;              // ソフトの終了
}

void DebugStage(){
	int c = Game.count;
	if(c==0){
		for(int i=0;i<6;i++){
			SEn_Make(CENTER_X-30-30*i,-20,i/2,100,0,0,i/2);
			SEn_Make(CENTER_X+30+30*i,-20,i/2,100,0,0,i/2);
		}
	}
	if(c==120){
		for(int i=0;i<2;i++){
			SEn_Make(CENTER_X-20+40*i,-20,3,1000,0,1,3);
		}
	}
	if(c>=240&&c<300&&c%3==0){
		SEn_Make(-20,20+get_rand(100),4,100,1,2,get_rand(1));
		SEn_Make(430,20+get_rand(100),4,100,1,2,get_rand(1));
	}
	
	return;
}

void Stage1(){
	int c = Game.count;	
	if(60<=c&&c<120&&c%8==0){
		if(c<104)	SEn_Make(50+get_rand(100),-20,0,100,2,3,0);
		else 		SEn_Make(50+get_rand(100),-20,1,100,2,3,1);
	}
	if(180<=c&&c<240&&c%8==0){
		if(c<224)	SEn_Make(370-get_rand(100),-20,0,100,3,3,0);
		else 		SEn_Make(370-get_rand(100),-20,1,100,3,3,1);
	}
	if(c==300){
		SEn_Make(CENTER_X,-20,3,2500,4,4,3);
	}
	if(330<=c&&c<480&&c%10==0){
		if(c<450)	SEn_Make(50+get_rand(100),-20,0,100,5,3,0);
		else if(c<470)	SEn_Make(50+get_rand(100),-20,1,100,5,3,1);
		else 		SEn_Make(50+get_rand(100),-20,2,100,5,3,2);
		if(c<450)	SEn_Make(370-get_rand(100),-20,0,100,6,3,0);
		else if(c<470)	SEn_Make(370-get_rand(100),-20,1,100,6,3,1);
		else 		SEn_Make(370-get_rand(100),-20,2,100,6,3,2);
	}
	if(1660<=c&&c<2880){
		if(c<2600){
			if(c%50==0)		SEn_Make(CENTER_X-get_rand(150),-20,0,100,7,3,0);
			else if(c%50==25)	SEn_Make(CENTER_X+get_rand(150),-20,0,100,7,3,0);
		}
		else{
			if(c%50==0)		SEn_Make(CENTER_X-get_rand(150),-20,1,100,7,8,1);
			else if(c%50==25)	SEn_Make(CENTER_X+get_rand(150),-20,1,100,7,8,1);
		}
		if(c%720==0){
			SEn_Make(CENTER_X-50,-20,3,1500,4,5,3);
		}
		else if(c%720==360){
			SEn_Make(CENTER_X+50,-20,3,1500,4,5,3);
		}
	}
	if(c==3030){
		SBos_Make(-10,-10,0,9000,-1,0,0,0,0,20);
	}
	if(c>3030&&GameScene==0&&c<3640){
		if(c%120==0)	SEn_Make(50+get_rand(160),-20,0,300,8,6,0);
		if(c%120==60)	SEn_Make(370-get_rand(160),-20,0,300,8,7,0);
	}
	if(3750<=c&&GameScene==0){
		if(c==5130){
			SEn_Make(CENTER_X-50,-20,3,1500,4,5,3);
			SEn_Make(CENTER_X+50,-20,3,1500,4,5,3);
		}
		else if(c<5070){
			if((c-3750)%6==0){
				int rand = get_rand(5);
				int color;
				if(rand<3)	color = 2;
				else if(rand<5)	color = 0;
				else		color = 1;
				if((c-3750)%120<18){
					SEn_Make(50+get_rand(100),-20,color,100,2,8,color);
				}
				else if((c-3750)%120<60){}
				else if((c-3750)%120<78){
					SEn_Make(370-get_rand(100),-20,color,100,3,8,color);
				}
			}
		}
	}
	if(c==5610){
		Talk.count ++;
	}
	return;
}

void Stage2(){
	int c = Game.count;
	if(180<=c&&c<310&&c%10==0){
		if(c<210)		SEn_Make(0,-20,5,15,9,9,0);
		else if(c<280) 		SEn_Make(0,-20,6,15,9,9,1);
		else 	 		SEn_Make(0,-20,7,15,9,9,2);
	}
	if(280<=c&&c<400&&c%10==0){
		if(c<300)		SEn_Make(422,-20,5,15,10,9,0);
		else if(c<370) 		SEn_Make(422,-20,6,15,10,9,1);
		else 	 		SEn_Make(422,-20,7,15,10,9,2);
	}
	if(440<=c&&c<600&&c%10==0){
		if(c<500)		SEn_Make(0,-20,5,15,9,9,0);
		else if(c<580) 		SEn_Make(0,-20,6,15,9,9,1);
		else 	 		SEn_Make(0,-20,7,15,9,9,2);
		if(c<500)		SEn_Make(422,-20,5,15,10,9,0);
		else if(c<580) 		SEn_Make(422,-20,6,15,10,9,1);
		else 	 		SEn_Make(422,-20,7,15,10,9,2);
	}
	if(1300<=c&&c<1480&&c%30==0){
		SEn_Make(CENTER_X-170+(c-1300)/30*25,480,0,100,11,10,0);
		SEn_Make(CENTER_X+170-(c-1300)/30*25,480,0,100,11,10,0);
	}
	if(1580<=c&&c<1760&&c%30==0){
		SEn_Make(CENTER_X-170+(c-1580)/30*25,480,1,100,11,10,1);
		SEn_Make(CENTER_X+170-(c-1580)/30*25,480,1,100,11,10,1);
	}
	if(1860<=c&&c<1980&&c%30==0){
		SEn_Make(CENTER_X-170+(c-1860)/30*25,480,2,100,11,10,2);
		SEn_Make(CENTER_X+170-(c-1860)/30*25,480,2,100,11,10,2);
	}
	if(2060<=c&&c<2660&&c%20==0){
		if(c%100==0||c%100==40||c%100==80)	SEn_Make(40+get_rand(342),0,7,20,12,-1,2);
		if(c%100==20)	SEn_Make(40+get_rand(342),0,6,20,12,-1,1);
		if(c%100==60)	SEn_Make(40+get_rand(342),0,5,20,12,-1,0);
	}
	if(2760<=c&&c<2890&&c%10==0){
		if(c<2790)		SEn_Make(422,CENTER_Y,5,15,14,9,0);
		else if(c<2860) 	SEn_Make(422,CENTER_Y,6,15,14,9,1);
		else 	 		SEn_Make(422,CENTER_Y,7,15,14,9,2);
	}
	if(2860<=c&&c<2980&&c%10==0){
		if(c<2890)		SEn_Make(0,CENTER_Y,5,15,13,9,0);
		else if(c<2950) 	SEn_Make(0,CENTER_Y,6,15,13,9,1);
		else 	 		SEn_Make(0,CENTER_Y,7,15,13,9,2);
	}
	if(3030<=c&&c<3190&&c%10==0){
		if(c<3090)		SEn_Make(0,CENTER_Y,5,15,13,9,0);
		else if(c<3170) 	SEn_Make(0,CENTER_Y,6,15,13,9,1);
		else 	 		SEn_Make(0,CENTER_Y,7,15,13,9,2);
		if(c<3090)		SEn_Make(422,CENTER_Y,5,15,14,9,0);
		else if(c<3170) 	SEn_Make(422,CENTER_Y,6,15,14,9,1);
		else 	 		SEn_Make(422,CENTER_Y,7,15,14,9,2);
	}
	if(c==3370){
		SPlaySound(11);
		SEn_Make(CENTER_X,-20,3,6000,15,11,3);
	}
	if(c==3690){
		SPlaySound(11);
		SEn_Make(CENTER_X,-20,3,6000,15,12,3);
	}
	if(c==4010){
		SPlaySound(11);
		SEn_Make(CENTER_X,-20,3,6000,15,13,3);
	}
	if(4300<=c&&c<4800&&c%30==0){
		if(c%150==0||c%150==60||c%150==120)	SEn_Make(40+get_rand(342),0,6,20,12,-1,1);
		if(c%150==30)	SEn_Make(40+get_rand(342),0,5,20,12,-1,0);
		if(c%150==90)	SEn_Make(40+get_rand(342),0,7,20,12,-1,2);
	}
	if(4800<=c&&c<5000&&c%5==0){
		if(c<4970)	SEn_Make(-20+450*(c%10/5),50+get_rand(150),4,100,1,14,0);
		else		SEn_Make(-20+450*(c%10/5),50+get_rand(150),4,100,1,14,1);
	}
	if(c==5300){
		SBos_Make(-10,CENTER_Y,0,1,12+SAVE.Level,1,3,-2,13,255);
		Boss.gage_exist = 0;
		Boss.b_zanzou = true;	
	}
	if(Boss.life<=0&&5500<=c&&c<6600&&c%10==0){
		if(c%30==0)	SEn_Make(80+get_rand(262),0,5,50,16,-1,0);
		else		SEn_Make(80+get_rand(262),0,7,50,16,-1,2);
	}
	if(c==6800){
		Talk.count ++;
	}
	return;
}

void Stage3(){
	static int after_boss_count;
	static int enemy_type;
	static int flag;
	int c = Game.count;
	if(c==0)	flag = 0;
	if(120<=c&&c<300&&c%5==0){
		SEn_Make(80+get_rand(262),0,5,100,17,16,0);
	}
	if(c==650){
		SBos_Make(-10,-10,0,12000,28+SAVE.Level,0,11,10,3,13);
		Boss.gage_exist = 0;
		Boss.b_atari = false;
		GameScene = 0;
		Talk.count ++;
	}
	if(c>650&&c<2800&&Boss.exist==0){
		int cp = c%100;
		if(cp==0){
			if(c<2500){
				int rand = 70+get_rand(60);
				for(int i=0;i<2;i++){
					SEn_Make(CENTER_X-rand/2+rand*i,100+get_rand(100),3,400,18,17,4);
				}
			}
			else{
				int rand = get_rand(360);
				for(int i=0;i<3;i++){
					float angle = Radian(rand+120*i,TRUE);
					SEn_Make(CENTER_X+100*cos(angle),150+100*sin(angle),3,400,18,17,5);
				}
			}
		}
	}
	if(c==2900){
		SBos_Make(-100,-100,0,12000,32+SAVE.Level,1,13,12,4,19);
		Boss.gage_exist = 0;
		Boss.b_atari = false;
		GameScene = 0;
		Talk.count ++;
	}
	if(c>2900&&Boss.exist==0&&flag==0){
		after_boss_count = 0;
		enemy_type = 270;
		flag = 1;
	}
	if(after_boss_count>60&&c>2900&&c<5900&&Boss.exist==0){
		int cp = c%10;
		if(cp==0){
			float angle = Radian(enemy_type,TRUE);
			int type;
			if(c>4500){
				if(enemy_type%1080<360)		type = 2;
				else if(enemy_type%1080<720)	type = 1;
				else				type = 0;
			}
			else{
				type = 2;
			}
			SEn_Make(CENTER_X+150*cos(angle),CENTER_Y+145*sin(angle),type,100,19,18,type);
			enemy_type += 35;
		}
	}
	if(c==5900)	after_boss_count = 0;
	if(c<5900&&after_boss_count>=120)	after_boss_count = 119;
	if(after_boss_count==120&&c>5400&&Boss.exist==0){
		Game.i_hanyou[1] = 1;
	}
	if(after_boss_count==420&&c>5400&&Boss.exist==0){
		Talk.count ++;
	}
	after_boss_count++;
	return;
}

void Stage4(){
	int c = Game.count;	
	if(60<=c&&c<120&&c%8==0){
		if(c<104)	SEn_Make(50+get_rand(100),-20,0,150,2,23,0);
		else 		SEn_Make(50+get_rand(100),-20,1,150,2,23,1);
	}
	if(180<=c&&c<240&&c%8==0){
		if(c<224)	SEn_Make(370-get_rand(100),-20,0,150,3,23,0);
		else 		SEn_Make(370-get_rand(100),-20,1,150,3,23,1);
	}
	if(c==300){
		SEn_Make(CENTER_X,-20,3,4500,4,24,3);
	}
	if(330<=c&&c<480&&c%10==0){
		if(c<400)	SEn_Make(50+get_rand(100),-20,0,150,5,23,0);
		else if(c<420)	SEn_Make(50+get_rand(100),-20,1,150,5,23,1);
		else 		SEn_Make(50+get_rand(100),-20,2,150,5,23,2);
		if(c<400)	SEn_Make(370-get_rand(100),-20,0,150,6,23,0);
		else if(c<420)	SEn_Make(370-get_rand(100),-20,1,150,6,23,1);
		else 		SEn_Make(370-get_rand(100),-20,2,150,6,23,2);
	}
	if(1660<=c&&c<2880){
		if(c<2600){
			if(c%50==0)		SEn_Make(CENTER_X-get_rand(150),-20,0,150,7,23,0);
			else if(c%50==25)	SEn_Make(CENTER_X+get_rand(150),-20,0,150,7,23,0);
		}
		else{
			if(c%50==0)		SEn_Make(CENTER_X-get_rand(150),-20,1,150,7,28,1);
			else if(c%50==25)	SEn_Make(CENTER_X+get_rand(150),-20,1,150,7,28,1);
		}
		if(c%720==0){
			SEn_Make(CENTER_X-50,-20,3,1700,4,25,3);
		}
		else if(c%720==360){
			SEn_Make(CENTER_X+50,-20,3,1700,4,25,3);
		}
	}
	if(c==3030){
		SBos_Make(-10,-10,0,9000,-1,0,0,17,5,20);
	}
	if(c>3030&&GameScene==0&&c<3640){
		if(c%120==0)	SEn_Make(50+get_rand(160),-20,0,500,8,26,0);
		if(c%120==60)	SEn_Make(370-get_rand(160),-20,0,500,8,27,0);
	}
	if(3750<=c&&GameScene==0){
		if(c==5130){
			SEn_Make(CENTER_X-50,-20,3,1700,4,25,3);
			SEn_Make(CENTER_X+50,-20,3,1700,4,25,3);
		}
		else if(c<5070){
			if((c-3750)%6==0){
				if((c-3750)%120<18){
					int cp = (c-3750)%120/6;
					SEn_Make(50+get_rand(100),-20,cp,150,2,28,cp);
				}
				else if((c-3750)%120<60){}
				else if((c-3750)%120<78){
					int cp = ((c-3750)%120-60)/6;
					SEn_Make(370-get_rand(100),-20,cp,150,3,28,cp);
				}
			}
		}
	}
	if(c==5610){
		Talk.count ++;
	}
	return;
}

void Stage5(){
	int c = Game.count;
	if(180<=c&&c<310&&c%10==0){
		if(c<210)		SEn_Make(0,-20,5,30,9,29,0);
		else if(c<280) 		SEn_Make(0,-20,6,30,9,29,1);
		else 	 		SEn_Make(0,-20,7,30,9,29,2);
	}
	if(280<=c&&c<400&&c%10==0){
		if(c<300)		SEn_Make(422,-20,5,30,10,29,0);
		else if(c<370) 		SEn_Make(422,-20,6,30,10,29,1);
		else 	 		SEn_Make(422,-20,7,30,10,29,2);
	}
	if(440<=c&&c<600&&c%10==0){
		if(c<500)		SEn_Make(0,-20,5,30,9,29,0);
		else if(c<580) 		SEn_Make(0,-20,6,30,9,29,1);
		else 	 		SEn_Make(0,-20,7,30,9,29,2);
		if(c<500)		SEn_Make(422,-20,5,30,10,29,0);
		else if(c<580) 		SEn_Make(422,-20,6,30,10,29,1);
		else 	 		SEn_Make(422,-20,7,30,10,29,2);
	}
	if(1300<=c&&c<1480&&c%30==0){
		SEn_Make(CENTER_X-170+(c-1300)/30*25,480,0,100,11,30,0);
		SEn_Make(CENTER_X+170-(c-1300)/30*25,480,0,100,11,30,0);
	}
	if(1580<=c&&c<1760&&c%30==0){
		SEn_Make(CENTER_X-170+(c-1580)/30*25,480,1,100,11,30,1);
		SEn_Make(CENTER_X+170-(c-1580)/30*25,480,1,100,11,30,1);
	}
	if(1860<=c&&c<1980&&c%30==0){
		SEn_Make(CENTER_X-170+(c-1860)/30*25,480,2,100,11,30,2);
		SEn_Make(CENTER_X+170-(c-1860)/30*25,480,2,100,11,30,2);
	}
	if(2060<=c&&c<2660&&c%20==0){
		if(c%100==0||c%100==40||c%100==80)	SEn_Make(40+get_rand(342),0,7,35,12,31,2);
		if(c%100==20)	SEn_Make(40+get_rand(342),0,6,35,12,31,1);
		if(c%100==60)	SEn_Make(40+get_rand(342),0,5,35,12,31,0);
	}
	if(2760<=c&&c<2890&&c%10==0){
		if(c<2790)		SEn_Make(422,CENTER_Y,5,30,14,29,0);
		else if(c<2860) 	SEn_Make(422,CENTER_Y,6,30,14,29,1);
		else 	 		SEn_Make(422,CENTER_Y,7,30,14,29,2);
	}
	if(2860<=c&&c<2980&&c%10==0){
		if(c<2890)		SEn_Make(0,CENTER_Y,5,30,13,29,0);
		else if(c<2950) 	SEn_Make(0,CENTER_Y,6,30,13,29,1);
		else 	 		SEn_Make(0,CENTER_Y,7,30,13,29,2);
	}
	if(3030<=c&&c<3190&&c%10==0){
		if(c<3090)		SEn_Make(0,CENTER_Y,5,30,13,29,0);
		else if(c<3170) 	SEn_Make(0,CENTER_Y,6,30,13,29,1);
		else 	 		SEn_Make(0,CENTER_Y,7,30,13,29,2);
		if(c<3090)		SEn_Make(422,CENTER_Y,5,30,14,29,0);
		else if(c<3170) 	SEn_Make(422,CENTER_Y,6,30,14,29,1);
		else 	 		SEn_Make(422,CENTER_Y,7,30,14,29,2);
	}
	if(c==3370){
		SPlaySound(11);
		SEn_Make(CENTER_X,-20,3,6000,15,32,3);
	}
	if(c==3690){
		SPlaySound(11);
		SEn_Make(CENTER_X,-20,3,6000,15,33,3);
	}
	if(c==4010){
		SPlaySound(11);
		SEn_Make(CENTER_X,-20,3,6000,15,34,3);
	}
	if(4400<=c&&c<4800&&c%30==0){
		if(c%150==0||c%150==60||c%150==120)	SEn_Make(40+get_rand(342),0,6,35,12,31,1);
		if(c%150==30)	SEn_Make(40+get_rand(342),0,5,35,12,31,0);
		if(c%150==90)	SEn_Make(40+get_rand(342),0,7,35,12,31,2);
	}
	if(4800<=c&&c<5000&&c%5==0){
		if(c<4970)	SEn_Make(-20+450*(c%10/5),50+get_rand(150),4,150,1,14,0);
		else		SEn_Make(-20+450*(c%10/5),50+get_rand(150),4,150,1,14,1);
	}
	if(c==5300){
		SBos_Make(-10,CENTER_Y,0,1,64+SAVE.Level,1,3,-2,13,255);
		Boss.gage_exist = 0;
		Boss.b_zanzou = true;	
	}
	if(Boss.life<=0&&5500<=c&&c<6600&&c%10==0){
		if(c%30==0)	SEn_Make(80+get_rand(262),0,5,50,16,35,0);
		else		SEn_Make(80+get_rand(262),0,7,50,16,35,2);
	}
	if(c==6800){
		Talk.count ++;
	}
	return;
}

void Stage6(){
	static int after_boss_count;
	static int enemy_type;
	static int flag;
	int c = Game.count;
	if(c==0)	flag = 0;
	if(120<=c&&c<300&&c%5==0){
		SEn_Make(80+get_rand(262),0,5,100,17,36,0);
	}
	if(c==650){
		SBos_Make(-10,-10,0,12000,76+SAVE.Level,0,11,23,7,13);
		Boss.gage_exist = 0;
		Boss.b_atari = false;
		GameScene = 0;
		Talk.count ++;
	}
	if(c>650&&c<2800&&Boss.exist==0){
		int cp = c%100;
		if(cp==0){
			if(c<2500){
				int rand = 70+get_rand(60);
				for(int i=0;i<2;i++){
					SEn_Make(CENTER_X-rand/2+rand*i,100+get_rand(100),3,400,18,37,4);
				}
			}
			else{
				int rand = get_rand(360);
				for(int i=0;i<3;i++){
					float angle = Radian(rand+120*i,TRUE);
					SEn_Make(CENTER_X+100*cos(angle),150+100*sin(angle),3,400,18,37,5);
				}
			}
		}
	}
	if(c==2900){
		SBos_Make(-100,-100,0,12000,79+SAVE.Level,1,13,24,8,19);
		Boss.gage_exist = 0;
		Boss.b_atari = false;
		GameScene = 0;
		Talk.count ++;
	}
	if(c>2900&&Boss.exist==0&&flag==0){
		after_boss_count = 0;
		enemy_type = 270;
		flag = 1;
	}
	if(after_boss_count>60&&c>2900&&c<5900&&Boss.exist==0){
		int cp = c%10;
		if(cp==0){
			float angle = Radian(enemy_type,TRUE);
			int type;
			if(c>4500){
				if(enemy_type%1080<360)		type = 0;
				else if(enemy_type%1080<720)	type = 2;
				else				type = 1;
			}
			else{
				type = 2;
			}
			SEn_Make(CENTER_X+150*cos(angle),CENTER_Y+145*sin(angle),type,100,19,38,type+6);
			enemy_type += 35;
		}
	}
	if(c==5900)	after_boss_count = 0;
	if(c<5900&&after_boss_count>=120)	after_boss_count = 119;
	if(after_boss_count==120&&c>5400&&Boss.exist==0){
		Game.i_hanyou[1] = 1;
	}
	if(after_boss_count==420&&c>5400&&Boss.exist==0){
		Talk.count ++;
	}
	after_boss_count++;
	return;
}

void Stage7(){
	int c = Game.count;	
	if(180<=c&&c<270&&c%6==0){
		SEn_Make(30+2*(c-180),-20,0,100,2,52,0);
	}
	if(370<=c&&c<460&&c%6==0){
		SEn_Make(390-2*(c-370),-20,0,100,3,52,0);
	}
	if(560<=c&&c<650&&c%6==0){
		if(c<620){
			SEn_Make(30+2*(c-560),-20,1,100,2,52,1);
			SEn_Make(390-2*(c-560),-20,1,100,3,52,1);
		}
		else{
			SEn_Make(30+2*(c-560),-20,2,100,2,52,2);
			SEn_Make(390-2*(c-560),-20,2,100,3,52,2);
		}
	}
	if(c==1400)	SEn_Make(CENTER_X,-20,3,4500,38,53,9);	
	if(1600<=c&&c<1900){
		c-=1600;
		if(c%18==0){
			SEn_Make(-20,CENTER_Y-30,0,150,39,54,0);
		}
		c+=1600;
	}
	else if(1900<=c&&c<2200){
		c-=1600;
		if(c%18==0){
			SEn_Make(-20,CENTER_Y-30,0,150,39,54,0);
		}
		if(c%18==6){
			SEn_Make(440,CENTER_Y-100,1,150,39,54,1);
		}
		c+=1600;
	}
	else if(2200<=c&&c<2800){
		c-=1600;
		if(c%18==0){
			SEn_Make(-20,CENTER_Y-30,0,150,39,54,0);
		}
		if(c%18==6){
			SEn_Make(440,CENTER_Y-100,1,150,39,54,1);
		}
		if(c%18==12){
			SEn_Make(-20,CENTER_Y-170,2,150,39,54,2);
		}
		c+=1600;
	}
	if(c==3000){
		SBos_Make(500,150,1,12000,-1,4,19,29,11,30);
	}
	if(c>3000&&Boss.gage_exist==0){
		Boss.i_hanyou[5]++;
	}
	if(c<5700&&Boss.i_hanyou[5]%520==1){
			SEn_Make(CENTER_X,-20,3,5500,38,55,9);
	}
	if(c<5700&&Boss.i_hanyou[5]%520==261){
			SEn_Make(CENTER_X,-20,3,5500,38,56,9);
	}
	if(c==5900){
		Boss.i_hanyou[5] = 0;
	}
	if(c>=5900&&Boss.exist==0&&Boss.i_hanyou[6]==0){
		if(Boss.i_hanyou[5]<900){
			for(int i=0;i<7;i++){
				if(Boss.i_hanyou[5]%90==1+5*i){
					int num;
					if(Boss.i_hanyou[5]%270<90)		num = 2;
					else if(Boss.i_hanyou[5]%270<180)	num = 1;
					else					num = 0;
					SEn_Make(CENTER_X+20*(i+1),-20,num,200,40,57+get_rand(1),num);
					num = (num+1)%3;
					SEn_Make(CENTER_X-20*(i+1),-20,num,200,40,57+get_rand(1),num);
				}
			}
		}
		if(Boss.i_hanyou[5]==1050)	SEn_Make(CENTER_X,-20,3,9000,41,60,10);	
		if(Boss.i_hanyou[5]==1800)	Talk.count ++;
	}
	return;
}