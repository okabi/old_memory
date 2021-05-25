//------------------------------------------------------------------------------
//
//	���q�ɏ������_���[�@�` A So Tallow.	10.12.10~
//                       
//------------------------------------------------------------------------------

//	�S�ʁ`�T�ʐ���
//	�d�w����

#include "DxLib.h"
#include "extern.h"
#include "graph.h"
#include "menu.h"
#include "pshot.h"
#include "enemy.h"
#include "boss.h"
#include "effect.h"
#include "talk.h"

void Debug();
void Stage0();
void Stage1();
void Stage2();
void Stage3();
void Stage4();
void Stage5();

void starts(){
//�N�����̃t���X�N���[�����[�h�ύX
        int flag;
        flag=MessageBox(
                NULL ,
                TEXT("���q�ɏ������_���[�I") ,
                TEXT("�������Y") , 
                MB_YESNO | MB_ICONQUESTION );
        if(flag==IDNO){
                ChangeWindowMode( TRUE );
	}
	return;
}

void Load(){
	SLoad();
	MuLoad();
	GLoad();
	MeLoad();
	TLoad();
	SpLoad();
	PLoad();
	replay_play = false;
	replay_play_num = 0;
	Player[0].chara = 0;
	scene = TITLE;
	MuChangeVolumeBgm(255*SAVE.Bgm*0.01);
	MuChangeVolumeSound(255*SAVE.Sound*0.01);
	MuPlayBgm(0);
	
	return;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
        SetWindowText("���q�ɏ������_���[�@�` A So Tallow.�@ver1.40a");        
	SetWindowIconID(101);
	starts();
        //ChangeWindowMode( TRUE );
        if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//�������Ɨ���ʉ�
        Load();

	do{
		ClearDrawScreen();
		CheckPushKey();
		GetInput(NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,true);
		
		LOOP = 1;
		//���f�o�b�O
		if(scene==GAME && bDemo==false /*&& replay_play==true*/ && (c_key[KEY_INPUT_LCONTROL]>0||c_pad[SAVE.Key_Skip]>0) && bTalk==false && Pcount==0 && Ccount==0 && c_key[KEY_INPUT_ESCAPE]==0 && c_pad[SAVE.Key_Pause]==0){
			LOOP = 10;
		}
		for(Sloop=0;Sloop<LOOP;Sloop++){
			switch(scene){
				case GAME:	
						if(Pcount==0){
							if(Player[0].stage==1)		Stage1();
							else if(Player[0].stage==2)	Stage2();
							else if(Player[0].stage==3)	Stage3();
							else if(Player[0].stage==4)	Stage4();
							else if(Player[0].stage==5)	Stage5();
						}
						Smain();
						if(Pcount==0){
							if(Player[0].stage==0)		Stage0();
						}
						Mcount = 180;
						Mcount2 = 50;
						break;
				case TITLE:	MeMain();	break;
				case REPLAY:	MeMain();	break;
				case RESULT:	MeMain();	break;
				case OPTION:	MeMain();	break;
				case SELECT_LEVEL:	MeMain();	break;
				case SELECT_PLAYER:	MeMain();	break;
				case NAMEENTRY:	MeNameEntry();	break;
			}
		
			SoundEffect();
		}
		SnapShot();
		if(scene==GAME)	Fps();
		Debug();
		SCheckPlayTime();
		ScreenFlip();
	}while(scene!=END&&ProcessMessage()==0&&!(c_key[KEY_INPUT_F4]>0&&(c_key[KEY_INPUT_LALT]>0||c_key[KEY_INPUT_RALT]>0)));

	SSave();
        DxLib_End();
        return 0 ;              // �\�t�g�̏I��
}

void Debug(){
	static bool muteki = false;
	list<BOSSDATA>::iterator it = Boss.begin();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	SetDrawBright(255,255,255);
	if(c_key[KEY_INPUT_D]==1){
		muteki = (muteki+1)%2;
	}
	if(muteki==true)	Player[0].muteki_count = 12;
	if(c_key[KEY_INPUT_B]==1){
		(*it).life = 0;
		(*it).death_count = -1;
	}
	if(c_key[KEY_INPUT_H]==1)	add_gage(MAX_GAGE);
	SAVE.Stage = STAGE_NUM;

	/*
	list<BOSSDATA>::iterator it = Boss.begin();
	DrawFormatString(20,400,GetColor(255,255,255),"life");
	DrawFormatString(60,400,GetColor(255,255,255),"%d",(*it).life);
	DrawFormatString(20,410,GetColor(255,255,255),"efn");
	DrawFormatString(60,410,GetColor(255,255,255),"%d",Effect.size());
	DrawFormatString(20,420,GetColor(255,255,255),"en");
	DrawFormatString(60,420,GetColor(255,255,255),"%d",Enemy.size());
	DrawFormatString(20,430,GetColor(255,255,255),"esn",EShot.size());
	DrawFormatString(60,430,GetColor(255,255,255),"%d",EShot.size());
	DrawFormatString(20,440,GetColor(255,255,255),"mc",Player[0].muteki_count);
	DrawFormatString(60,440,GetColor(255,255,255),"%d",Player[0].muteki_count);
	DrawFormatString(20,450,GetColor(255,255,255),"rs",rand_seed);
	DrawFormatString(60,450,GetColor(255,255,255),"%d",rand_seed);
	*/
	//DrawFormatString(20,460,GetColor(255,255,255),"sc",Scount);
	//DrawFormatString(60,460,GetColor(255,255,255),"%d",Scount);	
	/*
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	SetDrawBright(255,255,255);
	DrawFormatString(20,50,GetColor(255,255,255),"score:%d%07d%d",Player[0].score[0],Player[0].score[1],Player[0].cont_num);
	if(c_key[KEY_INPUT_Z]==1)	add_score(10);
	if(c_key[KEY_INPUT_X]==1)	add_score(1000);
	if(c_key[KEY_INPUT_C]==1)	add_score(100000);
	if(c_key[KEY_INPUT_V]==1)	add_score(10000000);
	if(c_key[KEY_INPUT_B]==1)	add_score(1000000000);
	*/

	return;
}

