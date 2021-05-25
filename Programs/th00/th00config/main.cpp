#include "extern.h"

int CSave();
int CLoad();
void CSaveReset();
void CConfig();

int MainFont;
int SubFont;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
        SetWindowText("�����剝�� �R���t�B�O");        
        ChangeWindowMode( TRUE );
        if( DxLib_Init() == -1 ) return -1; // �c�w���C�u�������������� �G���[���N������I��
	CLoad();

	do{
		ClsDrawScreen();
		CConfig();
		CheckPushKey();
		ScreenFlip();
	}while(ProcessMessage()==0&&CheckHitKey(KEY_INPUT_ESCAPE)==0);

	CSave();	
        DxLib_End();
        return 0 ;              // �\�t�g�̏I��
}

int CSave(){
	char *name = "th00.cfg";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "�f�[�^�̏������݂Ɏ��s");
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
		return 1;
	}
	fwrite(&Config,sizeof(CONFIGDATA),1,fp);
	
	fclose(fp);
	
	return 0;
}

int CLoad(){
	MainFont = CreateFontToHandle("�l�r �S�V�b�N",18,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
	SubFont = CreateFontToHandle("�l�r �S�V�b�N",14,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(FALSE);
	

	char *name = "th00.cfg";
	FILE *fp;
	if((fp=fopen(name,"rb")) == NULL){
		CSaveReset();
		fp=fopen(name,"rb");
	}
	fread(&Config,sizeof(CONFIGDATA),1,fp);
	
	fclose(fp);
	
	return 0;
}

void CSaveReset(){
	Config.fps = 0;
	Config.drawmode = 0;
	Config.bgmmode = 0;
	char *name = "th00.cfg";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "�f�[�^�̏������Ɏ��s");
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
		return;
	}
	
	fwrite(&Config,sizeof(CONFIGDATA),1,fp);
	
	fclose(fp);
	return;
}

void CConfig(){
	static int carsol;
	int number = 3;
	int st_size = 20;
	int base_y = 100;
	int base_y2 = 350;
	int size;
	char ma[128],sub[2][128];
	for(int i=0;i<number;i++){
		switch(i){
			case 0:
				wsprintf(ma , "�e�o�r���U�O�ɌŒ肷��i����:����j");
				break;
			case 1:
				wsprintf(ma , "�`��X�V�񐔁i����:����j");
				break;
			case 2:
				wsprintf(ma , "�a�f�l���[�h�����i����:�O�j");
				break;
		}
		switch(carsol){
			case 0:
				wsprintf(sub[0] , "�e�o�r�������I�ɂU�O�ɂ��邩�A�}�V���ɔC���邩��I��");
				wsprintf(sub[1] , "�U�O�ȊO�łe�o�r�����肷��ꍇ�A���Ȃ���I��");		
				break;
			case 1:
				wsprintf(sub[0] , "�`��X�V�񐔂�I���B�����������y�������");
				wsprintf(sub[1] , "�X�V�񐔂����炷�Ȃ�A�K���e�o�r�Œ�����Ă�������");		
				break;
			case 2:
				if(Config.bgmmode==0){
					wsprintf(sub[0] , "%d:�K�v�ɉ����ă��[�h�i�f�t�H���g�j",Config.bgmmode);		
					wsprintf(sub[1] , "�K�v���Ƀ��[�h���܂��B���������͊e�����ɕ��U���܂��B");
				}
				if(Config.bgmmode==1){
					wsprintf(sub[0] , "%d:�Q�[���J�n���ɑS�ă��[�h",Config.bgmmode);		
					wsprintf(sub[1] , "�}�V���ɂ���Ă͏d���Ȃ�܂��B���������̓Q�[���J�n���ɏW�����܂�");
				}
				if(Config.bgmmode==2){
					wsprintf(sub[0] , "%d:���񃍁[�h",Config.bgmmode);		
					wsprintf(sub[1] , "�Đ��̂��тɃ��[�h���܂��B�ȃf�[�^�ێ��ŏd���Ȃ�}�V���ɗL���ł�");
				}
				break;
		}
		if(carsol==i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
		DrawStringToHandle(50,base_y+st_size*i,ma,GetColor(255,255,255),MainFont);
		if(i==0){
			size = GetDrawFormatStringWidthToHandle(MainFont,ma);
			if(Config.fps==0)	DrawStringToHandle(70+size,base_y+st_size*i,"�� ���� �@��",GetColor(255,255,100),MainFont);
			else			DrawStringToHandle(70+size,base_y+st_size*i,"�� ���Ȃ� ��",GetColor(255,255,100),MainFont);
		}
		if(i==1){
			size = GetDrawFormatStringWidthToHandle(MainFont,ma);
			if(Config.drawmode==0)	DrawStringToHandle(70+size,base_y+st_size*i,"�� �@���� �@��",GetColor(255,255,100),MainFont);
			if(Config.drawmode==1)	DrawStringToHandle(70+size,base_y+st_size*i,"�� �Q���̂P ��",GetColor(255,255,100),MainFont);
			if(Config.drawmode==2)	DrawStringToHandle(70+size,base_y+st_size*i,"�� �R���̂P ��",GetColor(255,255,100),MainFont);
		}
		if(i==2){
			size = GetDrawFormatStringWidthToHandle(MainFont,ma);
			if(Config.bgmmode==0)	DrawStringToHandle(70+size,base_y+st_size*i,"�� �O ��",GetColor(255,255,100),MainFont);
			if(Config.bgmmode==1)	DrawStringToHandle(70+size,base_y+st_size*i,"�� �P ��",GetColor(255,255,100),MainFont);
			if(Config.bgmmode==2)	DrawStringToHandle(70+size,base_y+st_size*i,"�� �Q ��",GetColor(255,255,100),MainFont);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	}
	for(int a=0;a<2;a++){
		DrawStringToHandle(50,base_y2+18*a,sub[a],GetColor(255,255,255),SubFont);
	}		
	char message[128];
	wsprintf(message , "Esc:�I��");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	size = GetDrawFormatStringWidthToHandle(SubFont,message);
	DrawStringToHandle(320-size/2,450,message,GetColor(255,255,150),SubFont);
	
	if(c_key[KEY_INPUT_DOWN]%20==1){
		carsol++;
	}
	if(c_key[KEY_INPUT_UP]%20==1){
		carsol--;
		carsol+=number;
	}
        carsol = carsol%number;
	if(c_key[KEY_INPUT_LEFT]%20==1){
		if(carsol==0){
			Config.fps--;
			Config.fps+=2;
		}
		if(carsol==1){
			Config.drawmode--;
			Config.drawmode+=3;
		}
		if(carsol==2){
			Config.bgmmode--;
			Config.bgmmode+=3;
		}
	}
	if(c_key[KEY_INPUT_RIGHT]%20==1){
		if(carsol==0)	Config.fps++;
		if(carsol==1)	Config.drawmode++;
		if(carsol==2)	Config.bgmmode++;
	}
	Config.fps = Config.fps%2;
	Config.drawmode = Config.drawmode%3;
	Config.bgmmode = Config.bgmmode%3;
	return;
}