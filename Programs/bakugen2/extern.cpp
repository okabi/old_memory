#include "extern.h"
#include "menu.h"
#include "map.h"
#include "player.h"
#include "net.h"

bool bOnline;
char LOG[MAX_LOG];
int c_key[C_KEY_NUM];
int c_pad[4][C_PAD_NUM];
int rand_seed;
int Gcount;
int Rcount;
int Rcount2;
int Pcount;//ポーズカウント
float shake_x;
float shake_y;
int HangonType;//反魂蝶プレイヤー
int HangonLife;
int TimeStopType;
bool bTimeStop;//咲夜の技
bool bSecondSun;
bool bIceStream;
bool bTreasure;
int TreasureCount;
bool bYukari;//紫スペカ
bool bAICheck;
int Hanten;//紫スペカ
int MapFlash;//優曇華スペカ

bool replay_play;//リプレイ再生か？
int replay_play_num;//何番のリプレイ再生か？
int replay_count;//リプレイ保存要素
REPLAYDATA Replay[REPLAY_NUM];
REPLAYDATA SReplay;
int repeat;
int repeat_max;

void WriteLog(char log[]);
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
void change_scene(SCENE change);
void GameLoad();


SAVEDATA SAVE;
PROFILEDATA Profile[PROFILE_NUM];

SCENE scene;

void WriteLog(char log[]){
	FILE *fp;
	fp = fopen("ログ.txt","a");
	fputs(log,fp);
	fputc('\n',fp);
	fclose(fp);
	
	return;
}

void SShake(int type, float level){
	static int count;
	if(type==0){//全体
		shake_x = level * sin(Radian(50*count,TRUE));
		shake_y = level * sin(Radian(70*count,TRUE));
	}
	else if(type==1){//x軸
		shake_x = level * sin(Radian(50*count,TRUE));
	}
	else if(type==2){//y軸
		shake_y = level * sin(Radian(70*count,TRUE));
	}
	count++;
	return;
}

void SCheckPlayTime(){
	DATEDATA D;
	static int time = 0;
	GetDateTime(&D);
	if(D.Sec!=time){
		time = D.Sec;
		SAVE.PlayTime++;
		if(scene==GAME&&replay_play==false){
			for(int i=0;i<4;i++){
				if(Player[i].bMan==true&&SAVE.User[i]!=-1){
					Profile[SAVE.User[i]].playtime++;
				}
			}
		}
	}
	if(SAVE.PlayTime>3599999){
		SAVE.PlayTime = 3599999;
	}
	/*
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int color = GetColor(255,255,255);
	DrawFormatString(550,445,color,"Time %d",SAVE.PlayTime);
	*/

	return;
}

int SSave(){
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	char *name = "score2.dat";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "セーブに失敗");
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
	for(int i=0;i<PROFILE_NUM;i++){
		if(Profile[i].exist==true){
			char fi[128];
			wsprintf(fi,"profile/player%d.dat",i+1);
			fp = fopen(fi,"wb");
			crypt(&Profile[i],sizeof(PROFILEDATA),0xF7);
			fwrite(&Profile[i],sizeof(PROFILEDATA),1,fp);
			crypt(&Profile[i],sizeof(PROFILEDATA),0xF7);
			fclose(fp);
		}
	}
	
	return 0;
}