void Stage0(){
	int up,down,left,right,shot,bomb,slow,skip,pause;
	GetInput(&up,&down,&left,&right,&shot,&bomb,&slow,&skip,&pause);
	static int level = 0;
	static int BAcount = 0;
	const int TATE = 10;
	const int YOKO = 64;
	static int count = 0;
	char message[TATE][YOKO];
	if(Scount<=1){
		level = 0;
		BAcount = 0;
		count = 0;
	}
	for(int i=0;i<TATE;i++){
		for(int j=0;j<YOKO;j++){
			message[i][j] = '\0';
		}
	}
	
	if(level==0){
		if(Scount>=180 && level==0 && BAcount==0){
			PlaySound(5);
			BAcount = 1;
		}
	}
	else if(level==1){
		sprintf(message[0], "Shot(Z)�Œe�������܂��B");
		sprintf(message[1], "�������ςȂ��ŘA�˂��܂��B");
		if(shot>180 && slow==0){
			PlaySound(5);
			level = 2;
			Eshot = 0;
		}
	}
	else if(level==2){
		sprintf(message[0], "Shot(Z)+Slow(��Shift)��");
		sprintf(message[1], "���[�U�[�������܂��B");
		sprintf(message[2], "�V���b�g��荂�З͂ł��B");
		sprintf(message[4], "���[�U�[���˒��͎��@���͂�");
		sprintf(message[5], "�I�[�����o���Ă��܂��B");
		sprintf(message[6], "�傫�ȍU���͂�����܂��B");
		sprintf(message[8], "�ᑬ�ړ����͓����蔻�肪");
		sprintf(message[9], "���@�̒��S�ɕ\������܂��B");
		if(shot>180 && slow>180){
			PlaySound(5);
			level = 3;
		}
	}
	else if(level==3){
		sprintf(message[0], "�G��|���Ă݂܂��傤�B");
		sprintf(message[1], "�G��|���ƁA�R���{�Q�[�W��");
		sprintf(message[2], "�}�b�N�X�ɂȂ�܂��B");
		sprintf(message[3], "�R���{�Q�[�W��؂炳����");
		sprintf(message[4], "�G��|���ƃR���{�ɂȂ�A");
		sprintf(message[5], "�傫�ȃ{�[�i�X�_�𓾂܂��B");
		if(Player[0].total_hit>70){
			PlaySound(5);
			level = 4;
		}
	}
	else if(level==4){
		sprintf(message[0], "���X�ɑ����Ă���̂́A");
		sprintf(message[1], "�n�C�p�[�Q�[�W�ł��B");
		sprintf(message[2], "�G��|������A���[�U�[��");
		sprintf(message[3], "�I�[���𓖂Ă���A�n�C�p�[");
		sprintf(message[4], "�A�C�e�����擾�����肷���");
		sprintf(message[5], "�Q�[�W���������܂��B");
		sprintf(message[6], "�R���{��؂炷�ƃQ�[�W��");
		sprintf(message[7], "�������܂��B");
		sprintf(message[8], "���^������Bomb(X)�������ƁA");
		sprintf(message[9], "�n�C�p�[�J�E���^�[�ɁI");
		if(Player[0].hyper_count>0){
			PlaySound(5);
			level = 5;
		}
	}
	else if(level==5){
		sprintf(message[0], "�n�C�p�[�J�E���^�[���́A");
		sprintf(message[1], "�U���͂��������A�V���b�g��");
		sprintf(message[2], "�G�e�������܂��I");
		sprintf(message[3], "�G�̍U���͌������Ȃ�A");
		sprintf(message[4], "�G��|�����Ƃ��̃n�C�p�[");
		sprintf(message[5], "�Q�[�W�����͂Ȃ��Ȃ�܂��B");
		sprintf(message[7], "�s���`���`�����X�ɕς���");
		sprintf(message[8], "�n�C�p�[����肭���p����");
		sprintf(message[9], "��������");
		if(Player[0].hyper_count==0 && count>600){
			PlaySound(5);
			level = 6;
			count = 0;
		}
	}
	else if(level==6){
		sprintf(message[0], "�G���[�U�[�́A���[�U�[��");
		sprintf(message[1], "���S�ɖh�������ł��܂��B");
		sprintf(message[3], "���̏�ɐÎ~���āA");
		sprintf(message[4], "���[�U�[�����������ĉ�����");
		if(count>900){
			PlaySound(5);
			level = 7;
			count = 0;
		}
	}
	else if(level==7){
		sprintf(message[0], "�n�C�p�[�Q�[�W�����^��");
		sprintf(message[1], "�łȂ�����Bomb(X)�������ƁA");
		sprintf(message[2], "�ً}�{�����������܂��B");
		sprintf(message[3], "�R���{�͐؂�܂����A");
		sprintf(message[4], "��莞�Ԗ��G�ɂȂ�܂��B");
		sprintf(message[6], "��e���ɂ��A�{���X�g�b�N��");
		sprintf(message[7], "����΃I�[�g�{����");
		sprintf(message[8], "�������܂�(�ʏ���ア)");
		if(count>600){
			PlaySound(5);
			level = 8;
			count = 0;
		}
	}
	else if(level==8){
		sprintf(message[0], "�n�C�p�[�������E�I�����ɂ�");
		sprintf(message[1], "�����������G���Ԃ�����܂��B");
		sprintf(message[2], "�~�X��̕��A����ɂ�");
		sprintf(message[3], "�����������G���Ԃ�����܂��B");
		sprintf(message[4], "��肭���p���Ă��������B");
		sprintf(message[6], "�܂��A�ł��G�ɂ̓��[�U�[��");
		sprintf(message[7], "���đ�����΁A");
		sprintf(message[8], "�R���{���؂�܂���");
		if(count>600){
			PlaySound(5);
			level = 9;
			count = 0;
		}
	}
	else if(level==9){
		sprintf(message[0], "�S�Ă̓G�e�́A�����ڂ��");
		sprintf(message[1], "�����Ɣ��肪�������ł��B");
		sprintf(message[2], "�|���炸�ɁA�A�O���b�V�u��");
		sprintf(message[3], "�s���܂��傤�B");
		if(count>600){
			PlaySound(5);
			level = 10;
			count = 0;
		}
	}
	else if(level==10){
		sprintf(message[0], "�X�e�[�W���i�ނƓ����");
		sprintf(message[1], "���[�U�[�����G�����܂��B");
		sprintf(message[2], "����͖h���悤���Ȃ��̂ŁA");
		sprintf(message[3], "�撣���Ĕ����܂��傤�B");
		if(count>900){
			PlaySound(5);
			level = 11;
			count = 0;
		}
	}
	else if(level==11){
		sprintf(message[0], "����Ń`���[�g���A����");
		sprintf(message[1], "�I���ł��B");
		sprintf(message[2], "�����l�ł����I");
		sprintf(message[4], "Pause(Esc)�Ń^�C�g����ʂ�");
		sprintf(message[5], "�߂��Ă��������B");
	}
	
	if(level>=3){
		int c = Scount;
		if(c%18==0){
			float x = 30.0+fabs((3*c)%760-380)+get_rand(20);
			if(x<40)	x += 100;
			if(x>400)	x -= 100;
			if(level==6)	EMake(x, -10, 15, 0, 0, -2); 
			else		EMake(x, -10, 15, 0, 0, -1); 
		}
		if(level>=4){
			if(Scount%900==0){
				EMake(CENTER_X, -60, 300, 6, 1, -10);	
			}
		}
		if(level>=10){
			if(Scount%300==0){
				EMake(CENTER_X+50, -60, 200, 0, 0, -3);	
			}
			else if(Scount%300==150){
				EMake(CENTER_X-50, -60, 200, 0, 0, -4);	
			}
		}
	}
	
	if(BAcount>0){
		float x = 190.0 * sin(Radian(1.5*BAcount,TRUE));
		float y = 150.0 * sin(Radian(1.5*BAcount,TRUE));
		if(BAcount<60)	BAcount++;
		else{
			if(level==0){
				level = 1;
				Eshot = 0;
			}
		}
		DrawBox(440, 175, 440+x, 175+y, 0, TRUE);
		if(level>=1){
			for(int i=0;i<TATE;i++)		DrawSt(445, 178+14*i, GetColor(255,255,255), 0, tuto_font, message[i]);
		}
	}
	count++;	

	return;
}

