#include "DxLib.h"
#include "extern.h"

int Eup;
int Edown;
int Eleft;
int Eright;
int Eshot;
int Ebomb;
int Eslow;
int Eskip;
int Epause;
int Sloop;
int LOOP;

bool bShake;

ATACKDATA atack[ATACK_NUMA][ATACK_NUMB];

int c_key[C_KEY_NUM];
int c_pad[C_PAD_NUM];
int rand_seed;
float shake_x;
float shake_y;
int SoundFlag[SOUND_NUM];
char nowloading[32];

bool replay_play;//���v���C�Đ����H
int replay_play_num;//���Ԃ̃��v���C�Đ����H
int replay_count;//���v���C�ۑ��v�f
REPLAYDATA Demo[DEMO_NUM];
REPLAYDATA Replay[REPLAY_NUM];
REPLAYDATA SReplay;
unsigned char before_key;//���O�̃L�[����
int Kcount;//���̃L�[���͂������Ă�t���[����

int default_font;
int talk_font;
int spell_font;
int tuto_font;

void WriteLog(char log[]);
bool GetSkip();
void GetInput(int *up, int *down, int *left, int *right, int *shot, int *bomb, int *slow, int *skip, int *pause, bool flag);
void PlaySound(int i);
void SoundEffect();
void SShake(int type, float level);
void SCheckPlayTime();
int SSave();
void SLoad();
void SSaveReset();
void CheckPushKey();
void Fps();
void SnapShot();
int get_rand(int max);
float Radian(float d, int flag);
float Atan2(float y, float x);
void crypt(void* data,unsigned int size,unsigned char code);
void DrawSt(float x,float y,int color,int tocolor,int font,char message[256]);
int draw_string(float x,float y,int num,char *buffer);
int get_length(int num,char *buffer);
int draw_score(float x,float y,unsigned int num,int limit,bool zero);
int draw_hit(float x,float y,int num,int img);
int draw_spell(float x,float y,int num);


SAVEDATA SAVE;
SCOREDATA SScore;//���v���C�L�^�p
int STCount;//�X�^�[�g���̃E�B���h�E�Y�N������̃J�E���g
int NOCount;//�O��^�C�}�[���~�߂��n�_�̃E�B���h�E�Y�N������̃J�E���g
int CKCount;//�~�σJ�E���g
int STCOUNT[STAGE_NUM][2];//0:�X�e�[�W�̑S�H���J�E���g�� 1:�{�X��̑���̃��C�t���i�S�U�����j
int BOSSERASENUM;//�{�X��|������
int i_hanyou[8];

SCENE scene;

void WriteLog(char log[]){
	FILE *fp;
	fp = fopen("���O.txt","a");
	fputs(log,fp);
	fputc('\n',fp);
	fclose(fp);
	
	return;
}

bool GetSkip(){
	if(LOOP==1 || (LOOP==10&&Sloop==LOOP-1))	return true;
	else	return false;
	
}