void SLoad(){
	/*
	if(1){
		char *name = "ログ.txt";
		FILE *fp;
		fp=fopen(name,"w");
		fclose(fp);
	}
	*/
	rand_seed = time(NULL);
	Gcount = 0;
	shake_x = 0;
	shake_y = 0;
	CreateMaskScreen();
	SetUseMaskScreenFlag(FALSE);
	SetDXArchiveExtension("dat");
	ChangeFontType(DX_FONTTYPE_EDGE);
        SetFontSize(10);
	SetAlwaysRunFlag(TRUE);
	ChangeFont("MS UI Gothic");
 	char message[32];
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	wsprintf(message , "Now Loading...");
	int size = GetDrawStringWidth(message,14);
	DrawString(640-size,480-12,message,GetColor(255,255,255));			
	ScreenFlip();
	char *name = "score2.dat";
	FILE *fp;
	if((fp=fopen(name,"rb")) == NULL){
		SSaveReset();
		fp=fopen(name,"rb");
	}
	
	fread(&SAVE,sizeof(SAVEDATA),1,fp);
	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	SetGraphDataShavedMode(DX_SHAVEDMODE_DITHER);
	
	fclose(fp);

	for(int i=0;i<REPLAY_NUM;i++){
		char name[64];
		wsprintf(name ,"replay/baku_%02d.rpy",i+1);
		FILE *fp;
		if((fp=fopen(name,"rb")) == NULL){
			Replay[i].exist = false;
			fclose(fp);
			continue;
		}
		
		fread(&Replay[i],sizeof(REPLAYDATA)-4*REPLAY_ELEMENT_NUM,1,fp);
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		int Element = Replay[i].element_num;
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		for(int a=0;a<Element;a++){
			for(int b=0;b<4;b++){
				Replay[i].replay_element[a][b] = fgetc(fp);
			}
		}
		crypt(&Replay[i],sizeof(REPLAYDATA),0xF7);
		
		fclose(fp);
	}	
	for(int i=0;i<PROFILE_NUM;i++){
		Profile[i].exist = false;
		char name[64];
		wsprintf(name ,"profile/player%d.txt",i+1);
		FILE *fp2;
		if((fp2=fopen(name,"r"))!=NULL){
			FILE *fp;
			wsprintf(name ,"profile/player%d.dat",i+1);
			if((fp=fopen(name,"rb")) == NULL){
				Profile[i].exist = true;
				Profile[i].ID = get_rand(0xffff);
				Profile[i].rate = 5000;
				Profile[i].max_rate = 5000;
				Profile[i].match_num = 0;
				Profile[i].win_num = 0;
				for(int j=0;j<3;j++)	Profile[i].lose_num[j] = 0;
				Profile[i].playtime = 0;
				Profile[i].death_average = 0;
				Profile[i].first_death_num = 0;
				Profile[i].sadon_match_num = 0;
				Profile[i].sadon_num = 0;
				Profile[i].kill_num = 0;
				Profile[i].miso_kill_num = 0;
				Profile[i].killme_num = 0;
				Profile[i].death_num = 0;
				Profile[i].danmaku_num = 0;
				Profile[i].max_renbaku = 0;
				for(int j=0;j<12;j++)	Profile[i].chara_num[j] = 0;
				for(int j=0;j<PROFILE_NUM;j++){
					Profile[i].player_match_num[j] = 0;
					Profile[i].player_win_num[j] = 0;
					Profile[i].player_lose_num[j] = 0;
					Profile[i].player_ID[j] = -1;
					for(int a=0;a<MAX_NAME;a++){
						Profile[i].player_name[j][a] = '\0';
					}
				}
				fgets(Profile[i].name,MAX_NAME-1,fp2);
				fclose(fp);
				fp = fopen(name,"wb");
				crypt(&Profile[i],sizeof(PROFILEDATA),0xF7);
				fwrite(&Profile[i],sizeof(PROFILEDATA),1,fp);
				crypt(&Profile[i],sizeof(PROFILEDATA),0xF7);
				fclose(fp);
				fclose(fp2);
				continue;
			}
			else{			
				fread(&Profile[i],sizeof(PROFILEDATA),1,fp);
				crypt(&Profile[i],sizeof(PROFILEDATA),0xF7);
				fgets(Profile[i].name,MAX_NAME-1,fp2);
				fclose(fp);
		        }
		}
		fclose(fp2);
	}
	for(int i=0;i<4;i++){
		if(Profile[SAVE.User[i]].exist==false)	SAVE.User[i] = -1;
	}	
	return;
}

