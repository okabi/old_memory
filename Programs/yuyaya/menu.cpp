#include "menu.h"

bool bDemo;
int DemoNum;
int commandA;
int commandB;
int Mcount;
int Mcount2;
int Mcount3;//カーソル動かしてなかった時間
int title_carsol;
int op_count;
int op_carsol;
int sl_count;
int sl_count2;
int sl_count3;
int slp_count;
int slp_count2;
int slp_count3;
int sl_stage;
int rp_count;
int rp_count2;
int rp_count3;
int rp_scene;
int rp_carsol;
int rp_carsol2;
int rs_count;
int rs_count2;
int rs_count3;
int rs_level;
int rs_chara;
int rs_scene;
int rs_carsol;
int ne_count;
int ne_count2;
int ne_count3;
int ne_count4;
int ne_carsol;
int ne_carsol2;
int ne_scene;
int now_tate;
int now_yoko;
int now_num;//入力されている文字列番号

LOGODATA Logo[LOGO_GRAPH_NUM];
MEFDATA MEf[MEF_NUM];
MENUDATA Menu[TITLE_NUM];
YUYAYADATA Yuyaya[YUYAYA_NUM];

void MeLoad();
void MeMain();
void MeBack();
void MeTitle();
void MeReplay();
void MeDrawReplay(float y, float plus, int entry, int only);
void MeResult();
void MeOption();
void MeSelectLevel();
void MeSelectPlayer();
void MeNameEntry();
void MeDrawRanking(float y,int level, int chara, float plus,int entry);
bool MeInputName(float y, float plus, char buffer[USER_NAME_NUM], bool bInput);


void MeLoad(){
//ゲーム起動時タイトルロゴ
	bDemo = false;
	DemoNum = 0;
	commandA = 0;
	commandB = 0;
	Mcount = 0;
	Mcount2 = 0;
	Mcount3 = 0;
	title_carsol = 0;
	op_count = 0;
	op_carsol = 0;
	sl_count = 0;
	sl_count2 = 0;
	sl_count3 = 0;
	slp_count = 0;
	slp_count2 = 0;
	slp_count3 = 0;
	sl_stage = 0;
	rp_count = 0;
	rp_count2 = 0;
	rp_count3 = 0;
	rp_scene = 0;
	rp_carsol = 0;
	rp_carsol2 = 0;
	rs_count = 0;
	rs_count2 = 0;
	rs_count3 = 0;
	rs_level = 0;
	rs_chara = 0;
	rs_scene = 0;
	rs_carsol = 0;
	ne_count = 0;
	ne_count2 = 0;
	ne_count3 = 0;
	ne_count4 = 0;
	ne_scene = 0;
	ne_carsol = 0;
	ne_carsol2 = 0;
	bool flag[LOGO_GRAPH_NUM];
	for(int i=0;i<LOGO_GRAPH_NUM;i++){
		Logo[i].x = 0;
		Logo[i].y = 0;
		Logo[i].angle = 0;
		Logo[i].speed = 0;
		Logo[i].accel = 0;
		Logo[i].move_x = 0;
		Logo[i].move_y = 0;		
		flag[i] = false;
	}
	for(int i=0;i<LOGO_GRAPH_NUM;i++){
		while(1){
			int r = get_rand(LOGO_GRAPH_NUM-1);
			if(flag[r]==false){
				flag[r] = true;
				Logo[i].angle = 360.0/(float)LOGO_GRAPH_NUM*(float)r;
				break;
			}
		}
	}
	for(int i=0;i<MEF_NUM;i++){
		MEf[i].x = get_rand(640);
		MEf[i].y = get_rand(480);
		MEf[i].speed = 0.5+0.01*get_rand(50);
		MEf[i].large = 0.01*get_rand(100);	
		float angle = Radian(get_rand(360),TRUE);
		MEf[i].move_x = cos(angle);	
		MEf[i].move_y = sin(angle);
		MEf[i].count = 0;
		MEf[i].red = get_rand(255);
		MEf[i].green = get_rand(255);
		MEf[i].blue = get_rand(255);
	}
	for(int i=0;i<TITLE_NUM;i++){
		Menu[i].x = 380+pow(-1,i)*400;
		Menu[i].y = 240+30*i;
		Menu[i].speed = -pow(-1,i)*13.3;
		Menu[i].accel = -Menu[i].speed/60.0;
		Menu[i].count = 0;
	}

	return;
}

void MeMain(){
	MeBack();
	if(scene==TITLE && Mcount>=180 && Mcount2==0){
		int up,down,left,right,shot,bomb,slow,skip,pause;
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
		if(Mcount3<DEMO_TIME && (up>0 || down>0 || left>0 || right>0 || shot>0 || bomb>0 || slow>0 || skip>0 || pause>0)){
			Mcount3 = 0;
		}
		else	Mcount3++;		
	}
	else{
		Mcount3 = 0;
		bDemo = false;
	}
	if(scene==TITLE)	MeTitle();
	if(scene==REPLAY)	MeReplay();
	if(scene==RESULT)	MeResult();
	if(scene==OPTION)	MeOption();
	if(scene==SELECT_LEVEL){
		MeSelectLevel();
		MeSelectPlayer();
	}
	else if(scene==SELECT_PLAYER){
		MeSelectLevel();
		MeSelectPlayer();
	}
	if(Mcount2>0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*Mcount2);
		DrawBox(0,0,640,480,GetColor(255,255,255),TRUE);
		Mcount2--;
	}

	Mcount++;
	
	return;
}