void GetInput(int *up, int *down, int *left, int *right, int *shot, int *bomb, int *slow, int *skip, int *pause, bool flag){
	if(flag==true){
		if(!(scene==GAME&&replay_play==true&&Pcount==0&&Ccount==0)){
			if(c_key[KEY_INPUT_UP]>0 || c_pad[PAD_UP]>0)		Eup++;
			else							Eup = 0;
			if(c_key[KEY_INPUT_DOWN]>0 || c_pad[PAD_DOWN]>0)	Edown++;
			else							Edown = 0;
			if(c_key[KEY_INPUT_LEFT]>0 || c_pad[PAD_LEFT]>0)	Eleft++;
			else							Eleft = 0;
			if(c_key[KEY_INPUT_RIGHT]>0 || c_pad[PAD_RIGHT]>0)	Eright++;
			else							Eright = 0;
			if(c_key[KEY_INPUT_Z]>0 || c_pad[SAVE.Key_Shot]>0)	Eshot++;
			else if((scene!=GAME||Pcount>0||Ccount>0)&&(c_key[KEY_INPUT_RETURN]>0))	Eshot++;
			else							Eshot = 0;
			if(c_key[KEY_INPUT_X]>0 || c_pad[SAVE.Key_Bomb]>0)	Ebomb++;
			else							Ebomb = 0;
			if(c_key[KEY_INPUT_LSHIFT]>0 || c_pad[SAVE.Key_Slow]>0)	Eslow++;
			else							Eslow = 0;
			if(c_key[KEY_INPUT_LCONTROL]>0 || c_pad[SAVE.Key_Skip]>0)	Eskip++;
			else								Eskip = 0;
		}
		if(c_key[KEY_INPUT_ESCAPE]>0 || c_pad[SAVE.Key_Pause]>0)	Epause++;
		else								Epause = 0;
	}
	else{
		if(!(scene==GAME&&replay_play==true&&Pcount==0&&Ccount==0)){
			*up = Eup;
			*down = Edown;
			*left = Eleft;
			*right = Eright;
			*shot = Eshot;
			*bomb = Ebomb;
			*slow = Eslow;
			*skip = Eskip;
		}
		*pause = Epause;
	}

	return;	
}

void PlaySound(int i){
	SoundFlag[i] = 1;
	return;
}

void SoundEffect(){
	for(int i=0;i<SOUND_NUM;i++){
		if(SoundFlag[i]==1)	MuPlaySound(i);
		SoundFlag[i] = 0;
	}
	return;
}

void SShake(int type, float level){
	if(bShake==true)	return;
	static int count;
	if(type==0){//�S��
		shake_x = level * sin(Radian(50*count,TRUE));
		shake_y = level * sin(Radian(70*count,TRUE));
	}
	else if(type==1){//x��
		shake_x = level * sin(Radian(50*count,TRUE));
	}
	else if(type==2){//y��
		shake_y = level * sin(Radian(70*count,TRUE));
	}
	count++;
	bShake = true;
	return;
}

void SCheckPlayTime(){
	DATEDATA D;
	static int time = 0;
	GetDateTime(&D);
	if(D.Sec!=time){
		time = D.Sec;
		SAVE.PlayTime[LEVEL_NUM]++;
	}
	if(SAVE.PlayTime[LEVEL_NUM]>3599999){
		SAVE.PlayTime[LEVEL_NUM] = 3599999;
	}

	return;
}

int SSave(){
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	char *name = "score.dat";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "�Z�[�u�Ɏ��s");
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
		return 1;
	}
	fwrite(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	
	fclose(fp);
	
	return 0;
}

