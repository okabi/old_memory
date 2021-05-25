#include "extern.h"

int CSave();
int CLoad();
void CSaveReset();
void CConfig();

int MainFont;
int SubFont;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow ){
        SetWindowText("東方大往生 コンフィグ");        
        ChangeWindowMode( TRUE );
        if( DxLib_Init() == -1 ) return -1; // ＤＸライブラリ初期化処理 エラーが起きたら終了
	CLoad();

	do{
		ClsDrawScreen();
		CConfig();
		CheckPushKey();
		ScreenFlip();
	}while(ProcessMessage()==0&&CheckHitKey(KEY_INPUT_ESCAPE)==0);

	CSave();	
        DxLib_End();
        return 0 ;              // ソフトの終了
}

int CSave(){
	char *name = "th00.cfg";
	FILE *fp;
	if((fp=fopen(name,"wb")) == NULL){
		char message[128];
		wsprintf(message , "データの書き込みに失敗");
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
	MainFont = CreateFontToHandle("ＭＳ ゴシック",18,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
	SubFont = CreateFontToHandle("ＭＳ ゴシック",14,-1,DX_FONTTYPE_ANTIALIASING_EDGE);
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
		wsprintf(message , "データの初期化に失敗");
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
				wsprintf(ma , "ＦＰＳを６０に固定する（推奨:する）");
				break;
			case 1:
				wsprintf(ma , "描画更新回数（推奨:毎回）");
				break;
			case 2:
				wsprintf(ma , "ＢＧＭロード方式（推奨:０）");
				break;
		}
		switch(carsol){
			case 0:
				wsprintf(sub[0] , "ＦＰＳを強制的に６０にするか、マシンに任せるかを選択");
				wsprintf(sub[1] , "６０以外でＦＰＳが安定する場合、しないを選択");		
				break;
			case 1:
				wsprintf(sub[0] , "描画更新回数を選択。処理落ちが軽減される");
				wsprintf(sub[1] , "更新回数を減らすなら、必ずＦＰＳ固定をしてください");		
				break;
			case 2:
				if(Config.bgmmode==0){
					wsprintf(sub[0] , "%d:必要に応じてロード（デフォルト）",Config.bgmmode);		
					wsprintf(sub[1] , "必要時にロードします。処理落ちは各部分に分散します。");
				}
				if(Config.bgmmode==1){
					wsprintf(sub[0] , "%d:ゲーム開始時に全てロード",Config.bgmmode);		
					wsprintf(sub[1] , "マシンによっては重くなります。処理落ちはゲーム開始時に集中します");
				}
				if(Config.bgmmode==2){
					wsprintf(sub[0] , "%d:毎回ロード",Config.bgmmode);		
					wsprintf(sub[1] , "再生のたびにロードします。曲データ保持で重くなるマシンに有効です");
				}
				break;
		}
		if(carsol==i)	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
		else		SetDrawBlendMode(DX_BLENDMODE_ALPHA,120);
		DrawStringToHandle(50,base_y+st_size*i,ma,GetColor(255,255,255),MainFont);
		if(i==0){
			size = GetDrawFormatStringWidthToHandle(MainFont,ma);
			if(Config.fps==0)	DrawStringToHandle(70+size,base_y+st_size*i,"← する 　→",GetColor(255,255,100),MainFont);
			else			DrawStringToHandle(70+size,base_y+st_size*i,"← しない →",GetColor(255,255,100),MainFont);
		}
		if(i==1){
			size = GetDrawFormatStringWidthToHandle(MainFont,ma);
			if(Config.drawmode==0)	DrawStringToHandle(70+size,base_y+st_size*i,"← 　毎回 　→",GetColor(255,255,100),MainFont);
			if(Config.drawmode==1)	DrawStringToHandle(70+size,base_y+st_size*i,"← ２分の１ →",GetColor(255,255,100),MainFont);
			if(Config.drawmode==2)	DrawStringToHandle(70+size,base_y+st_size*i,"← ３分の１ →",GetColor(255,255,100),MainFont);
		}
		if(i==2){
			size = GetDrawFormatStringWidthToHandle(MainFont,ma);
			if(Config.bgmmode==0)	DrawStringToHandle(70+size,base_y+st_size*i,"← ０ →",GetColor(255,255,100),MainFont);
			if(Config.bgmmode==1)	DrawStringToHandle(70+size,base_y+st_size*i,"← １ →",GetColor(255,255,100),MainFont);
			if(Config.bgmmode==2)	DrawStringToHandle(70+size,base_y+st_size*i,"← ２ →",GetColor(255,255,100),MainFont);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	}
	for(int a=0;a<2;a++){
		DrawStringToHandle(50,base_y2+18*a,sub[a],GetColor(255,255,255),SubFont);
	}		
	char message[128];
	wsprintf(message , "Esc:終了");
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