void MeBack(){
	int black_flash=0;
	if(Mcount>=1200){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		int count = (Mcount-1200)%3500;
		int count2 = (Mcount-1200)/3500;
		if(count<170){
			DrawRotaGraphF(320,565-count,1.0,0,gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
		}
		else if(count<290){
			DrawRotaGraphF(320,395,1.0,0,gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
		}
		else if(count<460){
			DrawRotaGraphF(320,395+(count-290),1.0,0,gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
		}
		else if(count<1300){
			if(count2%2==1){
				for(int i=0;i<6;i++){
					DrawRotaGraphF(-100+(count-460),395-170*i,1.0,0,gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
					DrawRotaGraphF(740-(count-460),395-170*i,1.0,0,gMenu[MENU_GRAPH_NUM-2],TRUE,TRUE);
				}
			}
			else{
				DrawRotaGraphF(-100+(count-460),395,1.0,0,gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
			}
		}
		else if(count<1900){
			float lx = 300.0 - (count-1300)/2;
			float ly = 100.0 + 10*sin(Radian(10.0*(count-1300),TRUE));
			float time = 2.0*(count-1300);
			DrawRotaGraphF(320+lx*cos(Radian(time,TRUE)),240+ly*sin(Radian(time,TRUE)),1.0,Radian(3.0*(count-1300),TRUE),gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
		}
		else if(count<2100){
			float ly = 100.0 + 10*sin(Radian(10.0*(count-1300),TRUE));
			float time = 2.0*(count-1300);
			DrawRotaGraphF(320,240+ly*sin(Radian(time,TRUE)),1.0+0.01*(count-1900),Radian(3.0*(count-1300),TRUE),gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
		}
		else if(count<2400){
			float ly = 100.0 + 10*sin(Radian(10.0*(count-1300),TRUE));
			float time = 2.0*(count-1300);
			DrawRotaGraphF(320,240+ly*sin(Radian(time,TRUE)),3.0-0.01*(count-2100),Radian(3.0*(count-1300),TRUE),gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
		}
		else if(count<2500){
			if(count==2400){
				for(int i=0;i<YUYAYA_NUM;i++){
					float r;
					if(count2%2==0){
						Yuyaya[i].x = 320;
						Yuyaya[i].y = 480;
						r = Radian(0.01*get_rand(18000)+180,TRUE);
					}
					else{
						Yuyaya[i].x = 320;
						Yuyaya[i].y = 240;
						r = Radian(0.01*get_rand(36000),TRUE);
					}
					float speed = 5.0+0.1*get_rand(50);
					Yuyaya[i].move_x = speed*cos(r);
					Yuyaya[i].move_y = speed*sin(r);
					Yuyaya[i].accel = 0.05;
				}
			}
		}
		else if(count<3500){
			for(int i=0;i<YUYAYA_NUM;i++){
				Yuyaya[i].x += Yuyaya[i].move_x;
				Yuyaya[i].y += Yuyaya[i].move_y;
				Yuyaya[i].move_y += Yuyaya[i].accel;
				DrawRotaGraphF(Yuyaya[i].x,Yuyaya[i].y,0.8,0,gMenu[MENU_GRAPH_NUM-2],TRUE,FALSE);
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	DrawGraph(0,0,gMenuBack,TRUE);
	for(int i=0;i<MEF_NUM;i++){
		MEf[i].x += MEf[i].speed * MEf[i].move_x;
		MEf[i].y += MEf[i].speed * MEf[i].move_y;
		if(-24<MEf[i].x && MEf[i].x<664 && -24<MEf[i].y && MEf[i].y<504){
			if(MEf[i].count<50)	SetDrawBlendMode(DX_BLENDMODE_ADD,2*MEf[i].count);
			else			SetDrawBlendMode(DX_BLENDMODE_ADD,100);
			SetDrawBright(MEf[i].red,MEf[i].green,MEf[i].blue);
			DrawRotaGraphF(MEf[i].x,MEf[i].y,MEf[i].large,0,gMenu[MENU_GRAPH_NUM-1],TRUE,FALSE);
			MEf[i].count++;
		}
		else{
			MEf[i].x = get_rand(640);
			MEf[i].y = get_rand(480);
			MEf[i].speed = 0.5+0.01*get_rand(50);
			MEf[i].large = 0.01*get_rand(100);	
			float angle = Radian(get_rand(360),TRUE);
			MEf[i].move_x = cos(angle);	
			MEf[i].move_y = sin(angle);
			MEf[i].count = 0;
			MEf[i].red = get_rand(255);
			MEf[i].green = get_rand(255);
			MEf[i].blue = get_rand(255);
		}
	}
	SetDrawBright(255,255,255);

	if(Mcount<120){
		black_flash = 255;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,black_flash);
		DrawBox(0,0,640,480,0,TRUE);
		float cx = 320.0;
		float cy = 240.0;
		float lx = 300.0;
		float ly = 150.0;
		float sp = 12.0;
		float la = 4.0;
		if(Mcount<60){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*Mcount);
			lx = 400.0 - 4.0*(float)Mcount;
			ly = 200.0 - 2.0*(float)Mcount;
			la = 4.0 - 0.05*(float)Mcount;
		}
		else{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			lx = 160.0;
			ly = 80.0;
			sp = 12.0 - 0.2*(float)(Mcount-60);
		}
		for(int i=0;i<LOGO_GRAPH_NUM;i++){
			la = 1.0;
			Logo[i].angle += sp;
			Logo[i].x = cx + lx*cos(Radian(Logo[i].angle,TRUE));
			Logo[i].y = cy + ly*sin(Radian(Logo[i].angle,TRUE));
			if(i<10)	SetDrawBright(180,180,255);
			else		SetDrawBright(255,180,180);
			DrawRotaGraphF(Logo[i].x,Logo[i].y,la,0,gLogo[i],TRUE,FALSE);
		}
	}
	else if(Mcount<180){
		black_flash = 255-4.25*(Mcount-120);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,black_flash);
		DrawBox(0,0,640,480,0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		if(Mcount==120){
			for(int i=0;i<LOGO_GRAPH_NUM;i++){
				float tox,toy;
				if(i<10){
					tox = 50.0 + 32.0*i;
					toy = 70.0;
				}
				else if(i==10){
					tox = 100.0 + 20.0*(i-10);
					toy = 105.0;
				}
				else if(i<13){
					tox = 100.0 + 20.0*(i-9);
					toy = 105.0;
				}
				else if(i<16){
					tox = 100.0 + 20.0*(i-8);
					toy = 105.0;
				}
				else{
					tox = 90.0 + 20.0*(i-8);
					toy = 105.0;
				}
				float ssx = tox-Logo[i].x;
				float ssy = toy-Logo[i].y;
				float ssq = sqrt(ssx*ssx+ssy*ssy);
				Logo[i].speed = ssq/30.0;
				Logo[i].accel = Logo[i].speed / 60.0;
				Logo[i].move_x = ssx/ssq;
				Logo[i].move_y = ssy/ssq;
			}
		}
		for(int i=0;i<LOGO_GRAPH_NUM;i++){
			Logo[i].x += Logo[i].speed * Logo[i].move_x;
			Logo[i].y += Logo[i].speed * Logo[i].move_y;
			Logo[i].speed -= Logo[i].accel;
			if(i<10)	SetDrawBright(180,180,255);
			else		SetDrawBright(255,180,180);
			DrawRotaGraphF(Logo[i].x,Logo[i].y,1.0,0,gLogo[i],TRUE,FALSE);
		}
		for(int i=0;i<TITLE_NUM;i++){
			Menu[i].x += Menu[i].speed;
			Menu[i].speed += Menu[i].accel;
		}
	}
	else{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		for(int i=0;i<LOGO_GRAPH_NUM;i++){
			if(i<10)	SetDrawBright(180,180,255);
			else		SetDrawBright(255,180,180);
			DrawRotaGraphF(Logo[i].x,Logo[i].y,1.0,0,gLogo[i],TRUE,FALSE);
		}	
	}
	SetDrawBright(255,255,255);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255-black_flash);
	for(int i=0;i<TITLE_NUM;i++){
		int red = 255;
		int green = 170+80*sin(Radian(Menu[i].count+35*i,TRUE));
		int blue = 170+80*sin(Radian(Menu[i].count+35*i,TRUE));
		if((i==1&&SAVE.Extra==false) || (i==2&&SAVE.Practice==false)){
			red = 40;
			green = 40;
			blue = 60;
		}
		else if(title_carsol != i){
			red /= 2.5;
			green /= 2.5;
			blue /= 2.5;
		}
		SetDrawBright(red,green,blue);
		DrawGraphF(Menu[i].x,Menu[i].y,gMenu[i],TRUE);
		Menu[i].count++;
	}
	SetDrawBright(255,255,255);
	char message[128];
	wsprintf(message , "ver1.40a");
	DrawFormatString(0,468,GetColor(255,255,255),message);
	wsprintf(message , "2010 2011 2012 (C)opyright okabi@vinylon66. All rights reserved.");
	int size = GetDrawStringWidth(message,128);
	DrawFormatString(640-size,468,GetColor(255,255,255),message);
	
	return;
}

void MeTitle(){
	if(Mcount>=180 && Mcount2==0 && Mcount3<DEMO_TIME){
		int up,down,left,right,shot,bomb,slow,skip,pause;
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
		if(up==1 || (up>0&&up%10==0)){
			PlaySound(0);
			title_carsol = (title_carsol+TITLE_NUM-1)%TITLE_NUM;
			if(title_carsol==2 && SAVE.Practice==false)	title_carsol--;
			if(title_carsol==1 && SAVE.Extra==false)	title_carsol--;
		}
		else if(down==1 || (down>0&&down%10==0)){
			PlaySound(0);
			title_carsol = (title_carsol+TITLE_NUM+1)%TITLE_NUM;
			if(title_carsol==1 && SAVE.Extra==false)	title_carsol++;
			if(title_carsol==2 && SAVE.Practice==false)	title_carsol++;
		}
		if(shot==1){
			PlaySound(1);
			if(title_carsol==0 || title_carsol==2){
				replay_play = false;
				sl_count = 0;
				sl_count2 = 0;
				sl_count3 = 0;
				slp_count = 0;
				slp_count2 = 0;
				slp_count3 = 0;
				commandA = 0;
				commandB = 0;
				sl_stage = 0;
				if(title_carsol==2)	sl_stage = -1;
				scene = SELECT_LEVEL;
			}
			else if(title_carsol==3){
				replay_play = true;
				rp_count = 0;
				rp_count2 = 0;
				rp_count3 = 0;
				rp_scene = 0;
				rp_carsol = 0;
				rp_carsol2 = 0;
				sl_count2 = 0;
				scene = REPLAY;
			}
			else if(title_carsol==4){
				rs_count = 0;
				rs_count2 = 0;
				rs_count3 = 0;
				rs_level = 1;
				rs_chara = 0;
				rs_scene = 0;
				rs_carsol = 0;
				scene = RESULT;
			}
			else if(title_carsol==5){
				op_count = 0;
				op_carsol = 0;
				scene = OPTION;
			}
			else if(title_carsol==6)	scene = END;
		}
		else if(bomb==1){
			PlaySound(2);
			if(title_carsol!=6)	title_carsol = 6;
			else 			scene = END;
		}
	}
	if(Mcount3==DEMO_TIME){
		sl_count2 = 0;
	}
	if(Mcount3>DEMO_TIME){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*sl_count2);
		DrawBox(0,0,640,480,0,TRUE);
		MuChangeVolumeBgm(255*SAVE.Bgm*0.01*(float)(50-sl_count2)/50.0);
		if(sl_count2==50){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			int size = GetDrawStringWidth(nowloading,14);
			DrawString(640-size,480-12,nowloading,GetColor(255,255,255));			
			ScreenFlip();
			MuStopBgm();
			MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
			bDemo = true;
			replay_play = true;
			scene = GAME;
			int st_n = 0;
			for(int i=0;i<STAGE_NUM;i++){
				if(Demo[DemoNum].s_exist[i]==true){
					st_n = i;
					break;
				}
			}
			for(int i=0;i<PLAYER_NUM;i++){
				Player[i].stage = st_n;
			}
			SReplay = Demo[DemoNum];
			
			PLoad();
			DemoNum = (DemoNum+1) % DEMO_NUM;
		}
		sl_count2++;
	}	

	return;
}

void MeOption(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	if(op_count<20)	DrawBox(320-16*op_count,240-12*op_count,320+16*op_count,240+12*op_count,0,TRUE);
	else		DrawBox(0,0,640,480,0,TRUE);
	
	if(op_count>=10){
		float plus = 0;
		if(op_count<30)	plus = 0.05*pow(op_count-30,2);
		float plus2 = 0;
		if(op_count<60)	plus2 = 0.1*pow(op_count-60,2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawGraph(20-plus2,20,gTitle[0],TRUE);
		char help[128] = {'\0',};
		char tag[128] = {'\0',};
		char num[128] = {'\0',};
		
		for(int i=0;i<OP_NUM;i++){
			for(int a=0;a<128;a++){
				help[a] = '\0';
				tag[a] = '\0';
				num[a] = '\0';
			}
			if(i==0)	sprintf(tag , "SHIP");
			if(i==1)	sprintf(tag , "BOMB");
			if(i==2)	sprintf(tag , "BGM");
			if(i==3)	sprintf(tag , "SOUND");
			if(i==4)	sprintf(tag , "KEY CONFIG");
			if(i==5)	sprintf(tag , "SHOT");
			if(i==6)	sprintf(tag , "BOMB HYPER");
			if(i==7)	sprintf(tag , "SLOW LASER");
			if(i==8)	sprintf(tag , "SKIP");
			if(i==9)	sprintf(tag , "PAUSE");
			if(i==10)	sprintf(tag , "KEY DEFAULT");
			if(i==11)	sprintf(tag , "OPTION DEFAULT");
			if(i==12)	sprintf(tag , "QUIT");
			int y;
			if(i<4)		y = 100 + 20*i;
			else if(i<10)	y = 110 + 20*i;
			else if(i<12)	y = 120 + 20*i;
			else		y = 130 + 20*i;
			if(op_carsol==i)	SetDrawBright(255,255,255);
			else if(i==4)		SetDrawBright(255,150,150);
			else			SetDrawBright(120,120,120);
       	
			if(i==0)	sprintf(num , "%d", SAVE.Ship);
			else if(i==1)	sprintf(num , "%d", SAVE.Bomb);
			else if(i==2)	sprintf(num , "%3d", SAVE.Bgm);
			else if(i==3)	sprintf(num , "%3d", SAVE.Sound);
			else if(i==5)	sprintf(num , "%2d", SAVE.Key_Shot-3);
			else if(i==6)	sprintf(num , "%2d", SAVE.Key_Bomb-3);
			else if(i==7)	sprintf(num , "%2d", SAVE.Key_Slow-3);
			else if(i==8)	sprintf(num , "%2d", SAVE.Key_Skip-3);
			else if(i==9)	sprintf(num , "%2d", SAVE.Key_Pause-3);
			else		sprintf(num , "       ");
       	
			draw_string(100+pow(-1,i)*plus, y+pow(-1,i)*plus, 128, tag);
			draw_string(250-pow(-1,i)*plus, y-pow(-1,i)*plus, 128, num);
		}

		if(op_carsol==0)	sprintf(help, "初期残機を設定します（０～６）　工場設定:２");
		if(op_carsol==1)	sprintf(help, "初期ボム数を設定します（０～６）　工場設定:３");
		if(op_carsol==2)	sprintf(help, "ＢＧＭ音量を設定します（０～１００）　工場設定:１００");
		if(op_carsol==3)	sprintf(help, "効果音音量を設定します（０～１００）　工場設定:３０");
		if(op_carsol==5)	sprintf(help, "ショットキーを設定します（パッドのみ）");
		if(op_carsol==6)	sprintf(help, "ボム・ハイパーキーを設定します（パッドのみ）");
		if(op_carsol==7)	sprintf(help, "低速移動・レーザーキーを設定します（パッドのみ）");
		if(op_carsol==8)	sprintf(help, "スキップキーを設定します（パッドのみ）");
		if(op_carsol==9)	sprintf(help, "ポーズキーを設定します（パッドのみ）");
		if(op_carsol==10)	sprintf(help, "キーコンフィグを初期設定に戻します");
		if(op_carsol==11)	sprintf(help, "キーコンフィグ以外の設定を初期設定に戻します");
		if(op_carsol==12)	sprintf(help, "お帰りはこちら");

		SetDrawBright(255,255,255);
		int size = GetDrawStringWidthToHandle(help,128,default_font);
		DrawSt(320-size/2, 420, GetColor(255,255,255), 0, default_font, help);

		if(op_count>=30){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			if(up==1 || (up>0&&up%10==0)){
				PlaySound(0);
				op_carsol = (op_carsol+OP_NUM-1)%OP_NUM;
				if(op_carsol==4)	op_carsol--;
			}
			else if(down==1 || (down>0&&down%10==0)){
				PlaySound(0);
				op_carsol = (op_carsol+OP_NUM+1)%OP_NUM;
				if(op_carsol==4)	op_carsol++;
			}
			if(op_carsol<4||9<op_carsol){
				if(left==1 || (left>0&&left%10==0)){
					PlaySound(0);
					if(op_carsol==0&&SAVE.Ship>0)	SAVE.Ship--;
					if(op_carsol==1&&SAVE.Bomb>0)	SAVE.Bomb--;
					if(op_carsol==2&&SAVE.Bgm>0){
						SAVE.Bgm-=5;
						MuChangeVolumeBgm(255*SAVE.Bgm*0.01);			
					}
					if(op_carsol==3&&SAVE.Sound>0){
						SAVE.Sound-=5;
						MuChangeVolumeSound(255*SAVE.Sound*0.01);			
					}
				}
				else if(right==1 || (right>0&&right%10==0)){
					PlaySound(0);
					if(op_carsol==0&&SAVE.Ship<6)	SAVE.Ship++;
					if(op_carsol==1&&SAVE.Bomb<6)	SAVE.Bomb++;
					if(op_carsol==2&&SAVE.Bgm<100){
						SAVE.Bgm+=5;
						MuChangeVolumeBgm(255*SAVE.Bgm*0.01);			
					}
					if(op_carsol==3&&SAVE.Sound<100){
						SAVE.Sound+=5;
						MuChangeVolumeSound(255*SAVE.Sound*0.01);
					}			
				}
				if(shot==1){
					PlaySound(1);
					if(op_carsol==10){
						SAVE.Key_Shot = PAD_A;
						SAVE.Key_Bomb = PAD_B;
						SAVE.Key_Slow = PAD_C;
						SAVE.Key_Skip = PAD_X;
						SAVE.Key_Pause = PAD_START;
					}
					else if(op_carsol==11){
						SAVE.Bgm = 100;
						SAVE.Sound = 30;
						SAVE.Ship = 2;
						SAVE.Bomb = 3;
						MuChangeVolumeBgm(255*SAVE.Bgm*0.01);			
						MuChangeVolumeSound(255*SAVE.Sound*0.01);
					}
					else if(op_carsol==12)	scene = TITLE;
				}
				else if(bomb==1){
					PlaySound(2);
					if(op_carsol!=12)	op_carsol = 12;
					else 			scene = TITLE;
				}
			}
			else{
				int input = -1;
				if(c_pad[PAD_A]==1)		input = PAD_A;
				else if(c_pad[PAD_B]==1)	input = PAD_B;
				else if(c_pad[PAD_C]==1)	input = PAD_C;
				else if(c_pad[PAD_X]==1)	input = PAD_X;
				else if(c_pad[PAD_Y]==1)	input = PAD_Y;
				else if(c_pad[PAD_Z]==1)	input = PAD_Z;
				else if(c_pad[PAD_L]==1)	input = PAD_L;
				else if(c_pad[PAD_R]==1)	input = PAD_R;
				else if(c_pad[PAD_START]==1)	input = PAD_START;
				else if(c_pad[PAD_M]==1)	input = PAD_M;
				if(input!=-1){
					PlaySound(1);
					if(op_carsol==5)	SAVE.Key_Shot = input;
					if(op_carsol==6)	SAVE.Key_Bomb = input;
					if(op_carsol==7)	SAVE.Key_Slow = input;
					if(op_carsol==8)	SAVE.Key_Skip = input;
					if(op_carsol==9)	SAVE.Key_Pause = input;
				}
			}
			if(op_carsol==3&&Mcount%60==0){
				PlaySound(3);
			}
		}
	}
	SetDrawBright(255,255,255);
	
	op_count++;

	return;
}

void MeSelectLevel(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	if(sl_count<20)	DrawBox(320-16*sl_count,240-12*sl_count,320+16*sl_count,240+12*sl_count,0,TRUE);
	else		DrawBox(0,0,640,480,0,TRUE);
	
	if(sl_count>=10){
		if(sl_count3<20)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,25.5*(sl_count3-10));
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		float plus2 = 0.0;
		if(sl_count3<60)	plus2 = 0.1*pow(sl_count3-60,2);
		DrawGraph(20.0-plus2,20.0,gTitle[1],TRUE);
		float plus = 0.0;
		if(sl_count3<40)	plus = 0.05*pow(sl_count3-40,2);
		for(int i=0;i<4;i++){
			if(SAVE.Level==i)	SetDrawBright(255,255,255);
			else			SetDrawBright(60,60,60);
                	DrawRotaGraphF(320.0+pow(-1,i)*plus, 150.0+70*i, 1.0, 0, gLevel[i], TRUE, FALSE);
		}
		SetDrawBright(255,255,255);
		if(title_carsol==2){
			int gx,gy;
			GetGraphSize(gLevel[0], &gx, &gy);
			char message[8];
			if(sl_stage>=0)	sprintf(message, "STAGE %d\0", sl_stage+1);
			else		sprintf(message, "TUTORIAL\0");
			draw_string(320+gx/2+20+plus, 150.0+70*SAVE.Level, 8, message); 
		}
		if(sl_count3>=40&&scene==SELECT_LEVEL&&sl_count2==0){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			if(slow>0){
				switch(commandA){
					case 0:	if(up==1)	commandA++;
						else if(down==1 || left==1 || right==1)	commandA = 0;
						break;
					case 1:	if(up==1)	commandA++;
						else if(down==1 || left==1 || right==1)	commandA = 0;
						break;
					case 2:	if(left==1)	commandA++;
						else if(down==1 || up==1 || right==1)	commandA = 0;
						break;
					case 3:	if(down==1)	commandA++;
						else if(left==1 || up==1 || right==1)	commandA = 0;
						break;
					case 4:	if(right==1)	commandA++;
						else if(left==1 || up==1 || down==1)	commandA = 0;
						break;
					default:if(up==1 || down==1 || left==1 || right==1)	commandA = 0;
				}
				switch(commandB){
					case 0:	if(up==1)	commandB++;
						else if(down==1 || left==1 || right==1)	commandB = 0;
						break;
					case 1:	if(up==1)	commandB++;
						else if(down==1 || left==1 || right==1)	commandB = 0;
						break;
					case 2:	if(down==1)	commandB++;
						else if(left==1 || up==1 || right==1)	commandB = 0;
						break;
					case 3:	if(down==1)	commandB++;
						else if(left==1 || up==1 || right==1)	commandB = 0;
						break;
					case 4:	if(left==1)	commandB++;
						else if(down==1 || up==1 || right==1)	commandB = 0;
						break;
					case 5:	if(right==1)	commandB++;
						else if(left==1 || up==1 || down==1)	commandB = 0;
						break;
					case 6:	if(left==1)	commandB++;
						else if(down==1 || up==1 || right==1)	commandB = 0;
						break;
					case 7:	if(right==1)	commandB++;
						else if(left==1 || up==1 || down==1)	commandB = 0;
						break;
					default:if(up==1 || down==1 || left==1 || right==1)	commandB = 0;
				}
			}
			else{
				commandA = 0;
				commandB = 0;
				if(up==1 || (up>0&&up%10==0)){
					PlaySound(0);
					SAVE.Level = (SAVE.Level+SL_NUM-1)%SL_NUM;
				}
				else if(down==1 || (down>0&&down%10==0)){
					PlaySound(0);
					SAVE.Level = (SAVE.Level+SL_NUM+1)%SL_NUM;
				}
				if(title_carsol==2){
					const int STG_NUM = SAVE.Stage;
					if(left==1 || (left>0&&left%10==0)){
						PlaySound(0);
						if(sl_stage==0)		sl_stage = -1;
						else if(sl_stage==-1)	sl_stage = STG_NUM-1;
						else		sl_stage = (sl_stage+STG_NUM-1)%STG_NUM;
					}
					else if(right==1 || (right>0&&right%10==0)){
						PlaySound(0);
						if(sl_stage==STG_NUM-1)	sl_stage = -1;
						else if(sl_stage==-1)	sl_stage = 0;
						else	sl_stage = (sl_stage+STG_NUM+1)%STG_NUM;
					}
				}
			}
			if(shot==1){
				if(commandA==5){
					PlaySound(24);
					SAVE.Baby = true;
				}
				else if(commandB==8){
					PlaySound(27);
					SAVE.Impossible = true;
				}
				else			PlaySound(1);
				if(title_carsol==2 && sl_stage==-1){
					SAVE.Chara = 0;
					sl_count2 = 1;
				}
				else{
					if(sl_count3>60)	sl_count3 = 60;
					slp_count = 0;
					slp_count2 = 0;
					slp_count3 = 0;
					scene = SELECT_PLAYER;
				}
			}
			else if(bomb==1){
				PlaySound(2);
				scene = TITLE;
			}
		}
		if(scene==SELECT_LEVEL && sl_count2>0){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*sl_count2);
			DrawBox(0,0,640,480,0,TRUE);
			MuChangeVolumeBgm(255*SAVE.Bgm*0.01*(float)(50-sl_count2)/50.0);
			if(sl_count2==50){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int size = GetDrawStringWidth(nowloading,14);
				DrawString(640-size,480-12,nowloading,GetColor(255,255,255));			
				ScreenFlip();
				MuStopBgm();
				MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
				scene = GAME;
				for(int i=0;i<PLAYER_NUM;i++){
					if(title_carsol==0)	Player[i].stage = 0;
					else			Player[i].stage = sl_stage;
					if(commandA==5)	Player[i].level = BABY;
					else if(commandB==8)	Player[i].level = IMPOSSIBLE;
					else		Player[i].level = SAVE.Level;
					Player[i].chara = SAVE.Chara;
				}
				
				PLoad();
			}
			sl_count2++;
		}
	}
	SetDrawBright(255,255,255);
	
	sl_count++;
	if(scene==SELECT_LEVEL)	sl_count3++;
	else{
		if(sl_count3>0)	sl_count3--;
        }

	return;
}

void MeSelectPlayer(){
	if(slp_count<10)SetDrawBlendMode(DX_BLENDMODE_ALPHA,25.5*slp_count);
	else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	if(slp_count>0){
		float plus = 0.0;
		if(slp_count2<40){
			plus = 0.05*pow(slp_count2-40,2);
		}
		for(int i=0;i<CHARA_NUM;i++){
			if(SAVE.Chara==i)	continue;
			SetDrawBright(60,60,60);
			int gx,gy;
			GetGraphSize(gLevel[5+i],&gx,&gy);
       	        	DrawRotaGraphF(150.0+80*i, 480-gy/2+pow(-1,i)*plus, 1.0, 0, gLevel[5+i], TRUE, FALSE);
		}
		if(scene==SELECT_PLAYER){
			int i = SAVE.Chara;
			int gx,gy;
			GetGraphSize(gLevel[5+i],&gx,&gy);
			SetDrawBright(255,255,255);
       	        	DrawRotaGraphF(150.0+80*i, 480-gy/2+pow(-1,i)*plus, 1.0, 0, gLevel[5+i], TRUE, FALSE);
			float plus2 = 0.0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
			if(slp_count3<20){
				plus2 = 0.1*pow(slp_count3-20,2);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*slp_count3);
			}
			float x = 340.0;
			if(i/3==1)	x = 20.0;
			float y = 150.0;
			DrawGraphF(x+pow(-1,i/3)*plus, y, gLevel[11+i], TRUE);
			SetDrawBright(255,150,150);
			DrawGraphF(x+10+pow(-1,i/3)*plus, y+20, gLevel[17+i], TRUE);
			if(i/3==0)	SetDrawBright(255,255,150);
			else		SetDrawBright(255,150,255);
			DrawGraphF(x+20+pow(-1,i/3)*plus, y+60, gLevel[23+i/3], TRUE);
			SetDrawBright(255,255,255);
			DrawGraphF(x+25+pow(-1,i/3)*plus, y+80, gLevel[25+i/3], TRUE);
			if(i/3==1){
				DrawGraphF(x+25+pow(-1,i/3)*plus, y+130, gLevel[27], TRUE);
				y += 50;
			}
			DrawGraphF(x+40+pow(-1,i/3)*plus, y+130, gLevel[28], TRUE);
			DrawGraphF(x+120+pow(-1,i/3)*plus, y+130, gLevel[29+i%3], TRUE);
			DrawGraphF(x+40+pow(-1,i/3)*plus, y+155, gLevel[32], TRUE);
			DrawGraphF(x+120+pow(-1,i/3)*plus, y+155, gLevel[33+i%3], TRUE);
		}
		SetDrawBright(255,255,255);
		if(scene==SELECT_PLAYER && slp_count2>=40 && sl_count2==0){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			if(left==1 || (left>0&&left%10==0)){
				PlaySound(0);
				SAVE.Chara = (SAVE.Chara+SLP_NUM-1)%SLP_NUM;
				slp_count3 = 0;
			}
			else if(right==1 || (right>0&&right%10==0)){
				PlaySound(0);
				SAVE.Chara = (SAVE.Chara+SLP_NUM+1)%SLP_NUM;
				slp_count3 = 0;
			}
			if(shot==1){
				PlaySound(1);
				sl_count2 = 1;
			}
			else if(bomb==1){
				PlaySound(2);
				if(slp_count>10)	slp_count = 10;
				if(slp_count2>60)	slp_count2 = 60;
				if(slp_count3>20)	slp_count3 = 20;
				sl_count3 = 10;
				scene = SELECT_LEVEL;
			}
		}

		SetDrawBright(255,255,255);
	
		if(slp_count<10)SetDrawBlendMode(DX_BLENDMODE_ALPHA,25.5*slp_count);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		float plus2 = 0.0;
		if(slp_count2<60)	plus2 = 0.1*pow(slp_count2-60,2);
		DrawGraph(20.0-plus2,20.0,gTitle[4],TRUE);

		if(scene==SELECT_PLAYER && sl_count2>0){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*sl_count2);
			DrawBox(0,0,640,480,0,TRUE);
			MuChangeVolumeBgm(255*SAVE.Bgm*0.01*(float)(50-sl_count2)/50.0);
			if(sl_count2==50){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int size = GetDrawStringWidth(nowloading,14);
				DrawString(640-size,480-12,nowloading,GetColor(255,255,255));			
				ScreenFlip();
				MuStopBgm();
				MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
				scene = GAME;
				for(int i=0;i<PLAYER_NUM;i++){
					if(title_carsol==0)	Player[i].stage = 0;
					else			Player[i].stage = sl_stage;
					if(commandA==5)	Player[i].level = BABY;
					else if(commandB==8)	Player[i].level = IMPOSSIBLE;
					else		Player[i].level = SAVE.Level;
					Player[i].chara = SAVE.Chara;
				}
				
				PLoad();
			}
			sl_count2++;
		}
	}
	
	SetDrawBright(255,255,255);
	
	if(scene==SELECT_PLAYER){
		slp_count++;
		slp_count2++;
		slp_count3++;
	}
	else{
		if(slp_count>0)		slp_count--;
		if(slp_count2>0)	slp_count2--;
		if(slp_count3>0)	slp_count3--;
	}

	return;
}

void MeReplay(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	if(rp_count<20)	DrawBox(320-16*rp_count,240-12*rp_count,320+16*rp_count,240+12*rp_count,0,TRUE);
	else		DrawBox(0,0,640,480,0,TRUE);
	
	if(rp_count>=20){
		if(rp_count<40)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(rp_count-20));
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		float plus2 = 0.0;
		if(rp_count<60)	plus2 = 0.1*pow(rp_count-60,2);
		DrawGraph(20.0-plus2,20.0,gTitle[2],TRUE);

		if(rp_scene==0){
			float plus = 0;
			if(rp_count2<60)	plus = 0.2*pow(60-rp_count2,2);
			MeDrawReplay(70, plus, rp_carsol);		
		}
		else{
			MeDrawReplay(200, 0, rp_carsol, rp_carsol);
			if(Replay[rp_carsol].level<=IMPOSSIBLE){
				for(int i=0;i<STAGE_NUM;i++){
					char message[128];
					for(int j=0;j<128;j++)	message[j] = '\0';
					if(Replay[rp_carsol].s_exist[i]==true){
						if(Replay[rp_carsol].score[i][0]==0)	sprintf(message, "STAGE%d      %7d%d", i+1, Replay[rp_carsol].score[i][1], Replay[rp_carsol].con_num);
						else					sprintf(message, "STAGE%d %5d%07d%d", i+1, Replay[rp_carsol].score[i][0], Replay[rp_carsol].score[i][1], Replay[rp_carsol].con_num);
					}
					else	sprintf(message, "STAGE%d _____________", i+1);
					if(rp_carsol2==i)	SetDrawBright(255,255,50);
					else			SetDrawBright(255,255,255);
					draw_string(150, 240+20*i, 128, message);
				}
			}
		}
		SetDrawBright(255,255,255);
		rp_count2++;

		if(sl_count2>0){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,5.1*sl_count2);
			DrawBox(0,0,640,480,0,TRUE);
			MuChangeVolumeBgm(255*SAVE.Bgm*0.01*(float)(50-sl_count2)/50.0);
			if(sl_count2==50){
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
				int size = GetDrawStringWidth(nowloading,14);
				DrawString(640-size,480-12,nowloading,GetColor(255,255,255));			
				ScreenFlip();
				MuStopBgm();
				MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
				scene = GAME;
				for(int i=0;i<PLAYER_NUM;i++){
					Player[i].stage = rp_carsol2;
				}
 				SReplay = Replay[rp_carsol];
				PLoad();
			}
			sl_count2++;
		}

		if(rp_count2>=60 && sl_count2==0){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			
			if(up==1 || (up>0&&up%10==0)){
				PlaySound(0);
				if(rp_scene==0)	rp_carsol = (rp_carsol+REPLAY_NUM-1)%REPLAY_NUM;
				else		rp_carsol2 = (rp_carsol2+STAGE_NUM-1)%STAGE_NUM;
			}
			else if(down==1 || (down>0&&down%10==0)){
				PlaySound(0);
				if(rp_scene==0)	rp_carsol = (rp_carsol+REPLAY_NUM+1)%REPLAY_NUM;
				else		rp_carsol2 = (rp_carsol2+STAGE_NUM+1)%STAGE_NUM;
			}

			if(shot==1){
				if(rp_scene==0){
					if(Replay[rp_carsol].exist==true){
						PlaySound(1);
						rp_scene = 1;
						rp_carsol2 = 0;
					}
					else	PlaySound(28);
				}
				else{
					if(Replay[rp_carsol].s_exist[rp_carsol2]==true){
						PlaySound(1);
						sl_count2 = 1;
					}
					else	PlaySound(28);
				}
			}
			else if(bomb==1){
				PlaySound(2);
				if(rp_scene==0)	scene = TITLE;
				else		rp_scene = 0;
			}
		}
	}
	SetDrawBright(255,255,255);
	
	rp_count++;

	return;
}

void MeDrawReplay(float y, float plus, int entry, int only){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);

	if(only>-1){
		const int LENGTH = 128;
		char message[LENGTH];
		for(int j=0;j<LENGTH;j++)	message[j] = '\0';
		char rank[5];
		sprintf(rank, "NO%2d\0", only+1);
		int l;
		if(Replay[only].exist==true){
			char stage[4];
			if(Replay[only].stage==STAGE_NUM+1)	sprintf(stage, "ALL\0");
			else					sprintf(stage, "ST%d\0", Replay[only].stage);
			char chara[4];
			if(Replay[only].chara==0)	sprintf(chara, "REM\0");
			else if(Replay[only].chara==1)	sprintf(chara, "ZHT\0");
			else if(Replay[only].chara==2)	sprintf(chara, "PAI\0");
			else if(Replay[only].chara==3)	sprintf(chara, "GJR\0");
			else if(Replay[only].chara==4)	sprintf(chara, "YYY\0");
			else if(Replay[only].chara==5)	sprintf(chara, "ARM\0");
			char rank2;
			if(Replay[only].rank>=900)		rank2 = 'S';
			else if(Replay[only].rank>=600)	rank2 = 'A';
			else if(Replay[only].rank>=300)	rank2 = 'B';
			else				rank2 = 'C';
			char level[3];
			if(Replay[only].level==EASY)		sprintf(level,"EA\0");
			else if(Replay[only].level==NORMAL)	sprintf(level,"NO\0");
			else if(Replay[only].level==HARD)	sprintf(level,"HA\0");
			else if(Replay[only].level==LUNATIC)	sprintf(level,"LU\0");
			else if(Replay[only].level==BABY)	sprintf(level,"BA\0");
			else if(Replay[only].level==IMPOSSIBLE)	sprintf(level,"IM\0");
			else if(Replay[only].level==EXTRA)	sprintf(level,"EX\0");
			int max = 0;
			for(int j=STAGE_NUM-1;j>0;j--){
				if((Replay[only].score[j][0]>0 || Replay[only].score[j][1]>0) && Replay[only].s_exist[j]==true){
					max = j;
					break;
				}
			}
			if(Replay[only].score[max][0]>0)	sprintf(message, "%4s %-9s %5d%07d%d  %c  %3s %2s %3s %02d/%2d/%2d", rank, Replay[only].name, Replay[only].score[max][0], Replay[only].score[max][1], Replay[only].con_num, rank2, chara, level, stage, Replay[only].year, Replay[only].month, Replay[only].date);
			else				sprintf(message, "%4s %-9s      %7d%d  %c  %3s %2s %3s %02d/%2d/%2d", rank, Replay[only].name, Replay[only].score[max][1], Replay[only].con_num, rank2, chara, level, stage, Replay[only].year, Replay[only].month, Replay[only].date);
			l = get_length(LENGTH,message);
			if(only==entry)    SetDrawBright(255,255,50);
			else		SetDrawBright(255, 255, 255);
		}
		else{
			sprintf(message, "%4s ________  _____________  _  ___ __ ST_ ____/__/__", rank);
			l = get_length(LENGTH,message);
			if(only==entry)    SetDrawBright(255,255,50);
			else		SetDrawBright(255, 255, 255);
		}
		draw_string(320-11.0*l/2.0+plus, y, LENGTH, message);
	
		return;
	}
	
	for(int i=0;i<REPLAY_NUM;i++){
		const int LENGTH = 128;
		char message[LENGTH];
		for(int j=0;j<LENGTH;j++)	message[j] = '\0';
		char rank[5];
		sprintf(rank, "NO%2d\0", i+1);
		int l;
		if(Replay[i].exist==true){
			char stage[4];
			if(Replay[i].stage==STAGE_NUM+1)	sprintf(stage, "ALL\0");
			else					sprintf(stage, "ST%d\0", Replay[i].stage);
			char chara[4];
			if(Replay[i].chara==0)		sprintf(chara, "REM\0");
			else if(Replay[i].chara==1)	sprintf(chara, "ZHT\0");
			else if(Replay[i].chara==2)	sprintf(chara, "PAI\0");
			else if(Replay[i].chara==3)	sprintf(chara, "GJR\0");
			else if(Replay[i].chara==4)	sprintf(chara, "YYY\0");
			else if(Replay[i].chara==5)	sprintf(chara, "ARM\0");
			char rank2;
			if(Replay[i].rank>=900)		rank2 = 'S';
			else if(Replay[i].rank>=600)	rank2 = 'A';
			else if(Replay[i].rank>=300)	rank2 = 'B';
			else				rank2 = 'C';
			char level[3];
			if(Replay[i].level==EASY)		sprintf(level,"EA\0");
			else if(Replay[i].level==NORMAL)	sprintf(level,"NO\0");
			else if(Replay[i].level==HARD)		sprintf(level,"HA\0");
			else if(Replay[i].level==LUNATIC)	sprintf(level,"LU\0");
			else if(Replay[i].level==BABY)		sprintf(level,"BA\0");
			else if(Replay[i].level==IMPOSSIBLE)	sprintf(level,"IM\0");
			else if(Replay[i].level==EXTRA)		sprintf(level,"EX\0");
			int max = 0;
			for(int j=STAGE_NUM-1;j>0;j--){
				if((Replay[i].score[j][0]>0 || Replay[i].score[j][1]>0) && Replay[i].s_exist[j]==true){
					max = j;
					break;
				}
			}
			if(Replay[i].score[max][0]>0)	sprintf(message, "%4s %-9s %5d%07d%d  %c  %3s %2s %3s %02d/%2d/%2d", rank, Replay[i].name, Replay[i].score[max][0], Replay[i].score[max][1], Replay[i].con_num, rank2, chara, level, stage, Replay[i].year, Replay[i].month, Replay[i].date);
			else				sprintf(message, "%4s %-9s      %7d%d  %c  %3s %2s %3s %02d/%2d/%2d", rank, Replay[i].name, Replay[i].score[max][1], Replay[i].con_num, rank2, chara, level, stage, Replay[i].year, Replay[i].month, Replay[i].date);
			l = get_length(LENGTH,message);
			if(i==entry)    SetDrawBright(255,255,50);
			else		SetDrawBright(255, 255, 255);
		}
		else{
			sprintf(message, "%4s ________  _____________  _  ___ __ ST_ ____/__/__", rank);
			l = get_length(LENGTH,message);
			if(i==entry)    SetDrawBright(255,255,50);
			else		SetDrawBright(255, 255, 255);
		}
		draw_string(320-11.0*l/2.0+plus, y+20*i, LENGTH, message);
	}

	return;
}

void MeResult(){
	if(rs_count>=20){
		float plus = 0;
		if(rs_count3<60)	plus = 0.2*pow(60-rs_count3,2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		DrawRotaGraphF(320+plus, 240, 1.0, 0, gLevel[5+rs_chara], TRUE, FALSE);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,180);
	if(rs_count<20)	DrawBox(320-16*rs_count,240-12*rs_count,320+16*rs_count,240+12*rs_count,0,TRUE);
	else		DrawBox(0,0,640,480,0,TRUE);
	
	if(c_key[KEY_INPUT_D]==1){
		const int MENUM = 256;
		char message[MENUM];
		char message2[MENUM];
		for(int i=0;i<MENUM;i++)	message[i] = '\0';
		for(int i=0;i<MENUM;i++)	message2[i] = '\0';
		FILE *fp;
		fp = fopen("score.txt", "w");
		fputs("=========================================================================\n",fp);
		fputs("\t\tA So Tallow   HighScore\n",fp);
		DATEDATA D;
		GetDateTime(&D);
		sprintf(message, "\t\t\t\t\tTimeStamp:%d/%02d/%02d %d:%02d:%02d\n", D.Year, D.Mon, D.Day, D.Hour, D.Min, D.Sec);
		fputs(message,fp);
		for(int i=0;i<MENUM;i++)	message[i] = '\0';
		fputs("=========================================================================\n\n",fp);
		fputs("※このファイルの中身を変更しても、内部情報は変更されません\n\n",fp);
		int hour = SAVE.PlayTime[LEVEL_NUM]/3600;
		int min = (SAVE.PlayTime[LEVEL_NUM]-hour*3600)/60;
		int sec = SAVE.PlayTime[LEVEL_NUM]-hour*3600-min*60;
		sprintf(message, "プレイタイム %d:%02d:%02d\n\n\n\n\n", hour, min, sec);
		fputs(message,fp);
		for(int i=0;i<MENUM;i++)	message[i] = '\0';

		for(int i=0;i<LEVEL_NUM;i++){
			if(i==BABY && SAVE.Baby==false)	continue;
			else if(i==IMPOSSIBLE && SAVE.Impossible==false)	continue;
			else if(i==EXTRA && SAVE.Extra==false)	continue;
			if(i==EASY)		fputs("EASY  Score Ranking\n\n\n",fp);
			else if(i==NORMAL)	fputs("NORMAL  Score Ranking\n\n\n",fp);
			else if(i==HARD)	fputs("HARD  Score Ranking\n\n\n",fp);
			else if(i==LUNATIC)	fputs("LUNATIC  Score Ranking\n\n\n",fp);
			else if(i==BABY)	fputs("BABY  Score Ranking\n\n\n",fp);
			else if(i==IMPOSSIBLE)	fputs("IMPOSSIBLE  Score Ranking\n\n\n",fp);
			else if(i==EXTRA)	fputs("EXTRA  Score Ranking\n\n\n",fp);
			for(int k=0;k<CHARA_NUM;k++){
				if(k==0)		fputs("博麗 霊夢(ボムスタイル)\n\n",fp);
				else if(k==1)		fputs("蒸発(ボムスタイル)\n\n",fp);
				else if(k==2)		fputs("π(ボムスタイル)\n\n",fp);
				else if(k==3)		fputs("ゴジラ(パワースタイル)\n\n",fp);
				else if(k==4)		fputs("電車○ きもも(パワースタイル)\n\n",fp);
				else if(k==5)		fputs("あらま～(パワースタイル)\n\n",fp);
				for(int j=0;j<SCORE_NUM;j++){
					if(SAVE.Score[i][k][j].gameper==0)	continue;
					sprintf(message, "\tNo.%d  %s\n", j+1, SAVE.Score[i][k][j].name);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					if(SAVE.Score[i][k][j].score[0]==0)	sprintf(message, "\t\tスコア: %d%d\n", SAVE.Score[i][k][j].score[1], SAVE.Score[i][k][j].con_num);
					else					sprintf(message, "\t\tスコア: %d%07d%d\n", SAVE.Score[i][k][j].score[0], SAVE.Score[i][k][j].score[1], SAVE.Score[i][k][j].con_num);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\tゲーム進行度: %.1f%%\n", (float)SAVE.Score[i][k][j].gameper/10.0);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t処理落ち率: %.1f%%\n", (float)SAVE.Score[i][k][j].slowrate/10.0);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\tコンティニュー回数: %d\n", SAVE.Score[i][k][j].con_num);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\tミス回数: %d\n", SAVE.Score[i][k][j].miss_num);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\tボム回数: %d\n", SAVE.Score[i][k][j].bomb_num);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\tハイパー回数: %d\n", SAVE.Score[i][k][j].hyper_num);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\tスペルカードボーナス回数: %d\n", SAVE.Score[i][k][j].spell_num);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					if(SAVE.Score[i][k][j].rank[STAGE_NUM]>=900)	sprintf(message2, "S");
					else if(SAVE.Score[i][k][j].rank[STAGE_NUM]>=600)	sprintf(message2, "A");
					else if(SAVE.Score[i][k][j].rank[STAGE_NUM]>=300)	sprintf(message2, "B");
					else	sprintf(message2, "C");
					sprintf(message, "\t\tランク: %s (%.1f点)\n", message2, (float)SAVE.Score[i][k][j].rank[STAGE_NUM]/10.0);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					for(int i=0;i<MENUM;i++)	message2[i] = '\0';
					int ye = SAVE.Score[i][k][j].year[0];
					int mo = SAVE.Score[i][k][j].month[0];
					int da = SAVE.Score[i][k][j].date[0];
					int ho = SAVE.Score[i][k][j].hour[0];
					int mi = SAVE.Score[i][k][j].minute[0];
					int se = SAVE.Score[i][k][j].second[0];
					sprintf(message, "\t\tプレイ開始: %d/%02d/%02d  %d:%02d:%02d\n", ye, mo, da, ho, mi, se);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					ye = SAVE.Score[i][k][j].year[1];
					mo = SAVE.Score[i][k][j].month[1];
					da = SAVE.Score[i][k][j].date[1];
					ho = SAVE.Score[i][k][j].hour[1];
					mi = SAVE.Score[i][k][j].minute[1];
					se = SAVE.Score[i][k][j].second[1];
					sprintf(message, "\t\tプレイ終了: %d/%02d/%02d  %d:%02d:%02d\n", ye, mo, da, ho, mi, se);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					ho = SAVE.Score[i][k][j].Rplaytime[STAGE_NUM]/216000;
					mi = (SAVE.Score[i][k][j].Rplaytime[STAGE_NUM]-ho*216000)/3600;
					se = (SAVE.Score[i][k][j].Rplaytime[STAGE_NUM]-ho*216000-mi*3600)/60;
					if(ho>0)	sprintf(message, "\t\tリアルプレイ時間: %d時間%d分%d秒\n", ho, mi, se);
					else		sprintf(message, "\t\tリアルプレイ時間: %d分%d秒\n", mi, se);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					ho = SAVE.Score[i][k][j].Vplaytime[STAGE_NUM]/216000;
					mi = (SAVE.Score[i][k][j].Vplaytime[STAGE_NUM]-ho*216000)/3600;
					se = (SAVE.Score[i][k][j].Vplaytime[STAGE_NUM]-ho*216000-mi*3600)/60;
					if(ho>0)	sprintf(message, "\t\tバーチャルプレイ時間: %d時間%d分%d秒\n", ho, mi, se);
					else		sprintf(message, "\t\tバーチャルプレイ時間: %d分%d秒\n", mi, se);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t敵機撃破数: %d\n", SAVE.Score[i][k][j].enemy_num[STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t敵弾撃破数: %d\n", SAVE.Score[i][k][j].enemyshot_num[STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t星アイテム（小）取得数: %d\n", SAVE.Score[i][k][j].item_num[0][STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t星アイテム（中）取得数: %d\n", SAVE.Score[i][k][j].item_num[1][STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t星アイテム（大）取得数: %d\n", SAVE.Score[i][k][j].item_num[2][STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t最大Ｐ素点: %d\n", SAVE.Score[i][k][j].max_soten[STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t最大ヒット: %d\n", SAVE.Score[i][k][j].max_hit[STAGE_NUM]);
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					sprintf(message, "\t\t取得スペルカード一覧（名前と取得点）\n");
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					for(int a=0,b=0;a<SPELL_NUM&&b<SAVE.Score[i][k][j].spell_num;a++){
						if(SAVE.Score[i][k][j].score_spcard[a]>0){
							sprintf(message, "\t\t\t%s (%d)\n", Spell[a].name, SAVE.Score[i][k][j].score_spcard[a]);
							fputs(message,fp);
							for(int i=0;i<MENUM;i++)	message[i] = '\0';
							b++;
						}
					}
					sprintf(message, "\t\tステージ情報\n");
					fputs(message,fp);
					for(int i=0;i<MENUM;i++)	message[i] = '\0';
					for(int a=0;a<STAGE_NUM;a++){
						if(SAVE.Score[i][k][j].Vplaytime[a]==0)	continue;
						sprintf(message, "\t\t\tStage %d\n", a+1);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						if(SAVE.Score[i][k][j].stage_allscore[a][0]==0)	sprintf(message, "\t\t\t\t総取得スコア: %d0\n", SAVE.Score[i][k][j].stage_allscore[a][1]);
						else						sprintf(message, "\t\t\t\t総取得スコア: %d%07d0\n", SAVE.Score[i][k][j].stage_allscore[a][0], SAVE.Score[i][k][j].stage_allscore[a][1]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						if(SAVE.Score[i][k][j].stage_score[a][0][0]==0)	sprintf(message, "\t\t\t\t取得スコア（道中前半）: %d0\n", SAVE.Score[i][k][j].stage_score[a][0][1]);
						else						sprintf(message, "\t\t\t\t取得スコア（道中前半）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][0][0], SAVE.Score[i][k][j].stage_score[a][0][1]);
						fputs(message,fp);
						if(a==4){
							for(int i=0;i<MENUM;i++)	message[i] = '\0';
							if(SAVE.Score[i][k][j].stage_score[a][2][0]==0)	sprintf(message, "\t\t\t\t取得スコア（中ボス１）: %d0\n", SAVE.Score[i][k][j].stage_score[a][2][1]);
							else						sprintf(message, "\t\t\t\t取得スコア（中ボス１）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][2][0], SAVE.Score[i][k][j].stage_score[a][2][1]);
							fputs(message,fp);					
							for(int i=0;i<MENUM;i++)	message[i] = '\0';
							if(SAVE.Score[i][k][j].stage_score[a][2][0]==0)	sprintf(message, "\t\t\t\t取得スコア（道中中盤）: %d0\n", SAVE.Score[i][k][j].stage_score[a][4][1]);
							else						sprintf(message, "\t\t\t\t取得スコア（道中中盤）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][4][0], SAVE.Score[i][k][j].stage_score[a][4][1]);
							fputs(message,fp);					
							for(int i=0;i<MENUM;i++)	message[i] = '\0';
							if(SAVE.Score[i][k][j].stage_score[a][2][0]==0)	sprintf(message, "\t\t\t\t取得スコア（中ボス２）: %d0\n", SAVE.Score[i][k][j].stage_score[a][5][1]);
							else						sprintf(message, "\t\t\t\t取得スコア（中ボス２）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][5][0], SAVE.Score[i][k][j].stage_score[a][5][1]);
							fputs(message,fp);					
						}
						else{
							for(int i=0;i<MENUM;i++)	message[i] = '\0';
							if(SAVE.Score[i][k][j].stage_score[a][1][0]==0)	sprintf(message, "\t\t\t\t取得スコア（中ボス）: %d0\n", SAVE.Score[i][k][j].stage_score[a][1][1]);
							else						sprintf(message, "\t\t\t\t取得スコア（中ボス）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][1][0], SAVE.Score[i][k][j].stage_score[a][1][1]);
							fputs(message,fp);
						}
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						if(SAVE.Score[i][k][j].stage_score[a][2][0]==0)	sprintf(message, "\t\t\t\t取得スコア（道中後半）: %d0\n", SAVE.Score[i][k][j].stage_score[a][2][1]);
						else						sprintf(message, "\t\t\t\t取得スコア（道中後半）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][2][0], SAVE.Score[i][k][j].stage_score[a][2][1]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						if(SAVE.Score[i][k][j].stage_score[a][3][0]==0)	sprintf(message, "\t\t\t\t取得スコア（ボス）: %d0\n", SAVE.Score[i][k][j].stage_score[a][3][1]);
						else						sprintf(message, "\t\t\t\t取得スコア（ボス）: %d%07d0\n", SAVE.Score[i][k][j].stage_score[a][3][0], SAVE.Score[i][k][j].stage_score[a][3][1]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						float rate = 100.0*(float)SAVE.Score[i][k][j].Rplaytime[a]/(float)SAVE.Score[i][k][j].Vplaytime[a]-100.0;
						if(rate>=100)	rate = 99.9;
						else if(rate<0)	rate = 0;
						sprintf(message, "\t\t\t\t処理落ち率: %.1f%%\n", rate);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						if(SAVE.Score[i][k][j].rank[a]>=900)	sprintf(message2, "S");
						else if(SAVE.Score[i][k][j].rank[a]>=600)	sprintf(message2, "A");
						else if(SAVE.Score[i][k][j].rank[a]>=300)	sprintf(message2, "B");
						else	sprintf(message2, "C");
						sprintf(message, "\t\t\t\tランク: %s (%.1f点)\n", message2, (float)SAVE.Score[i][k][j].rank[a]/10.0);
						fputs(message,fp);
						/*
						if(SAVE.Score[i][k][j].root[a]==0)	sprintf(message2, "表");
						else	sprintf(message2, "裏");
						sprintf(message, "\t\t\t\t進行ルート: %s\n", message2, (float)SAVE.Score[i][k][j].rank[a]/10.0);
						fputs(message,fp);
						*/
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						for(int i=0;i<MENUM;i++)	message2[i] = '\0';
						mi = (SAVE.Score[i][k][j].Rplaytime[a])/3600;
						se = (SAVE.Score[i][k][j].Rplaytime[a]-mi*3600)/60;
						sprintf(message, "\t\t\t\tリアルプレイ時間: %d分%d秒\n", mi, se);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						mi = (SAVE.Score[i][k][j].Vplaytime[a])/3600;
						se = (SAVE.Score[i][k][j].Vplaytime[a]-mi*3600)/60;
						sprintf(message, "\t\t\t\tバーチャルプレイ時間: %d分%d秒\n", mi, se);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t敵機撃破数: %d\n", SAVE.Score[i][k][j].enemy_num[a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t敵弾撃破数: %d\n", SAVE.Score[i][k][j].enemyshot_num[a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t星アイテム（小）取得数: %d\n", SAVE.Score[i][k][j].item_num[0][a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t星アイテム（中）取得数: %d\n", SAVE.Score[i][k][j].item_num[1][a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t星アイテム（大）取得数: %d\n", SAVE.Score[i][k][j].item_num[2][a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t最大Ｐ素点: %d\n", SAVE.Score[i][k][j].max_soten[a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
						sprintf(message, "\t\t\t\t最大ヒット: %d\n", SAVE.Score[i][k][j].max_hit[a]);
						fputs(message,fp);
						for(int i=0;i<MENUM;i++)	message[i] = '\0';
					}
					fputs("\n",fp);
				}
				fputs("\n\n",fp);
			}
		}
				
		fclose(fp);
	}
	
	if(rs_count>=20){
		if(rs_count<40)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,12.75*(rs_count-20));
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		float plus2 = 0.0;
		if(rs_count<60)	plus2 = 0.1*pow(rs_count-60,2);
		DrawGraph(20.0-plus2,20.0,gTitle[3],TRUE);

		if(rs_scene==0){
			float plus = 0;
			if(rs_count2<60)	plus = 0.2*pow(60-rs_count2,2);
			MeDrawRanking(100, rs_level, rs_chara, plus, -1);		
		}
		else{
			const int mnum = 256;
			char message[4][mnum];
			for(int j=0;j<4;j++){
				for(int i=0;i<mnum;i++)	message[j][i] = '\0';
			}
			for(int i=rs_carsol*10;i<(rs_carsol+1)*10&&i<SPELL_NUM;i++){
				char level[3];
				if(Spell[i].level==EASY)		sprintf(level,"EA\0");
				else if(Spell[i].level==NORMAL)		sprintf(level,"NO\0");
				else if(Spell[i].level==HARD)		sprintf(level,"HA\0");
				else if(Spell[i].level==LUNATIC)	sprintf(level,"LU\0");
				else if(Spell[i].level==BABY)		sprintf(level,"BA\0");
				else if(Spell[i].level==IMPOSSIBLE)	sprintf(level,"IM\0");
				else if(Spell[i].level==EXTRA)		sprintf(level,"EX\0");
				if(SAVE.SpChallenge[rs_chara][i]>0){
					sprintf(message[0], "No.%-3d", i+1);
					sprintf(message[1], "%s", Spell[i].name);
					sprintf(message[2], "(%2s)", level);
					sprintf(message[3], "%3d/%-3d", SAVE.SpGet[rs_chara][i], SAVE.SpChallenge[rs_chara][i]);
				}
				else{
					sprintf(message[0], "No.%-3d", i+1);
					sprintf(message[1], "----------------------------------------");
					sprintf(message[2], "(--)");
					sprintf(message[3], "---/---");
				}
				if(SAVE.SpGet[rs_chara][i]>0)	SetDrawBright(255,255,255);
				else				SetDrawBright(100,100,100);
				for(int j=0;j<4;j++){
					int size = GetDrawStringWidthToHandle(message[j],256,default_font);
					if(j==0)	DrawSt(30, 100+20*(i-rs_carsol*10), GetColor(255,255,255), 0, default_font, message[j]);
					else if(j==1)	DrawSt(100, 100+20*(i-rs_carsol*10), GetColor(255,255,255), 0, default_font, message[j]);
					else if(j==2)	DrawSt(510, 100+20*(i-rs_carsol*10), GetColor(255,255,255), 0, default_font, message[j]);
					else if(j==3)	DrawSt(560, 100+20*(i-rs_carsol*10), GetColor(255,255,255), 0, default_font, message[j]);
				}
			}
		}
		rs_count2++;
		rs_count3++;

		SetDrawBright(255,255,255);
		char time[64];
		for(int i=0;i<64;i++)	time[i] = '\0';
		int hour = SAVE.PlayTime[LEVEL_NUM]/3600;
		int min = (SAVE.PlayTime[LEVEL_NUM]-hour*3600)/60;
		int sec = SAVE.PlayTime[LEVEL_NUM]-hour*3600-min*60;
		sprintf(time, "プレイ時間　%d:%02d:%02d", hour, min, sec);
		int size = GetDrawStringWidthToHandle(time,64,default_font);
		DrawSt(320-size/2, 360, GetColor(255,255,255), 0, default_font, time);
		for(int i=0;i<3;i++){
			if(i==0){
				if(rs_scene==0)	DrawSt(150, 400+20*i, GetColor(255,255,255), 0, default_font, "←→ キャラ変更　　↑↓ 難易度変更");
				else		DrawSt(150, 400+20*i, GetColor(255,255,255), 0, default_font, "←→ キャラ変更　　↑↓ 番号変更");
			}
			else if(i==1){
				if(rs_scene==0)	DrawSt(150, 400+20*i, GetColor(255,255,255), 0, default_font, "Shot 御札戦歴を見る");
				else		DrawSt(150, 400+20*i, GetColor(255,255,255), 0, default_font, "Shot ハイスコアを見る");
			}
			else if(i==2){
				DrawSt(150, 400+20*i, GetColor(255,255,255), 0, default_font, "Bomb 戻る");
			}
		}

		if(rs_count>=40){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			const int RS_NUM1 = LEVEL_NUM;
			const int RS_NUM4 = CHARA_NUM;
			const int RS_NUM2 = 1 + SPELL_NUM/10;
			const int RS_NUM3 = 2;
			
			if(left==1 || (left>0&&left%10==0)){
				PlaySound(0);
				rs_count2 = 0;
				rs_count3 = 0;
				rs_chara = (rs_chara+RS_NUM4-1)%RS_NUM4;
			}
			else if(right==1 || (right>0&&right%10==0)){
				PlaySound(0);
				rs_count2 = 0;
				rs_count3 = 0;
				rs_chara = (rs_chara+RS_NUM4+1)%RS_NUM4;
			}
			if(up==1 || (up>0&&up%10==0)){
				PlaySound(0);
				if(rs_scene==0){
					rs_count2 = 0;
					while(1){
						rs_level = (rs_level+RS_NUM1-1)%RS_NUM1;
						if(rs_level==BABY && SAVE.Baby==false){}
						else if(rs_level==IMPOSSIBLE && SAVE.Impossible==false){}
						else if(rs_level==EXTRA && SAVE.Extra==false){}
						else	break;
					}
				}
				else		rs_carsol = (rs_carsol+RS_NUM2-1)%RS_NUM2;
			}
			else if(down==1 || (down>0&&down%10==0)){
				PlaySound(0);
				if(rs_scene==0){
					rs_count2 = 0;
					while(1){
						rs_level = (rs_level+RS_NUM1+1)%RS_NUM1;
						if(rs_level==BABY && SAVE.Baby==false){}
						else if(rs_level==IMPOSSIBLE && SAVE.Impossible==false){}
						else if(rs_level==EXTRA && SAVE.Extra==false){}
						else	break;
					}
				}
				else		rs_carsol = (rs_carsol+RS_NUM2+1)%RS_NUM2;
			}

			if(shot==1){
				PlaySound(1);
				rs_scene = (rs_scene+RS_NUM3+1)%RS_NUM3;
			}
			else if(bomb==1){
				PlaySound(2);
				scene = TITLE;
			}
		}
	}
	SetDrawBright(255,255,255);
	
	rs_count++;

	return;
}

void MeNameEntry(){
	SetDrawBright(255,255,255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	DrawGraph(0, 0, gMenuBack2, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	DrawBox(0,0,640,480,0,TRUE);
	
	//↓スコアエントリー
	SScore.score[0] = Player[0].score[0];
	SScore.score[1] = Player[0].score[1];
	SScore.con_num = Player[0].cont_num;
	int entry = -1;
	for(int i=0;i<SCORE_NUM;i++){
		if(	SScore.score[0]>SAVE.Score[Player[0].level][Player[0].chara][i].score[0] ||
			(SScore.score[0]==SAVE.Score[Player[0].level][Player[0].chara][i].score[0] && SScore.score[1]>SAVE.Score[Player[0].level][Player[0].chara][i].score[1]) || 
			(SScore.score[0]==SAVE.Score[Player[0].level][Player[0].chara][i].score[0] && SScore.score[1]==SAVE.Score[Player[0].level][Player[0].chara][i].score[1] && SScore.con_num>=SAVE.Score[Player[0].level][Player[0].chara][i].con_num)){ 
				entry = i;
				break;
		} 
	}
	//↓スコア確認
	if(ne_scene==0){
		if(title_carsol==2){
			ne_scene = 1;
			ne_count2 = 0;
			ne_count3 = 0;
			ne_scene = 2;
			ne_carsol = 0;		
			return;
		}
		else if(!(SAVE.Ship==2&&SAVE.Bomb==3)&&Player[0].level!=IMPOSSIBLE){
			ne_scene = 1;
			ne_count2 = 0;
			return;
		}
		float plus = 0;
		if(ne_count<60)	plus = 0.2*pow(60-ne_count,2);

		if(ne_count2==0){
			if(ne_count==0){
				if(entry!=-1){
					for(int i=SCORE_NUM-2;i>=entry;i--){
						SAVE.Score[Player[0].level][Player[0].chara][i+1] = SAVE.Score[Player[0].level][Player[0].chara][i];
					}
					SAVE.Score[Player[0].level][Player[0].chara][entry] = SScore;
				}
				now_tate = 0;
				now_yoko = 0;
				now_num = get_length(USER_NAME_NUM, SAVE.LastName);
			}
			
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
       	
			bool bEnd = false;
			if(entry!=-1){
				bool bInput = true;
				if(ne_count<60)	bInput = false;
				bEnd = MeInputName(300, plus, SAVE.Score[Player[0].level][Player[0].chara][entry].name, bInput);
			}
			if((entry==-1&&ne_count>=60&&(shot==1||pause==1)) || (entry!=-1&&bEnd==true)){
				ne_count = 60;
				ne_count2 = 1;
			}
			
			ne_count++;
		}
		else{
			ne_count--;
			if(ne_count==0){
				ne_scene = 1;
				ne_count2 = 0;
			}
		}
		MeDrawRanking(50, Player[0].level, Player[0].chara, plus, entry);
	}
	//↑スコア確認
	//↓あなたの戦跡
	else if(ne_scene==1){
		if(ne_count2<60)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*ne_count2);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		float x = 50;
		float y = 50;
		DrawGraphF(x, y, gPauseG[9], TRUE);
		y += 30;
		for(int i=0;i<10;i++){
			int gx,gy;
			GetGraphSize(gPauseG[10+i], &gx, &gy);
			DrawGraphF(x+194-gx, y+20*i, gPauseG[10+i], TRUE);
			float x2 = x + 220;
			switch(i){
				case 0:
					if(Player[0].level==EASY)		draw_string(x2, y+20*i, 5, "EASY\0");
					else if(Player[0].level==NORMAL)	draw_string(x2, y+20*i, 7, "NORMAL\0");
					else if(Player[0].level==HARD)		draw_string(x2, y+20*i, 5, "HARD\0");
					else if(Player[0].level==LUNATIC)	draw_string(x2, y+20*i, 8, "LUNATIC\0");
					else if(Player[0].level==BABY)		draw_string(x2, y+20*i, 5, "BABY\0");
					else if(Player[0].level==IMPOSSIBLE)	draw_string(x2, y+20*i, 11, "IMPOSSIBLE\0");
					else if(Player[0].level==EXTRA)		draw_string(x2, y+20*i, 6, "EXTRA\0");
					break;
				case 1:
					if(Player[0].score[0]==0){
						if(Player[0].score[1]!=0)	draw_score(x2+11*5, y+20*i, Player[0].score[1], 7, false);
						draw_score(x2+11*12, y+20*i, Player[0].cont_num, 1, true);
					}
					else{
						draw_score(x2, y+20*i, Player[0].score[0], 5, false);
						draw_score(x2+11*5, y+20*i, Player[0].score[1], 7, true);
						draw_score(x2+11*12, y+20*i, Player[0].cont_num, 1, true);
					}
					break;
				case 2:
					if(1){
						int num = SScore.gameper/10;
						int keta = draw_score(x2, y+20*i, num, 0, false);
						if(keta==0)	keta = 1;
						int num2 = SScore.gameper-num*10;
						DrawGraphF(x2+11*keta, y+20*i, gPauseG[20], TRUE);
						draw_score(x2+11*keta+10, y+20*i, num2, 0, false);
						DrawGraphF(x2+11*(keta+1)+10, y+20*i, gPauseG[21], TRUE);
					}
					break;
				case 3:
					if(1){
						int num = SScore.slowrate/10;
						int keta = draw_score(x2, y+20*i, num, 0, false);
						if(keta==0)	keta = 1;
						int num2 = SScore.slowrate-num*10;
						DrawGraphF(x2+11*keta, y+20*i, gPauseG[20], TRUE);
						draw_score(x2+11*keta+10, y+20*i, num2, 1, false);
						DrawGraphF(x2+11*(keta+1)+10, y+20*i, gPauseG[21], TRUE);
					}
					break;
				case 4:
					draw_score(x2, y+20*i, SScore.con_num, 0, false);
					break;
				case 5:
					draw_score(x2, y+20*i, SScore.miss_num, 0, false);
					break;
				case 6:
					draw_score(x2, y+20*i, SScore.bomb_num, 0, false);
					break;
				case 7:
					draw_score(x2, y+20*i, SScore.hyper_num, 0, false);
					break;
				case 8:
					draw_score(x2, y+20*i, SScore.spell_num, 0, false);
					break;
				case 9:
					if(SScore.rank[STAGE_NUM]>=900)		DrawGraphF(x2, y+20*i, gPauseG[22], TRUE);
					else if(SScore.rank[STAGE_NUM]>=600)	DrawGraphF(x2, y+20*i, gPauseG[23], TRUE);
					else if(SScore.rank[STAGE_NUM]>=300)	DrawGraphF(x2, y+20*i, gPauseG[24], TRUE);
					else					DrawGraphF(x2, y+20*i, gPauseG[25], TRUE);
					break;
			}
		}

		if(ne_count2>60 && ne_count3==0){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			if(shot==1 || pause==1){
				ne_count2 = 60;
				ne_count3 = 1;
			}
		}
		if(ne_count3==0)	ne_count2++;
		if(ne_count3>0){
			if(ne_count2==0){
				ne_count3 = 0;
				ne_scene = 2;
				ne_carsol = 0;		
			}
			ne_count2--;
		}
	}
	//↑あなたの戦跡
	//↓リプレイ保存しますか？
	else if(ne_scene==2){
		if(ne_count3<60)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,4.25*ne_count3);
		else			SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		int function;
		if(SScore.con_num>0){
			function = 0;
			DrawRotaGraphF(320, 230, 1.0, 0, gPauseG[27], TRUE, FALSE);
			DrawRotaGraphF(320, 250, 1.0, 0, gPauseG[29], TRUE, FALSE);
		}
		else if(Player[0].level!=IMPOSSIBLE && SScore.slowrate>=500){
			function = 1;
			DrawRotaGraphF(320, 230, 1.0, 0, gPauseG[28], TRUE, FALSE);
			DrawRotaGraphF(320, 250, 1.0, 0, gPauseG[29], TRUE, FALSE);
		}
		else{
			function = 2;
			DrawRotaGraphF(320, 230, 1.0, 0, gPauseG[26], TRUE, FALSE);
			for(int i=0;i<2;i++){
				if(ne_carsol==i)	SetDrawBright(255,255,255);
				else			SetDrawBright(50,50,50);
				DrawGraphF(250, 260+25*i, gPauseG[5+i], TRUE);
			}
			SetDrawBright(255,255,255);
			if(ne_count3>=60){
				int up,down,left,right,shot,bomb,slow,skip,pause;
				GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
				int CARSOL_NUM = 2;
				if(up==1 || (up>0&&up%10==0)){
					PlaySound(0);
					ne_carsol = (ne_carsol+CARSOL_NUM-1)%CARSOL_NUM;
				}
				else if(down==1 || (down>0&&down%10==0)){
					PlaySound(0);
					ne_carsol = (ne_carsol+CARSOL_NUM+1)%CARSOL_NUM;
				}
				if(shot==1 || pause==1){
					if(ne_carsol==0){
						PlaySound(1);
						now_tate = 0;
						now_yoko = 0;
						now_num = get_length(USER_NAME_NUM, SAVE.LastName);
						ne_carsol2 = 0;
						ne_count4 = 0;
						ne_scene = 3;
					}
					else if(ne_carsol==1){
						MuPlayBgm(0);
						scene = TITLE;
					}
				}
				else if(bomb==1){
					PlaySound(2);
					ne_carsol = 1;
				}
			}
		}
		if(function<2 && ne_count3>=60){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			if(shot==1 || pause==1){
				MuPlayBgm(0);
				scene = TITLE;
			}
		}

		ne_count3++;	
	}
	//↑リプレイ保存しますか？
	//↓リプレイ保存するよー
	else if(ne_scene==3){
		float plus = 0;
		if(ne_count4<60)	plus = 0.2*pow(60-ne_count4,2);
		MeDrawReplay(70, plus, ne_carsol2);
		if(ne_count4>=60){
			int up,down,left,right,shot,bomb,slow,skip,pause;
			GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
			const int CARSOL_NUM = REPLAY_NUM;
			if(up==1 || (up>0&&up%10==0)){
				PlaySound(0);
				ne_carsol2 = (ne_carsol2+CARSOL_NUM-1)%CARSOL_NUM;
			}
			else if(down==1 || (down>0&&down%10==0)){
				PlaySound(0);
				ne_carsol2 = (ne_carsol2+CARSOL_NUM+1)%CARSOL_NUM;
			}
			if(shot==1 || pause==1){
				PlaySound(1);
				now_tate = 0;
				now_yoko = 0;
				now_num = get_length(USER_NAME_NUM, SAVE.LastName);
				ne_scene = 4;
				for(int i=0;i<USER_NAME_NUM;i++){
					SReplay.name[i] = SAVE.LastName[i]; 
				}
				RSave(ne_carsol2,false);
			}
			else if(bomb==1){
				PlaySound(2);
				ne_count3 = 0;
				ne_scene = 2;
				ne_carsol = 0;		
			}
		}
		
		ne_count4++;
		
	}
	else if(ne_scene==4){
		MeDrawReplay(240, 0, ne_carsol2, ne_carsol2);

		bool bEnd = MeInputName(300, 0, Replay[ne_carsol2].name, true);
		if(bEnd==true){
			for(int i=0;i<USER_NAME_NUM;i++){
				SReplay.name[i] = SAVE.LastName[i]; 
			}
			RSave(ne_carsol2,true);
			MuPlayBgm(0);
			scene = TITLE;
		}
	}
	//↑リプレイ保存するよー
	SetDrawBright(255,255,255);

	return;
}

void MeDrawRanking(float y,int level, int chara, float plus,int entry){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);

	const int ILEVEL = level;
	const int ICHARA = chara;
	char le[12];
	for(int i=0;i<12;i++)	le[i] = '\0';
	if(ILEVEL==EASY){
		sprintf(le, "EASY");
		SetDrawBright(50,255,50);
	}
	else if(ILEVEL==NORMAL){
		sprintf(le, "NORMAL");
		SetDrawBright(50,50,255);
	}
	else if(ILEVEL==HARD){
		sprintf(le, "HARD");
		SetDrawBright(255,50,50);
	}
	else if(ILEVEL==LUNATIC){
		sprintf(le, "LUNATIC");
		SetDrawBright(255,50,255);
	}
	else if(ILEVEL==BABY){
		sprintf(le, "BABY");
		SetDrawBright(255,255,150);
	}
	else if(ILEVEL==IMPOSSIBLE){
		sprintf(le, "IMPOSSIBLE");
		SetDrawBright(100,10,100);
	}
	else if(ILEVEL==EXTRA){
		sprintf(le, "EXTRA");
		SetDrawBright(255,255,50);
	}
	int lel = get_length(12,le);
	draw_string(50+plus, y, 12, le);
	SetDrawBright(255,255,255);
	draw_string(50+11*(lel+1)+plus, y, 20, "MODE  SCORE RANKING\0");	
	for(int i=0;i<SCORE_NUM;i++){
		const int LENGTH = 256;
		char message[LENGTH];
		for(int j=0;j<LENGTH;j++)	message[j] = '\0';
		char stag[8];
		int st = SAVE.Score[ILEVEL][ICHARA][i].end_stage;
		if(st==STAGE_NUM+1)	sprintf(stag, "ALL\0");
		else			sprintf(stag, "ST%d\0", st);
		//draw_string(0, 20*i, 8, stag);
		char rank[8];
		if(i+1==1)	sprintf(rank, "%2dst\0", i+1);
		else if(i+1==2)	sprintf(rank, "%2dnd\0", i+1);
		else if(i+1==3)	sprintf(rank, "%2drd\0", i+1);
		else		sprintf(rank, "%2dth\0", i+1);
		char rank2;
		if(SAVE.Score[ILEVEL][ICHARA][i].rank[STAGE_NUM]>=900)	rank2 = 'S';
		else if(SAVE.Score[ILEVEL][ICHARA][i].rank[STAGE_NUM]>=600)	rank2 = 'A';
		else if(SAVE.Score[ILEVEL][ICHARA][i].rank[STAGE_NUM]>=300)	rank2 = 'B';
		else							rank2 = 'C';
		if(SAVE.Score[ILEVEL][ICHARA][i].score[0]>0)	sprintf(message, "%3s %-9s %5d%07d%d  %c  %3s %02d/%2d/%2d", rank, SAVE.Score[ILEVEL][ICHARA][i].name, SAVE.Score[ILEVEL][ICHARA][i].score[0], SAVE.Score[ILEVEL][ICHARA][i].score[1], SAVE.Score[ILEVEL][ICHARA][i].con_num, rank2, stag, SAVE.Score[ILEVEL][ICHARA][i].year[1], SAVE.Score[ILEVEL][ICHARA][i].month[1], SAVE.Score[ILEVEL][ICHARA][i].date[1]);
		else					sprintf(message, "%3s %-9s      %7d%d  %c  %3s %02d/%2d/%2d", rank, SAVE.Score[ILEVEL][ICHARA][i].name, SAVE.Score[ILEVEL][ICHARA][i].score[1], SAVE.Score[ILEVEL][ICHARA][i].con_num, rank2, stag, SAVE.Score[ILEVEL][ICHARA][i].year[1], SAVE.Score[ILEVEL][ICHARA][i].month[1], SAVE.Score[ILEVEL][ICHARA][i].date[1]);
		int l = get_length(LENGTH,message);
		if(i==entry)    SetDrawBright(255,255,50);
		else		SetDrawBright(255-(float)i*255.0/(float)SCORE_NUM, 255-(float)i*255.0/(float)SCORE_NUM, 255);
		draw_string(320-11.0*l/2.0+plus, y+30+20*i, LENGTH, message);
	}

	return;
}

bool MeInputName(float y, float plus, char buffer[USER_NAME_NUM], bool bInput){
//trueが返ってきたら、入力終了の合図
	if(now_num>=USER_NAME_NUM){
		now_num = USER_NAME_NUM;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		
	int size = 11*10+9*9;//横の長さ
	float x = 320-size/2;
	int now_inp;
	if(now_tate==0)		now_inp = now_yoko;
	else if(now_tate==1)	now_inp = 10+now_yoko;
	else if(now_tate==2)	now_inp = 20+now_yoko;
	else if(now_tate==3)	now_inp = 26+now_yoko;
	else if(now_tate==4)	now_inp = 36+now_yoko;
	else	now_inp = -1;//END
	

	for(int i=0;i<5;i++){
		for(int j=0;j<10;j++){
			int num;
			if(i==0)	num = j;
			else if(i==1)	num = 10+j;
			else if(i==2)	num = 20+j;
			else if(i==3)	num = 26+j;
			else if(i==4)	num = 36+j;
			if(now_inp==num)	SetDrawBright(255,255,10);
			else			SetDrawBright(255,255,255);
			if(i==0 || i==1 || i==3){
				DrawGraphF(x+20*j+plus, y+20*i, gAscii[num], TRUE);
			}
			else if(i==2){
				if(j<6)	DrawGraphF(x+20*j+plus, y+20*i, gAscii[num], TRUE);
				else	break;
			}
			else if(i==4){
				if(j<9)	DrawGraphF(x+20*j+plus, y+20*i, gAscii[num], TRUE);
				else	break;
			}
		}
	}
	if(now_inp==-1)	SetDrawBright(255,255,10);
	else		SetDrawBright(255,255,255);
	draw_string(320-11*3/2+plus, y+20*5, 4, "END\0");

	
	if(bInput==true){
		int up,down,left,right,shot,bomb,slow,skip,pause;
		GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
       	
		const int TATE_NUM = 6;
		const int YOKO_NUM = 10;
		if(up==1 || (up>0&&up%10==0)){
			PlaySound(0);
			now_tate = (now_tate+TATE_NUM-1)%TATE_NUM;
			if(now_tate==2 && now_yoko>5)	now_tate--;
			if(now_tate==4 && now_yoko>8)	now_tate--;
		}
		else if(down==1 || (down>0&&down%10==0)){
			PlaySound(0);
			now_tate = (now_tate+TATE_NUM+1)%TATE_NUM;
			if(now_tate==2 && now_yoko>5)	now_tate++;
			if(now_tate==4 && now_yoko>8)	now_tate++;
		}
		if(left==1 || (left>0&&left%10==0)){
			PlaySound(0);
			now_yoko = (now_yoko+YOKO_NUM-1)%YOKO_NUM;
			if(now_tate==2 && now_yoko>5)	now_yoko = 5;
			if(now_tate==4 && now_yoko>8)	now_yoko = 8;
		}
		else if(right==1 || (right>0&&right%10==0)){
			PlaySound(0);
			now_yoko = (now_yoko+YOKO_NUM+1)%YOKO_NUM;
			if(now_tate==2 && now_yoko>5)	now_yoko = 0;
			if(now_tate==4 && now_yoko>8)	now_yoko = 0;
		}
		
		if(shot==1){
			PlaySound(1);
			if(now_tate==0)		now_inp = now_yoko;
			else if(now_tate==1)	now_inp = 10+now_yoko;
			else if(now_tate==2)	now_inp = 20+now_yoko;
			else if(now_tate==3)	now_inp = 26+now_yoko;
			else if(now_tate==4)	now_inp = 36+now_yoko;
			else	now_inp = -1;//END
			if(now_inp==-1){
				for(int i=0;i<USER_NAME_NUM;i++)	SAVE.LastName[i] = buffer[i];
				return true;
			}
			else{
				if(now_num==USER_NAME_NUM)	now_num--;
				char input;
				if(now_inp<26)	input = now_inp+65;
				else if(now_inp<36)	input = now_inp+22;
				else if(now_inp==36)	input = 33;
				else if(now_inp==37)	input = 63;
				else if(now_inp==38)	input = 64;
				else if(now_inp==39)	input = 92;
				else if(now_inp==40)	input = 43;
				else if(now_inp==41)	input = 45;
				else if(now_inp==42)	input = 42;
				else if(now_inp==43)	input = 47;
				else if(now_inp==44)	input = 95;
				buffer[now_num] = input;
				now_num++;
				if(now_num==USER_NAME_NUM)	now_tate = 5;
			}
		}
		else if(bomb==1){
			PlaySound(2);
			if(now_num>0){
				buffer[now_num-1] = '\0';
				now_num--;
			}
		}
		else if(pause==1){
			PlaySound(2);
			now_tate = 5;
		}
	}

	return false;
}