void SSaveReset(){
	for(int i=0;i<4;i++){
		SAVE.Key_Bomb[i] = PAD_A;
		SAVE.Key_Spell[i] = PAD_B;
		SAVE.Key_Pause[i] = PAD_START;
		SAVE.User[i] = -1;
	}
	SAVE.Key_Type[0] = DX_INPUT_PAD1;
	SAVE.Key_Type[1] = DX_INPUT_PAD2;
	SAVE.Key_Type[2] = DX_INPUT_PAD3;
	SAVE.Key_Type[3] = DX_INPUT_PAD4;
	SAVE.Bgm = 100;
	SAVE.Sound = 50;
	SAVE.PlayCount = 0;
	SAVE.PlayTime = 0;
	SAVE.MatchNum = 3;
	SAVE.MatchTime = 2;

	crypt(&SAVE,sizeof(SAVEDATA),0xF7);
	char *name = "score2.dat";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "データの初期化に失敗");
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
//何フレームの間ボタンが押されているか。0は押されていない。
	bool runflag = GetWindowActiveFlag();
	char check[C_KEY_NUM];
	GetHitKeyStateAll(check);
	for(int i=0;i<C_KEY_NUM;i++){
		if(check[i]==1&&runflag==true)	c_key[i]++;
		else		c_key[i] = 0; 
	}
	int key = GetJoypadInputState(DX_INPUT_PAD1);
	int key2 = GetJoypadInputState(DX_INPUT_PAD2);
	int key3 = GetJoypadInputState(DX_INPUT_PAD3);
	int key4 = GetJoypadInputState(DX_INPUT_PAD4);
	for(int i=0;i<C_PAD_NUM;i++){
		int a = 1;
		for(int b=0;b<i;b++){	a *= 2;	}
		if((key&a)&&runflag==true)	c_pad[0][i]++;
		else		c_pad[0][i] = 0;
		if((key2&a)&&runflag==true)	c_pad[1][i]++;
		else		c_pad[1][i] = 0;
		if((key3&a)&&runflag==true)	c_pad[2][i]++;
		else		c_pad[2][i] = 0;
		if((key4&a)&&runflag==true)	c_pad[3][i]++;
		else		c_pad[3][i] = 0;
	}
		
	return;
}

void Fps(){
	float frame = 60.0;
	//if(c_key[KEY_INPUT_RETURN]>0)	frame = 30.0;
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
			wsprintf(path , "snapshot/baku_%03d.bmp",i+1);
			if(PathFileExists(path)==false){
				break;
			}
		}
		SaveDrawScreen(0,0,640,480,path);
	}
	return;
}

int get_rand(int max){
//0~maxまでの乱数を取得
	rand_seed ++;
	SRand(rand_seed);
	int rand = GetRand(max);
	return rand;
}

float Radian(float d, int flag){
//TRUE:度→ラジアン変換、FALSE:ラジアン→度変換
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

	// ＤＸライブラリの初期化
	if( DxLib_Init() < 0 )
	{
		// エラーが発生したら直ちに終了
		return -1 ;
	}

	// 縁つきアンチエイリアスフォントの作成
	FontHandle = CreateFontToHandle( NULL, 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE ) ;

	// 文字列イメージを転送する ARGB8形式の画面サイズのメモリイメージを作成( 縁用と二つ )
	SoftImage = MakeARGB8ColorSoftImage( 640, 480 ) ;
	EdgeSoftImage = MakeARGB8ColorSoftImage( 640, 480 ) ;

	// 作成したメモリイメージを０で塗りつぶす
	FillSoftImage( SoftImage, 0, 0, 0, 0 ) ;
	FillSoftImage( EdgeSoftImage, 0, 0, 0, 0 ) ;

	// 文字列イメージをメモリイメージに書き込む
	BltStringSoftImageToHandle( 
		0, 0, "グラデーションテスト",
		SoftImage, EdgeSoftImage,
		FontHandle, FALSE ) ;

	// 描画幅を取得する
	DrawWidth = GetDrawStringWidthToHandle( "グラデーションテスト", lstrlen( "グラデーションテスト" ), FontHandle ) ;

	// 描画幅と描画高さのグラフィックハンドルを作成する
	ImageHandle = CreateGraphFromRectSoftImage( SoftImage, 0, 0, DrawWidth, 26 ) ;
	EdgeImageHandle = CreateGraphFromRectSoftImage( EdgeSoftImage, 0, 0, DrawWidth, 26 ) ;

	// 縁の部分は緑色で描画
	SetDrawBright( 0, 255, 0 ) ;
	DrawGraph( 0, 0, EdgeImageHandle, TRUE ) ;
	SetDrawBright( 255, 255, 255 ) ;

	// 本体部分は DrawPolygon を使用して上下に赤から青にグラデーションさせながら描画
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
	if(repeat==9||scene!=GAME||Rcount>=0)	DrawStringToHandle(x,y,message,color,font,tocolor);
	

	return;
}

int draw_string(float x,float y,int num,char *buffer){
//num文字数の半角文字bufferを描画
	if(Pcount==0&&repeat!=9&&scene==GAME&&Rcount==0)	return 0;
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
		if(buffer[i]=='_')	buf = 44;
		if(buf>=0)	DrawGraphF(x+11*i,y,gAscii[buf],TRUE);
	}

	return 0;
}