void Stage1(){
//2500�Œ��{�X
//4350�ő��񂵏I��
	int level = Player[0].level;
	if(level==BABY)	level = EASY;
	else if(level==IMPOSSIBLE)	level = LUNATIC;
	STCOUNT[0][0] = 5030;
	STCOUNT[0][1] = 6;
	list<BOSSDATA>::iterator it = Boss.begin();
	if(Scount<340){}
	else if(Scount<=2500){
		int c = Scount-340;
		if(c%12==0){
			float x = 30.0+fabs((3*c)%760-380)+get_rand(20);
			if(x<40)	x += 100;
			if(x>400)	x -= 100;
			EMake(x, -10, 15, 0, 0, 0); 
		}
		if(c%150==0){
			if(c/150==2)		EMake(100, -10, 150, 5, 1, 1); 
			else if(c/150==3)	EMake(320, -10, 150, 5, 1, 1); 
			else if(c/150==5)	EMake(CENTER_X, -10, 150, 5, 1, 1); 
			else if(c/150==6)	EMake(320, -10, 150, 5, 1, 1); 
			else if(c/150==7)	EMake(CENTER_X, -10, 150, 5, 1, 1); 
			else if(c/150==8)	EMake(100, -10, 150, 5, 1, 1); 
			else if(c/150==9)	EMake(CENTER_X, -10, 150, 5, 1, 1); 
		}
		if(Scount==900){
			EMake(320, -60, 300, 6, 1, 2);	
		}
	}
	else if(Scount<5000&&(Boss.size()==0||(*it).death_count>0)){
		int c = Scount-2500;
		if(c%12==0){
			float x = 30.0+fabs((3*c)%760-380)+get_rand(20);
			Player[0].x-100+get_rand(200);
			if(x<40)	x += 100;
			if(x>400)	x -= 100;
			EMake(x, -10, 15, 0, 0, 0); 
			if(c%180==0){
				if(c%540==0)		EMake(100, -10, 150, 5, 1, 1); 
				else if(c%540==180)	EMake(CENTER_X, -10, 150, 5, 1, 1); 
				else if(c%540==360)	EMake(320, -10, 150, 5, 1, 1); 
			}
			if(c%900==0){
				EMake(CENTER_X-150*pow(-1,c/900), -60, 300, 6, 1, 2);	
			}
		}
	}
	if(Scount==2500){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		atack[0][0].life = 2000;		
		atack[0][0].defence = 100;
		atack[0][0].pattern = 0;
		atack[0][0].red = 255;
		atack[0][0].green = 255;
		atack[0][0].blue = 255;
		atack[0][0].count = 20;
		atack[0][0].bSpell = false;
		atack[0][1].life = 2000;		
		atack[0][1].defence = 100;
		atack[0][1].pattern = 1;
		atack[0][1].red = 255;
		atack[0][1].green = 100;
		atack[0][1].blue = 255;
		atack[0][1].count = 20;
		atack[0][1].bSpell = false;		
		BMake(600, 150, 0, 0, atack);
		NowPart = MIDBOSS; 
	}
	else if(Scount==5030){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		for(int i=0;i<3;i++){
			if(i==0){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 2900;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 2;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 40;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 5000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 0+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 50;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==1){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 2900;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 3;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 40;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 5000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 4+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 50;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==2){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 2500;		
						atack[i][j].defence = 0;
						atack[i][j].pattern = 6;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 40;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 5000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 8+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 50;
						atack[i][j].bSpell = true;		
                			}
				}
			}
		}
		TMake(0);
		NowPart = BOSS; 
	}
	if(Scount>=2500 && Boss.size()==0 && NowPart==MIDBOSS)	NowPart = LATER;
	
	if(850<=BackY&&FunctionCount==0){
		for(int i=0;i<50;i++){
			EMake(0+40*i*cos(Atan2(-265,400)), -105+40*i*sin(Atan2(-265,400)), 9, 1, 2, 4);
			EMake(0+40*i*cos(Atan2(-265,400)), -50+40*i*sin(Atan2(-265,400)), 9, 1, 2, 4);
		}
		FunctionCount = 1;
	}
	else if(1135<=BackY&&FunctionCount==1){
		for(int i=0;i<50;i++){
			EMake(0+40*i*cos(Atan2(-265,400)), -105+40*i*sin(Atan2(-265,400)), 9, 1, 2, 4);
			EMake(0+40*i*cos(Atan2(-265,400)), -50+40*i*sin(Atan2(-265,400)), 9, 1, 2, 4);
		}
		FunctionCount = 2;
	}
	else if(2367<=BackY&&FunctionCount==2){
		for(int i=0;i<50;i++){
			if(i%8==0){
				EMake(0+40*i*cos(Atan2(-265,400)), -105+40*i*sin(Atan2(-265,400)), 9, 8, 2, 3);
				EMake(0+40*i*cos(Atan2(-265,400)), -50+40*i*sin(Atan2(-265,400)), 9, 8, 2, 3);
			}
			else{
				EMake(0+40*i*cos(Atan2(-265,400)), -105+40*i*sin(Atan2(-265,400)), 9, 1, 2, 4);
				EMake(0+40*i*cos(Atan2(-265,400)), -50+40*i*sin(Atan2(-265,400)), 9, 1, 2, 4);
			}
		}
		FunctionCount = 3;
	}

	return;
}