void SLoad(){
	//SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	if(1){
		char *name = "���O.txt";
		FILE *fp;
		fp=fopen(name,"w");
		fclose(fp);
	}
	SetDXArchiveExtension("dat");
	rand_seed = time(NULL);
	shake_x = 0;
	shake_y = 0;
	default_font = CreateFontToHandle("�l�r �S�V�b�N", 14, -1, DX_FONTTYPE_ANTIALIASING_EDGE);
	talk_font = CreateFontToHandle("�l�r �S�V�b�N", 14, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	spell_font = CreateFontToHandle("�l�r �o�S�V�b�N", 14, -1, DX_FONTTYPE_ANTIALIASING_EDGE);
	tuto_font = CreateFontToHandle("�l�r �o�S�V�b�N", 12, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	//CreateMaskScreen();
	//SetUseMaskScreenFlag(FALSE);
	ChangeFontType(DX_FONTTYPE_EDGE);
        SetFontSize(10);
	SetAlwaysRunFlag(TRUE);
	ChangeFont("MS UI Gothic");
 	sprintf(nowloading, "��ł�ł�Ł�");
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int size = GetDrawStringWidth(nowloading,14);
	DrawString(640-size,480-12,nowloading,GetColor(255,255,255));			
	ScreenFlip();
	char *name = "score.dat";
	FILE *fp;
	if((fp=fopen(name,"rb")) == NULL){
		SSaveReset();
		fp=fopen(name,"rb");
	}
	
	fread(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	SetGraphDataShavedMode(DX_SHAVEDMODE_DITHER);
	
	fclose(fp);

	if(SAVE.Version!=VERSION){
		SSaveReset();
		fp=fopen(name,"rb");
		fread(&SAVE,sizeof(SAVEDATA),1,fp);
		crypt(&SAVE,sizeof(SAVEDATA),0xF7);
		fclose(fp);
        }

	replay_play = false;
	replay_play_num = 0;
	RLoad();
	for(int i=0;i<REPLAY_NUM;i++){
		char name[64];
		wsprintf(name ,"replay/goog_%02d.rpy",i+1);
		FILE *fp;
		if((fp=fopen(name,"rb")) == NULL){
			Replay[i].exist = false;
			for(int j=0;j<USER_NAME_NUM+1;j++)	Replay[i].name[j] = '\0';
			fclose(fp);
			continue;
		}
		
		fread(&Replay[i],sizeof(REPLAYDATA)-5*REPLAY_ELEMENT_NUM,1,fp);
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		int Element = Replay[i].element_num;
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		for(int a=0;a<Element;a++){
			Replay[i].replay_element[a] = fgetc(fp);
		}
		fread(&Replay[i].replay_count[0],4*Element,1,fp);
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		
		if(Replay[i].version!=VERSION)	Replay[i].exist = false;
		
		fclose(fp);
	}
	for(int i=0;i<DEMO_NUM;i++){
		char name[64];
		wsprintf(name ,"data/demo/demo_%02d.rpy",i+1);
		FILE *fp;
		if((fp=fopen(name,"rb")) == NULL){
			Demo[i].exist = false;
			for(int j=0;j<USER_NAME_NUM+1;j++)	Demo[i].name[j] = '\0';
			fclose(fp);
			continue;
		}
		
		fread(&Demo[i],sizeof(REPLAYDATA)-5*REPLAY_ELEMENT_NUM,1,fp);
		crypt(&Demo[i],sizeof(REPLAYDATA),0xF7);
		int Element = Demo[i].element_num;
		crypt(&Demo[i],sizeof(REPLAYDATA),0xF7);
		for(int a=0;a<Element;a++){
			Demo[i].replay_element[a] = fgetc(fp);
		}
		fread(&Demo[i].replay_count[0],4*Element,1,fp);
		crypt(&Demo[i],sizeof(REPLAYDATA),0xF7);
		
		if(Demo[i].version!=VERSION)	Demo[i].exist = false;
		
		fclose(fp);
	}
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	Eup = 0;
	Edown = 0;
	Eleft = 0;
	Eright = 0;
	Eshot = 0;
	Ebomb = 0;
	Eslow = 0;
	Eskip = 0;
	Epause = 0;
	Sloop = 0;
	LOOP = 0;

	return;
}

void SSaveReset(){
	SAVE.Version = VERSION;
	SAVE.Key_Shot = PAD_A;
	SAVE.Key_Bomb = PAD_B;
	SAVE.Key_Slow = PAD_C;
	SAVE.Key_Skip = PAD_X;
	SAVE.Key_Pause = PAD_START;
	SAVE.Bgm = 100;
	SAVE.Sound = 30;
	SAVE.Ship = 2;
	SAVE.Bomb = 3;
	SAVE.Level = 1;
	SAVE.Chara = 0;
	SAVE.Stage = 1;
	for(int i=0;i<LEVEL_NUM;i++)	SAVE.PlayCount[i] = 0;
	for(int i=0;i<LEVEL_NUM+1;i++)	SAVE.PlayTime[i] = 0;
	for(int j=0;j<CHARA_NUM;j++){
		for(int i=0;i<SPELL_NUM;i++){
			SAVE.SpGet[j][i] = 0;
			SAVE.SpChallenge[j][i] = 0;
		}
	}
	SAVE.Extra = false;
	SAVE.Practice = true;
	SAVE.Baby = false;
	SAVE.Impossible = false;
	for(int i=0;i<USER_NAME_NUM+1;i++)	SAVE.LastName[i] = '\0';
	sprintf(SAVE.LastName, "\0");
	for(int j=0;j<LEVEL_NUM;j++){
		for(int k=0;k<CHARA_NUM;k++){
			for(int i=0;i<SCORE_NUM;i++){
				SAVE.Score[j][k][i].score[0] = SCORE_NUM-i;
				SAVE.Score[j][k][i].score[1] = 0;
				for(int a=0;a<STAGE_NUM;a++){
					for(int b=0;b<2;b++){
						SAVE.Score[j][k][i].stage_allscore[a][b] = 0;
						for(int c=0;c<STAGE_SCORE_NUM;c++)	SAVE.Score[j][k][i].stage_score[a][c][b] = 0;
					}
				}
				if(j!=EXTRA){
					SAVE.Score[j][k][i].start_stage = 1;
					if(i<2)		SAVE.Score[j][k][i].end_stage = 5;
					else if(i<4)	SAVE.Score[j][k][i].end_stage = 4;
					else if(i<6)	SAVE.Score[j][k][i].end_stage = 3;
					else if(i<8)	SAVE.Score[j][k][i].end_stage = 2;
					else		SAVE.Score[j][k][i].end_stage = 1;
				}
				else{
					SAVE.Score[j][k][i].start_stage = 1;
					SAVE.Score[j][k][i].end_stage = 1;
				}
				SAVE.Score[j][k][i].gameper = 0;
				SAVE.Score[j][k][i].slowrate = 0;
				SAVE.Score[j][k][i].con_num = 0;
				SAVE.Score[j][k][i].miss_num = 0;
				SAVE.Score[j][k][i].bomb_num = 0;
				SAVE.Score[j][k][i].hyper_num = 0;
				SAVE.Score[j][k][i].spell_num = 0;
				for(int a=0;a<STAGE_NUM+1;a++){
					if(i<3)		SAVE.Score[j][k][i].rank[a] = 600;
					else if(i<7)	SAVE.Score[j][k][i].rank[a] = 300;
					else		SAVE.Score[j][k][i].rank[a] = 0;
					SAVE.Score[j][k][i].root[a] = 0;
					SAVE.Score[j][k][i].Rplaytime[a] = 0;
					SAVE.Score[j][k][i].Vplaytime[a] = 0;
					SAVE.Score[j][k][i].enemy_num[a] = 0;
					SAVE.Score[j][k][i].enemyshot_num[a] = 0;
					for(int l=0;l<3;l++)	SAVE.Score[j][k][i].item_num[l][a] = 0;
					SAVE.Score[j][k][i].max_soten[a] = 0;
					SAVE.Score[j][k][i].max_hit[a] = 0;
				}
				for(int a=0;a<2;a++){
					SAVE.Score[j][k][i].year[a] = 2011;
					SAVE.Score[j][k][i].month[a] = 1;
					SAVE.Score[j][k][i].date[a] = 1;
					SAVE.Score[j][k][i].hour[a] = 0;
					SAVE.Score[j][k][i].minute[a] = 0;
					SAVE.Score[j][k][i].second[a] = 0;
				}
				for(int a=0;a<SPELL_NUM;a++){
					SAVE.Score[j][k][i].score_spcard[a] = 0;
				}
				for(int a=0;a<USER_NAME_NUM+1;a++){
					SAVE.Score[j][k][i].name[a] = '\0';
				}
				sprintf(SAVE.Score[j][k][i].name, "VINYLON");
			}
		}
	}

	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	char *name = "score.dat";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "�f�[�^�̏������ɉ��̂����s");
		MessageBox( 	NULL,
			message,
			"Error",
			MB_OK | 
			MB_ICONSTOP |
			MB_TOPMOST);
		return;
	}
	
	fwrite(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	
	fclose(fp);	
	return;
}

void CheckPushKey(){
//���t���[���̊ԃ{�^����������Ă��邩�B0�͉�����Ă��Ȃ��B
	bool runflag = GetWindowActiveFlag();
	char check[C_KEY_NUM];
	GetHitKeyStateAll(check);
	for(int i=0;i<C_KEY_NUM;i++){
		if(check[i]==1&&runflag==true)	c_key[i]++;
		else		c_key[i] = 0; 
	}
	int key = GetJoypadInputState(DX_INPUT_PAD1);
	for(int i=0;i<C_PAD_NUM;i++){
		int a = 1;
		for(int b=0;b<i;b++){	a *= 2;	}
		if((key&a)&&runflag==true)	c_pad[i]++;
		else		c_pad[i] = 0;
	}
		
	return;
}

void Fps(){
	float frame = 60.0;
	static float ZeroCount = 0;
	static float count = frame;
	static float fps = 0;
	static int fps2;
	if(ZeroCount!=0){
		float wait = ZeroCount+1000.0/frame*count-1.0-GetNowCount();
		if(wait>0){
			Sleep(wait);
		}
	}
	if(count==frame){
		int zero = ZeroCount;
		ZeroCount = GetNowCount();
		fps = 1000.0 / ((GetNowCount()-zero)/frame);
		fps2 = GetNowCount() - zero;
		count = 1;
	}
	else{
		count++;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int color = GetColor(255,255,255);
	if(fps<50){
		color = GetColor(100,100,255);
	}
	if(fps>0.09){
		int size = GetDrawFormatStringWidth("%.1ffps",fps);
		DrawFormatString(640-size,468,color,"%.1ffps",fps);
	}	
	return;
}

void SnapShot(){
	if(c_key[KEY_INPUT_P]==1){
		char path[128];
		wsprintf(path , "snapshot");
		if(PathIsDirectory(path)==false){
			CreateDirectory(path,NULL);
		}
		for(int i=0;i<999;i++){
			wsprintf(path , "snapshot/goog_%03d.bmp",i+1);
			if(PathFileExists(path)==false){
				break;
			}
		}
		SaveDrawScreen(0,0,640,480,path);
	}
	return;
}

int get_rand(int max){
//0~max�܂ł̗������擾
	rand_seed ++;
	SRand(rand_seed);
	int rand = GetRand(max);
	return rand;
}

float Radian(float d, int flag){
//TRUE:�x�����W�A���ϊ��AFALSE:���W�A�����x�ϊ�
	float degree;
	if(flag==TRUE) degree = d / 180 * M_PI;
	else degree = d * 180 / M_PI;
	
	return degree;		
}

float Atan2(float y, float x){
	if(x!=0||y!=0)	return atan2(y,x);
	else		return 0;		
}

void crypt(void* data,unsigned int size,unsigned char code){
	unsigned char* ch = (unsigned char*)data;
	unsigned char* ch_end = ch + size;
	int count = 1;
	while(ch<ch_end){
		*ch ^= code*count;
		ch++;
		count++;
	}
	return;
}

void DrawSt(float x,float y,int color,int tocolor,int font,char message[256]){
	/*
	int FontHandle, ImageHandle, EdgeImageHandle, DrawWidth ;
	int SoftImage, EdgeSoftImage ;
	VERTEX Vertex[ 6 ] ;

	ChangeWindowMode( TRUE ) ;

	// �c�w���C�u�����̏�����
	if( DxLib_Init() < 0 )
	{
		// �G���[�����������璼���ɏI��
		return -1 ;
	}

	// �����A���`�G�C���A�X�t�H���g�̍쐬
	FontHandle = CreateFontToHandle( NULL, 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE ) ;

	// ������C���[�W��]������ ARGB8�`���̉�ʃT�C�Y�̃������C���[�W���쐬( ���p�Ɠ�� )
	SoftImage = MakeARGB8ColorSoftImage( 640, 480 ) ;
	EdgeSoftImage = MakeARGB8ColorSoftImage( 640, 480 ) ;

	// �쐬�����������C���[�W���O�œh��Ԃ�
	FillSoftImage( SoftImage, 0, 0, 0, 0 ) ;
	FillSoftImage( EdgeSoftImage, 0, 0, 0, 0 ) ;

	// ������C���[�W���������C���[�W�ɏ�������
	BltStringSoftImageToHandle( 
		0, 0, "�O���f�[�V�����e�X�g",
		SoftImage, EdgeSoftImage,
		FontHandle, FALSE ) ;

	// �`�敝���擾����
	DrawWidth = GetDrawStringWidthToHandle( "�O���f�[�V�����e�X�g", lstrlen( "�O���f�[�V�����e�X�g" ), FontHandle ) ;

	// �`�敝�ƕ`�捂���̃O���t�B�b�N�n���h�����쐬����
	ImageHandle = CreateGraphFromRectSoftImage( SoftImage, 0, 0, DrawWidth, 26 ) ;
	EdgeImageHandle = CreateGraphFromRectSoftImage( EdgeSoftImage, 0, 0, DrawWidth, 26 ) ;

	// ���̕����͗ΐF�ŕ`��
	SetDrawBright( 0, 255, 0 ) ;
	DrawGraph( 0, 0, EdgeImageHandle, TRUE ) ;
	SetDrawBright( 255, 255, 255 ) ;

	// �{�̕����� DrawPolygon ���g�p���ď㉺�ɐԂ���ɃO���f�[�V���������Ȃ���`��
	Vertex[ 0 ].x =      0.0f - 0.5f ; Vertex[ 0 ].y =  0.0f - 0.5f ;
	Vertex[ 1 ].x = DrawWidth - 0.5f ; Vertex[ 1 ].y =  0.0f - 0.5f ;
	Vertex[ 2 ].x =      0.0f - 0.5f ; Vertex[ 2 ].y = 26.0f - 0.5f ;
	Vertex[ 3 ].x = DrawWidth - 0.5f ; Vertex[ 3 ].y = 26.0f - 0.5f ;

	Vertex[ 0 ].u = 0.0f ; Vertex[ 0 ].v = 0.0f ;
	Vertex[ 1 ].u = 1.0f ; Vertex[ 1 ].v = 0.0f ;
	Vertex[ 2 ].u = 0.0f ; Vertex[ 2 ].v = 1.0f ;
	Vertex[ 3 ].u = 1.0f ; Vertex[ 3 ].v = 1.0f ;

	Vertex[ 0 ].b =   0 ; Vertex[ 0 ].g = 0 ; Vertex[ 0 ].r = 255 ; Vertex[ 0 ].a = 255 ;
	Vertex[ 1 ].b =   0 ; Vertex[ 1 ].g = 0 ; Vertex[ 1 ].r = 255 ; Vertex[ 1 ].a = 255 ;
	Vertex[ 2 ].b = 255 ; Vertex[ 2 ].g = 0 ; Vertex[ 2 ].r =   0 ; Vertex[ 2 ].a = 255 ;
	Vertex[ 3 ].b = 255 ; Vertex[ 3 ].g = 0 ; Vertex[ 3 ].r =   0 ; Vertex[ 3 ].a = 255 ;

	Vertex[ 4 ] = Vertex[ 2 ] ;
	Vertex[ 5 ] = Vertex[ 1 ] ;

	DrawPolygon( Vertex, 2, ImageHandle, TRUE, TRUE ) ;
	*/
	if(GetSkip())	DrawStringToHandle(x,y,message,color,font,tocolor);
	

	return;
}

int draw_string(float x,float y,int num,char *buffer){
//num�������̔��p����buffer��`��
	for(int i=0;i<num;i++){
		int img;
		int buf = -1;
		if(buffer[i]>=65&&buffer[i]<=90)	buf = buffer[i]-65;
		if(buffer[i]>=97&&buffer[i]<=122)	buf = buffer[i]-97;
		if(buffer[i]>=48&&buffer[i]<=57)	buf = buffer[i]-22;
		if(buffer[i]=='!')	buf = 36;
		if(buffer[i]=='?')	buf = 37;
		if(buffer[i]=='@')	buf = 38;
		if(buffer[i]=='\\')	buf = 39;
		if(buffer[i]=='+')	buf = 40;
		if(buffer[i]=='-')	buf = 41;
		if(buffer[i]=='*')	buf = 42;
		if(buffer[i]=='/')	buf = 43;
		if(buffer[i]=='_' || buffer[i]=='.')	buf = 44;
		if(buf>=0){
			if(GetSkip())	DrawGraphF(x+11*i,y,gAscii[buf],TRUE);
		}
	}

	return 0;
}

int get_length(int num,char *buffer){
//�ő�num�����̕�����buffer�̒������擾
	int l = 0;
	for(int i=0;i<num;i++){
		if(buffer[i]=='\0')	break;
		l++;
	}

	return l;
}

int draw_score(float x,float y,unsigned int num,int limit,bool zero){
//�X�R�A�����\�L�Blimit=0�Ȃ獶�l�߁B����ȊO�͉E�l�߁Bzero==true�Ȃ�0�l�߁B�P�^����Ԃ�
	int keta = 0;
	for(int i=0;(i<limit||limit==0)&&i<9;i++){
		if(num/(int)pow(10,i)>0)	keta++;
		else	break;
	}
	if(limit==0){
		if(num==0){
			if(GetSkip())	DrawGraphF(x,y,gScore[0],TRUE);
		}
		else{
			for(int i=0;i<keta;i++){
				int n = num/(int)pow(10,keta-i-1);
				num -= n * (int)pow(10,keta-i-1);
				if(GetSkip())	DrawGraphF(x+11*i,y,gScore[n],TRUE);
			}
		}
	}
	else if(zero==true){
		for(int i=0;i<limit;i++){
			int n = num/(int)pow(10,limit-i-1);
			num -= n * (int)pow(10,limit-i-1);
			if(GetSkip())	DrawGraphF(x+11*i,y,gScore[n],TRUE);
		}
	}
	else{
		if(num==0){
			if(GetSkip())	DrawGraphF(x+11*(limit-1),y,gScore[0],TRUE);
		}
		else{
			bool z = false;
			for(int i=0;i<keta;i++){
				int n = num/(int)pow(10,keta-i-1);
				num -= n * (int)pow(10,keta-i-1);
				if(z==true || n>0){
					if(GetSkip())	DrawGraphF(x+11*(limit-keta+i),y,gScore[n],TRUE);
				}
				if(n>0)		z = true;
			}
		}
	}

	return keta;
}

int draw_hit(float x,float y,int num,int img){
//�q�b�g�����\�L
	int keta = 0;
	for(int i=0;i<8;i++){
		if(num/(int)pow(10,i)>0)	keta++;
		else	break;
	}
	if(keta==0)	keta = 1;
	if(num==0&&img<2){}
	else{
		for(int i=0;i<keta;i++){
			int n = num/(int)pow(10,keta-i-1);
			num -= n * (int)pow(10,keta-i-1);
			if(img%2==1){
				if(GetSkip())	DrawGraphF(x+18*i,y,gHit2[n],TRUE);
			}
			else{
				if(GetSkip())	DrawGraphF(x+18*i,y,gHit[n],TRUE);
			}
		}
		if(img==0){
			if(GetSkip())	DrawGraphF(x+18*keta,y+5,gHit[10],TRUE);
		}
		else if(img==1){
			if(GetSkip())	DrawGraphF(x+18*keta,y+5,gHit2[10],TRUE);
		}
	}

	return keta;
}

int draw_spell(float x,float y,int num){
//�Q�b�g�X�y���J�[�h�{�[�i�X
	int keta = 0;
	for(int i=0;i<9;i++){
		if(num/(int)pow(10,i)>0)	keta++;
		else	break;
	}
	if(keta==0)	keta = 1;
	for(int i=0;i<keta;i++){
		int n = num/(int)pow(10,keta-i-1);
		num -= n * (int)pow(10,keta-i-1);
		if(GetSkip())	DrawGraphF(x+18*i,y,gSpell[n],TRUE);
	}

	return keta;
}