void change_scene(SCENE change){
	if(scene!=change){
		if(change==SETTINGA){
			if(scene==SETTINGB)	settingA_count = 30;
			else			settingA_count = 0;
			settingA_carsol = 0;		
		}
		if(change==SETTINGB){
			settingB_count = 0;
			for(int i=0;i<4;i++){
				settingB_flag[i] = false;
			}
			bool flag = false;
			for(int i=0;i<4;i++){
				if(Player[i].bMan==true){
					flag = true;
					break;
				}
			}
			if(Player[0].bMan==true)	settingB_carsol[0] = 0;
			else{
				settingB_carsol[0] = -1;		
				if(flag==false)	settingB_carsol[0] = 0;
			}
			if(Player[1].bMan==true)	settingB_carsol[1] = 1;
			else				settingB_carsol[1] = -1;		
			if(Player[2].bMan==true)	settingB_carsol[2] = 2;
			else				settingB_carsol[2] = -1;		
			if(Player[3].bMan==true)	settingB_carsol[3] = 3;
			else				settingB_carsol[3] = -1;		
			settingC_count2 = 0;
		}
		if(change==SETTINGC){
			settingC_count = 0;
			settingC_count2 = 0;
			settingC_carsol[0] = MAP_NUM;
			settingC_carsol[1] = -1;
			settingC_carsol[2] = -1;
		}
		if(change==NETSETTINGA){
			if(scene==NETSETTINGB)	netsettingA_count = 30;
			else			netsettingA_count = 0;
			netsettingA_carsol[0] = 0;		
			netsettingA_carsol[1] = -1;
			for(int i=0;i<MAX_LOG;i++){
				LOG[i] = '\0';
			}		
		}
		if(change==NETSETTINGB){
			for(int i=0;i<2;i++)	NetWork.SB.bSettingBEnd[i] = false;
			netsettingB_count = 0;
			if(NetWork.host_num==-1)	netsettingB_seleca = 0;
			else				netsettingB_seleca = 7;
			for(int i=0;i<9;i++){
				if(i<4){
					if(NetWork.NFD[0].connect_num<=i)	netsettingB_carsol[i] = i;
					else				netsettingB_carsol[i] = NetWork.NFD[0].connect_num+4;
				}
				else if(i==4)	netsettingB_carsol[i] = MAP_NUM;		
				else if(i==5)	netsettingB_carsol[i] = SAVE.MatchNum;		
				else if(i==6)	netsettingB_carsol[i] = SAVE.MatchTime;		
				else		netsettingB_carsol[i] = -1;		
			}
			for(int i=0;i<MAX_LOG;i++){
				LOG[i] = '\0';
			}
			NetWork.SBnum = 0;
		}
		if(scene==GAME){
			for(int i=0;i<DIRECTORY_NUM;i++){
				for(int j=0;j<BGM_NUM[i];j++){
					if(strcmp(BgmName[i][j],"53ミニッツの青い海")==0){
						play_bgm(i,j);
					} 
				}
			}
		}
		if(change==GAME){
			for(int i=0;i<PLAYER_NUM;i++){
				Player[i].victory = 0;
				SReplay.player[i] = Player[i].get_chara();
				SReplay.player_color[i] = Player[i].color;
				SReplay.bMan[i] = Player[i].bMan;
				if(Player[i].bMan==true&&SAVE.User[i]!=-1){
					wsprintf(SReplay.name[i],"%s",Profile[SAVE.User[i]].name);
				}
				else if(Player[i].bMan==true){
					wsprintf(SReplay.name[i],"ゲスト%d",i+1);
				}
				else{
					wsprintf(SReplay.name[i],"COM%d",i+1);
				}
			}
			SReplay.element_num = 0;
			SReplay.match = 1;
			SReplay.matchnum = SAVE.MatchNum;
			SReplay.matchtime = SAVE.MatchTime;
			SReplay.stage = settingC_carsol[0];
			SReplay.bgm[0] = settingC_carsol[1];
			SReplay.bgm[1] = settingC_carsol[2];
			SReplay.exist = true;
			DATEDATA D;
			GetDateTime(&D);
			SReplay.year = D.Year;
			SReplay.month = D.Mon;
			SReplay.day = D.Day;
			SReplay.hour[0] = D.Hour;
			SReplay.minute[0] = D.Min;
			SReplay.second[0] = D.Sec;			
			SReplay.hour[1] = D.Hour;
			SReplay.minute[1] = D.Min;
			SReplay.second[1] = D.Sec;			
			replay_count = 0;
			SReplay.start_count[SReplay.match-1] = replay_count;
			if(replay_play==false)	SAVE.PlayCount++;
		}
		scene = change;
	}

	return;
}