void Stage2(){
	int level = Player[0].level;
	if(level==BABY)	level = EASY;
	else if(level==IMPOSSIBLE)	level = LUNATIC;
	STCOUNT[1][0] = 5600;
	STCOUNT[1][1] = 8;
	list<BOSSDATA>::iterator it = Boss.begin();
	if(Scount<340){
		//Scount = 5600;
		//i_hanyou[0] = 1599;
	}
	else if(Scount<1100){
		int c = Scount-340;
		
		if(c<120){
			if(c%8==0){
				float x = 400.0-get_rand(100);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<240){
			if(c%8==0){
				float x = 40.0+get_rand(100);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<360){
			if(c%8==0){
				float x = 400.0-get_rand(100);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<540){}
		else{
			if(c%5==0){
				float x = 10.0+get_rand(420);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		if(c==240)	EMake(110, -50, 500, 11, 3, 5);	
		else if(c==400)	EMake(330, -50, 500, 11, 3, 5);	
		else if(c==500)	EMake(200, -50, 400, 11, 3, 5);	
	}
	else if(Scount<2400){
		if(Scount%50==0){
			EMake(80+get_rand(280), -30, 100, 13, 4, 6);
		}
	}
	else if(Scount<2500){}
	else if(Scount<4000){
		if(Boss.size()==0||(*it).death_count>0){
			if(Scount%3==0){
				EMake(50+get_rand(320), -30, 8, 16, 8, 10);
			}
		}
	}

	if(/*NowPart==LATER && */Scount>=4000){
		i_hanyou[0]++;
	}

	if(i_hanyou[0]==0 || (Boss.size()!=0&&(*it).death_count==0)){}
	else if(i_hanyou[0]<780){
		if(i_hanyou[0]<240){
			if(Scount%15==0){
				EMake(-94+get_rand(30), 180+get_rand(100), 80, 17, 9, 11);
			}
		}
		else if(i_hanyou[0]<420){
			if(Scount%15==0){
				EMake(504+get_rand(30), 180+get_rand(100), 80, 17, 10, 11);
			}
		}
		else if(i_hanyou[0]<600){
			if(Scount%15==0){
				EMake(-94+get_rand(30), 180+get_rand(100), 80, 17, 9, 11);
			}
		}
		else{
			if(Scount%15==0){
				EMake(504+get_rand(30), 180+get_rand(100), 80, 17, 10, 11);
			}
		}
	}
	else if(i_hanyou[0]<1600){
		int c = i_hanyou[0]-780;
		
		if(c<120){
			if(c%8==0){
				float x = 40.0+get_rand(100);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<240){
			if(c%8==0){
				float x = 400.0-get_rand(100);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<360){
			if(c%8==0){
				float x = 40.0+get_rand(100);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<540){}
		else{
			if(c%5==0){
				float x = 10.0+get_rand(420);
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		if(c==240)	EMake(330, -50, 500, 11, 3, 5);	
		else if(c==400)	EMake(110, -50, 500, 11, 3, 5);	
		else if(c==500)	EMake(240, -50, 400, 11, 3, 5);	
	}
	else if(i_hanyou[0]==1600){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		for(int i=0;i<4;i++){
			if(i==0){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 3500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 9;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 45;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 6000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 16+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 55;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==1){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 3500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 10;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 40;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 5000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 20+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 50;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==2){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 2500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 11;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 40;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 7000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 24+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 60;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==3){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 2500;		
						atack[i][j].defence = 0;
						atack[i][j].pattern = 12;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 40;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 10000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 28+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 80;
						atack[i][j].bSpell = true;		
                			}
				}
			}
		}
		TMake(2);
		NowPart = BOSS; 
	}
	
	if(Scount==2410){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		atack[0][0].life = 100;		
		atack[0][0].defence = 0;
		atack[0][0].pattern = 8;
		atack[0][0].red = 255;
		atack[0][0].green = 255;
		atack[0][0].blue = 255;
		atack[0][0].count = 255;
		atack[0][0].bSpell = false;
		atack[0][1].life = 4500;		
		atack[0][1].defence = 20;
		atack[0][1].pattern = 12+level;
		atack[0][1].red = 255;
		atack[0][1].green = 100;
		atack[0][1].blue = 100;
		atack[0][1].count = 30;
		atack[0][1].bSpell = true;		
		BMake(600, 150, 3, 0, atack);
		NowPart = MIDBOSS; 
	}
	if(Scount>=2410 && Boss.size()==0 && NowPart==MIDBOSS)	NowPart = LATER;

	return;
}

void Stage3(){
	int level = Player[0].level;
	if(level==BABY)	level = EASY;
	else if(level==IMPOSSIBLE)	level = LUNATIC;
	STCOUNT[2][0] = 14500;
	STCOUNT[2][1] = 11;
	list<BOSSDATA>::iterator it = Boss.begin();
	if(Scount<120){}
	else if(Scount<1500){
		int c = Scount-120;
		
		if(c<160){
			if(c%6==0){
				float x = 20.0 + 2.5*c;
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<300){}
		else if(c<460){
			c -= 300;
			if(c%6==0){
				float x = 420.0 - 2.5*c;
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<620){
			c -= 460;
			if(c%6==0){
				float x = 20.0 + 2.5*c;
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<780){
			c -= 620;
			if(c%6==0){
				float x = 20.0 + 2.5*c;
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<940){
			c -= 780;
			if(c%6==0){
				float x = 420.0 - 2.5*c;
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<1100){
			c -= 940;
			if(c%6==0){
				float x = 420.0 - 2.5*c;
				EMake(x, -10, 15, 0, 0, 0); 
			}
		}
		else if(c<1500){
			c -= 1100;
			if(c%15==0 && Scount!=1300){
				float x1 = 20.0 + 1.0*c;
				float x2 = 420.0 - 1.0*c;
				EMake(x1, -10, 15, 0, 0, 0); 
				EMake(x2, -10, 15, 0, 0, 0); 
			}
		}
		if(Scount==1300){
			EMake(CENTER_X, -60, 700, 3, 18, 17);	
		}
	}
	else if(Scount<1900){}
	else if(Scount<3000){
		int c = Scount-1900;
		if(c<300){
			if(Scount%30==0){
				EMake(-94+get_rand(30), 180+get_rand(100), 60, 17, 9, 18);
			}
		}
		else if(c<600){
			if(Scount%30==0){
				EMake(504+get_rand(30), 180+get_rand(100), 60, 17, 10, 18);
			}
		}
		else if(c<800){}
		else{
			if(Scount%30==0){
				EMake(-94+get_rand(30), 180+get_rand(100), 60, 17, 9, 18);
				EMake(504+get_rand(30), 180+get_rand(100), 60, 17, 10, 18);
			}
		}
		if(c==500){
			EMake(CENTER_X-100.0, -60, 400, 3, 18, 17);	
		}
		else if(c==900){
			EMake(CENTER_X+100.0, -60, 400, 3, 18, 17);	
		}
		if(c%12==0){
			float x = 30.0+fabs((3*c)%760-380)+get_rand(20);
			if(x<40)	x += 100;
			if(x>400)	x -= 100;
			EMake(x, -10, 15, 0, 0, 0); 
		}
	}
	else if(Scount<3200){}
	else if(Scount<6200){
		int c = Scount-3200;
		if(c==0){
		
		}
		if(Scount<5700){
			//�d��
			if(c==0)	EMake(85, -86, 350, 18, 25, 22);
			else if(c==300)	EMake(365, 556, 350, 18, 26, 22);
			else if(c==600)	EMake(85, -86, 350, 18, 25, 22);
			else if(c==900)	EMake(365, 556, 350, 18, 26, 22);
			else if(c==1200)EMake(365, -86, 350, 18, 26, 22);
			else if(c==1500)EMake(365, 556, 350, 18, 26, 22);
			else if(c==1900){
				for(int i=0;i<3;i++){
					EMake(85, -86-192*i, 350, 18, 25, 22);
					EMake(365, 556+192*i, 350, 18, 26, 22);
				}
			}
			//���
			if(c%30==0){
				EMake(CENTER_X-60, -6, 9, 1, 19, 20);
				EMake(CENTER_X+60, -6-32, 9, 1, 19, 20);
			}
			if(c%60==0){
				EMake(CENTER_X-20, 496, 9, 1, 20, 20);
				EMake(CENTER_X+20, 496+32, 9, 1, 20, 20);
			}
			//���^���
			if(c!=0 && c%700==0){
				for(int i=0;i<2;i++){
					EMake(-150, 0+150*i, 80, 10, 21, 21);
					EMake(590, 0+150*i, 80, 10, 22, 21);
				}
			}
		}     	
		if(c%150==0){
			EMake(-16, 30+get_rand(150), 100, 13, 23, 23);
		}
		if(c%150==75){
			EMake(456, 30+get_rand(150), 100, 13, 24, 23);
		}
	}
	else if(Scount<6260){}
	else if(Scount<7890){
		int c = Scount-6260;
		if((Boss.size()==0||(*it).death_count>0) && (c!=0 && c%3==0)){
			EMake(50+get_rand(320), -30, 8, 16, 8, 10);
		}
	}
	else if(Scount<7940){}
	else if(Scount<9490){
		if(1){//�ы�
			int c = Scount-7940;
			int pat;
			int comp = c/240;
			int comp2 = c%240;
			if(comp%3==0)		pat = 25;
			else if(comp%3==1)	pat = 26;
			else if(comp%3==2)	pat = 27;
			if(comp2<70){
				if(c%4==0){
					EMake(-6, 80+get_rand(100), 8, 19, 30, pat);
				}
			}
			else if(comp2<110){}
			else if(comp2<180){
				if(c%4==0){
					EMake(446, 80+get_rand(100), 8, 19, 31, pat);
				}
			}
		}
		if(1){//�F�ы�
			int c = Scount-7940;
			if(c%6==0){
				if(c<120){
					EMake(-6, -6, 4, 20, 32, 28);
				}
				else if(c<150){}
				else if(c<270){
					EMake(446, -6, 4, 20, 33, 28);
				}
				else if(c<300){}
				else if(c<420){
					EMake(-6, -6, 4, 20, 32, 28);
					EMake(446, -6, 4, 20, 33, 28);
				}
				else if(c<450){}
				else if(c<570){
					EMake(-6, 486, 4, 21, 34, 29);
				}
				else if(c<600){}
				else if(c<720){
					EMake(446, 486, 4, 21, 35, 29);
				}
				else if(c<750){}
				else if(c<870){
					EMake(-6, 486, 4, 21, 34, 29);
					EMake(446, 486, 4, 21, 35, 29);
				}
				else if(c<900){}
				else if(c<1020){
					EMake(-6, -6, 4, 20, 32, 28);
					EMake(446, 486, 4, 21, 35, 29);
				}
				else if(c<1050){}
				else if(c<1170){
					EMake(-6, 486, 4, 21, 34, 29);
					EMake(446, -6, 4, 20, 33, 28);
				}
				else if(c<1200){}
				else if(c<1500){
					EMake(-6, -6, 4, 20, 32, 28);
					EMake(446, -6, 4, 20, 33, 28);
					EMake(-6, 486, 4, 21, 34, 29);
					EMake(446, 486, 4, 21, 35, 29);
				}
			}
		}
	}
	else if(Scount<11000){
		if(1){//�ы�
			int c = Scount-9490;
			int pat;
			int comp = c/4;
			int comp2 = c%240;
			if(comp%3==0)		pat = 25;
			else if(comp%3==1)	pat = 31;
			else if(comp%3==2)	pat = 32;
			if(comp2<70){
				if(c%4==0){
					EMake(-6, 80+get_rand(100), 8, 19, 30, pat);
				}
			}
			else if(comp2<110){}
			else if(comp2<180){
				if(c%4==0){
					EMake(446, 80+get_rand(100), 8, 19, 31, pat);
				}
			}
		}
		if(1){//�F�ы�
			int c = Scount-9490;
			if(c%6==0){
				if(c<120){
					EMake(-6, -6, 4, 20, 32, 28);
				}
				else if(c<150){}
				else if(c<270){
					EMake(446, -6, 4, 20, 33, 28);
				}
				else if(c<300){}
				else if(c<420){
					EMake(-6, -6, 4, 20, 32, 28);
					EMake(446, -6, 4, 20, 33, 28);
				}
				else if(c<450){}
				else if(c<570){
					EMake(-6, 486, 4, 21, 34, 29);
				}
				else if(c<600){}
				else if(c<720){
					EMake(446, 486, 4, 21, 35, 29);
				}
				else if(c<750){}
				else if(c<870){
					EMake(-6, 486, 4, 21, 34, 29);
					EMake(446, 486, 4, 21, 35, 29);
				}
				else if(c<900){}
				else if(c<1020){
					EMake(-6, -6, 4, 20, 32, 28);
					EMake(446, 486, 4, 21, 35, 29);
				}
				else if(c<1050){}
				else if(c<1170){
					EMake(-6, 486, 4, 21, 34, 29);
					EMake(446, -6, 4, 20, 33, 28);
				}
				else if(c<1200){}
				else if(c<1500){
					EMake(-6, -6, 4, 20, 32, 28);
					EMake(446, -6, 4, 20, 33, 28);
					EMake(-6, 486, 4, 21, 34, 29);
					EMake(446, 486, 4, 21, 35, 29);
				}
			}
		}
	}
	else if(Scount<12600){
		if(1){//�A�z��
			int c = Scount-11000;
			if(c>=60 && c<120){
				c -= 60;
				if(c%20==0)	EMake((c/20)*(CENTER_X/3.0), -16, 100, 23, 36, 33);
			}
			else if(c>=120 && c<240){}
			else if(c>=240 && c<300){
				c -= 240;
				if(c%20==0)	EMake(430-(c/20)*(CENTER_X/3.0), -16, 100, 23, 36, 33);
			}
			else if(c>=300 && c<420){}
			else if(c>=420 && c<540){
				c -= 420;
				if(c%20==0)	EMake((c/20)*(430/6.0), -16, 100, 23, 36, 33);
			}
			else if(c>=540 && c<600){}
			else if(c>=600 && c<720){
				c -= 600;
				if(c%20==0)	EMake(430.0-(c/20)*(430/6.0), -16, 100, 23, 36, 33);
			}
			else if(c>=720 && c<840){}
			else if(c>=840 && c<1020){
				c -= 840;
				if(c==0){
					for(int i=0;i<3;i++)	EMake(i*(430/3), -16, 100, 23, 36, 33);
				}
			}
			else if(c>=1020 && c<1200){
				c -= 1020;
				if(c==0){
					for(int i=0;i<3;i++)	EMake(430.0-i*(430/3), -16, 100, 23, 36, 33);
				}
			}
			else if(c>=1200 && c<1380){
				c -= 1200;
				if(c==0){
					for(int i=0;i<6;i++)	EMake(i*(430/6), -16, 100, 23, 36, 33);
				}
			}
			else if(c>=1380 && c<1600){
				c -= 1380;
				if(c==0){
					for(int i=0;i<6;i++)	EMake(430.0-i*(430/6), -16, 100, 23, 36, 33);
				}
			}
		}
		if(1){//�F�ы�
			int c = Scount-11000;
			if(c%6==0){
				if(c<120){
					EMake(-6, -6, 4, 22, 32, 30);
				}
				else if(c<150){}
				else if(c<270){
					EMake(446, -6, 4, 22, 33, 30);
				}
				else if(c<300){}
				else if(c<420){
					EMake(-6, -6, 4, 22, 32, 30);
					EMake(446, -6, 4, 22, 33, 30);
				}
				else if(c<450){}
				else if(c<570){
					EMake(-6, 486, 4, 22, 34, 30);
				}
				else if(c<600){}
				else if(c<720){
					EMake(446, 486, 4, 22, 35, 30);
				}
				else if(c<750){}
				else if(c<870){
					EMake(-6, 486, 4, 22, 34, 30);
					EMake(446, 486, 4, 22, 35, 30);
				}
				else if(c<900){}
				else if(c<1020){
					EMake(-6, -6, 4, 22, 32, 30);
					EMake(446, 486, 4, 22, 35, 30);
				}
				else if(c<1050){}
				else if(c<1170){
					EMake(-6, 486, 4, 22, 34, 30);
					EMake(446, -6, 4, 22, 33, 30);
				}
				else if(c<1200){}
				else if(c<1600){
					EMake(-6, -6, 4, 22, 32, 30);
					EMake(446, -6, 4, 22, 33, 30);
					EMake(-6, 486, 4, 22, 34, 30);
					EMake(446, 486, 4, 22, 35, 30);
				}
			}
		}
	}
	else if(Scount<14100){
		if(1){//�ы�
			int c = Scount-12600;
			int pat;
			int comp = c/8;
			int comp2 = c%240;
			if(comp%3==0)		pat = 25;
			else if(comp%3==1)	pat = 31;
			else if(comp%3==2)	pat = 32;
			if(comp2<70){
				if(c%8==0){
					EMake(-6, 80+get_rand(100), 8, 19, 30, pat);
				}
			}
			else if(comp2<110){}
			else if(comp2<180){
				if(c%8==0){
					EMake(446, 80+get_rand(100), 8, 19, 31, pat);
				}
			}
		}
		if(1){//�A�z��
			int c = Scount-12600;
			if(c>=60 && c<120){
				c -= 60;
				if(c%20==0)	EMake((c/20)*(CENTER_X/3.0), -16, 60, 23, 36, 33);
			}
			else if(c>=120 && c<240){}
			else if(c>=240 && c<300){
				c -= 240;
				if(c%20==0)	EMake(430-(c/20)*(CENTER_X/3.0), -16, 60, 23, 36, 33);
			}
			else if(c>=300 && c<420){}
			else if(c>=420 && c<540){
				c -= 420;
				if(c%20==0)	EMake((c/20)*(430/6.0), -16, 60, 23, 36, 33);
			}
			else if(c>=540 && c<600){}
			else if(c>=600 && c<720){
				c -= 600;
				if(c%20==0)	EMake(430.0-(c/20)*(430/6.0), -16, 60, 23, 36, 33);
			}
			else if(c>=720 && c<840){}
			else if(c>=840 && c<1020){
				c -= 840;
				if(c==0){
					for(int i=0;i<3;i++)	EMake(i*(430/3), -16, 60, 23, 36, 33);
				}
			}
			else if(c>=1020 && c<1200){
				c -= 1020;
				if(c==0){
					for(int i=0;i<3;i++)	EMake(430.0-i*(430/3), -16, 60, 23, 36, 33);
				}
			}
			else if(c>=1200 && c<1380){
				c -= 1200;
				if(c==0){
					for(int i=0;i<6;i++)	EMake(i*(430/6), -16, 60, 23, 36, 33);
				}
			}
			else if(c>=1380 && c<1600){
				c -= 1380;
				if(c==0){
					for(int i=0;i<6;i++)	EMake(430.0-i*(430/6), -16, 60, 23, 36, 33);
				}
			}
		}
		if(1){//�F�ы�
			int c = Scount-12600;
			if(c%6==0){
				if(c<120){
					EMake(-6, -6, 4, 22, 32, 30);
				}
				else if(c<150){}
				else if(c<270){
					EMake(446, -6, 4, 22, 33, 30);
				}
				else if(c<300){}
				else if(c<420){
					EMake(-6, -6, 4, 22, 32, 30);
					EMake(446, -6, 4, 22, 33, 30);
				}
				else if(c<450){}
				else if(c<570){
					EMake(-6, 486, 4, 22, 34, 30);
				}
				else if(c<600){}
				else if(c<720){
					EMake(446, 486, 4, 22, 35, 30);
				}
				else if(c<750){}
				else if(c<870){
					EMake(-6, 486, 4, 22, 34, 30);
					EMake(446, 486, 4, 22, 35, 30);
				}
				else if(c<900){}
				else if(c<1020){
					EMake(-6, -6, 4, 22, 32, 30);
					EMake(446, 486, 4, 22, 35, 30);
				}
				else if(c<1050){}
				else if(c<1170){
					EMake(-6, 486, 4, 22, 34, 30);
					EMake(446, -6, 4, 22, 33, 30);
				}
				else if(c<1200){}
				else if(c<1600){
					EMake(-6, -6, 4, 22, 32, 30);
					EMake(446, -6, 4, 22, 33, 30);
					EMake(-6, 486, 4, 22, 34, 30);
					EMake(446, 486, 4, 22, 35, 30);
				}
			}
		}
	}

	if(Scount>7800 && Scount<8000)		SESDelete(5); 
	if(Scount>14000 && Scount<14200)	SESDelete(5); 

	if(Scount>=6200 && Scount<6260){
		if(Scount==6200)	PlaySound(20);
		float d = 5 + 4.0*(6260-Scount);
		EfMake(CENTER_X, CENTER_Y, -2, 11, d);
	}
	if(Scount==6260){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		atack[0][0].life = 4000;		
		atack[0][0].defence = 100;
		atack[0][0].pattern = 13;
		atack[0][0].red = 255;
		atack[0][0].green = 255;
		atack[0][0].blue = 255;
		atack[0][0].count = 25;
		atack[0][0].bSpell = false;
		BMake(CENTER_X, CENTER_Y, 3, 0, atack);
		NowPart = MIDBOSS; 
	}
	if(Scount>=6260 && Boss.size()==0 && NowPart==MIDBOSS)	NowPart = LATER;
	if(Scount==14620){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		for(int i=0;i<5;i++){
			if(i==0){
				for(int j=0;j<1;j++){
					if(j==0){
						atack[i][j].life = 6500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 14;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 45;
						atack[i][j].bSpell = false;
					}
				}
			}
			else if(i==1){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 6500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 15;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 45;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 8000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 32+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 55;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==2){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 6500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 16;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 45;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 8000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 36+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 55;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==3){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 6500;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 17;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 45;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 8000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 40+level;
						atack[i][j].red = 255;
						atack[i][j].green = 100;
						atack[i][j].blue = 100;
						atack[i][j].count = 60;
						atack[i][j].bSpell = true;		
                			}
				}
			}
			else if(i==4){
				for(int j=0;j<4;j++){
					if(j==0){
						atack[i][j].life = 2500;		
						atack[i][j].defence = 0;
						atack[i][j].pattern = 12;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 255;
						atack[i][j].bSpell = false;
					}
					else if(j==1){
						atack[i][j].life = 4000;		
						atack[i][j].defence = 20;
						atack[i][j].pattern = 44+level;
						atack[i][j].red = 255;
						atack[i][j].green = 150;
						atack[i][j].blue = 150;
						atack[i][j].count = 60;
						atack[i][j].bSpell = true;		
					}
					else if(j==2){
						atack[i][j].life = 2500;		
						atack[i][j].defence = 0;
						atack[i][j].pattern = 12;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 255;
						atack[i][j].bSpell = false;
					}
					else if(j==3){
						atack[i][j].life = 8000;		
						atack[i][j].defence = 10;
						atack[i][j].pattern = 48+level;
						atack[i][j].red = 255;
						atack[i][j].green = 0;
						atack[i][j].blue = 0;
						atack[i][j].count = 70;
						atack[i][j].bSpell = true;		
                			}
				}
			}
		}
		TMake(4);
		NowPart = BOSS; 
	}

	return;
}

void Stage4(){
	int level = Player[0].level;
	if(level==BABY)	level = EASY;
	else if(level==IMPOSSIBLE)	level = LUNATIC;
	STCOUNT[2][0] = 14250;
	STCOUNT[2][1] = 10;
	list<BOSSDATA>::iterator it = Boss.begin();
	
	if(Scount==0){
	}

	/*
	if(Scount%300==0){
		EMake(CENTER_X, -10, 100, 0, 0, 19);
	}
	*/
	
	return;
}

void Stage5(){
	int level = Player[0].level;
	if(level==BABY)	level = EASY;
	else if(level==IMPOSSIBLE)	level = LUNATIC;
	STCOUNT[2][0] = 14250;
	STCOUNT[2][1] = 10;
	list<BOSSDATA>::iterator it = Boss.begin();
	
	if(Scount==0){
		for(int i=0;i<ATACK_NUMA;i++){
			for(int j=0;j<ATACK_NUMB;j++){
				atack[i][j].life = 0;		
				atack[i][j].defence = 100;
				atack[i][j].pattern = 0;
				atack[i][j].red = 255;
				atack[i][j].green = 255;
				atack[i][j].blue = 255;
				atack[i][j].count = 0;
				atack[i][j].bSpell = false;
			}
		}
		for(int i=0;i<1;i++){
			if(i==0){
				for(int j=0;j<2;j++){
					if(j==0){
						atack[i][j].life = 30000;		
						atack[i][j].defence = 100;
						atack[i][j].pattern = 25;
						atack[i][j].red = 255;
						atack[i][j].green = 255;
						atack[i][j].blue = 255;
						atack[i][j].count = 255;
						atack[i][j].bSpell = false;
					}
				}
			}
		}
		//BMake(CENTER_X, CENTER_Y+100, 1, 1, atack); 
		BMake(CENTER_X, CENTER_Y-100, 1, 1, atack); 
		NowPart = BOSS; 
	}

	/*
	if(Scount%300==0){
		EMake(CENTER_X, -10, 100, 0, 0, 19);
	}
	*/
	
	return;
}