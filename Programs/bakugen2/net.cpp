#include "DxLib.h"
#include "net.h"
#include "player.h"
#include "menu.h"

CLASS_NETWORK NetWork;


void CLASS_NETWORK::Load(){
	Reset();
	for(int i=0;i<4;i++){
		for(int j=0;j<3;j++)	draw_IP[i][j] = 0;
	}
	for(int i=0;i<5;i++){
		draw_port[i] = 0;
	}
	FILE *fp;
	if((fp=fopen("IP.txt","r"))!=NULL){
		for(int i=0;i<4;i++){
			char get[4] = {'\0','\0','\0','\0'};
			for(int j=0;j<4;j++){
				get[j] = fgetc(fp);
				if(get[j]=='.'||get[j]=='\n'){
					get[j] = '\0';
					break;
				}
			}
			for(int a=0,n=0;a<4;a++){
				if(get[3-a]!='\0'){
					draw_IP[i][2-n] = get[3-a]-48;
					n++;
				}
			}	
		}
		char get[6] = {'\0','\0','\0','\0','\0','\0'};
		for(int i=0;i<6;i++){
			get[i] = fgetc(fp);
			if(get[i]==EOF){
				get[i] = '\0';
				break;
			}
		}
		for(int a=0,n=0;a<6;a++){
			if(get[5-a]!='\0'){
				draw_port[4-n] = get[5-a]-48;
				n++;
			}
		}	
	}
	fclose(fp);

	return;
}

void CLASS_NETWORK::Reset(){
//最初の設定時に初期化される
	for(int i=0;i<MAX_CONNECT;i++){
		CloseNetWork(connect_tcp[i]);
		connect_tcp[i] = -1;
	}
	DeleteUDPSocket(connect_udp);
	connect_udp = -1;
	color = GetColor(255,255,255);
	host_num = -1;
	player_num = -1;
	message_handle = -1;
	for(int i=0;i<4;i++){
		hostIP[i] = 0;
	}
	hostport = 0;
	wait_count = -1; 
	bChat = false;
	bSettingAEnd = false;
	for(int i=0;i<2;i++)	SB.bSettingBEnd[i] = false;

	for(int i=0;i<MAX_CONNECT+1;i++){
		for(int j=0;j<MAX_NAME;j++)	NFD[i].name[j] = '\0';
		NFD[i].connect_num = 0;
		NFD[i].player_num = -1;
		NFD[i].color = 0;
		NFD[i].rate = 0;
		for(int j=0;j<4;j++)	NFD[i].IP[j] = -1;
	}

	for(int i=0;i<MAX_LOG;i++){
		LOG[i] = '\0';
	}
	if(SAVE.User[0]==-1){
		wsprintf(LOG,"ERROR:１Ｐがゲストでオンライン対戦は不可能");
	}
	else{
		wsprintf(NFD[0].name,"%s",Profile[SAVE.User[0]].name);
		NFD[0].rate = Profile[SAVE.User[0]].rate;
	}		

	return;
}

void CLASS_NETWORK::ChatFunction(){
//チャット処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	//メッセージ入力欄の確立
	static bool before_bChat = bChat;
	static int dummy_handle = MakeKeyInput(MAX_MESSAGE-1, TRUE, FALSE, FALSE);//非アクティブ状態にするためのダミーハンドル
	if(message_handle==-1){
		message_handle = MakeKeyInput(MAX_MESSAGE-1, TRUE, FALSE, FALSE);
		SetActiveKeyInput(message_handle);
	}
	if(bChat==false)	SetActiveKeyInput(dummy_handle);
	if(bChat!=before_bChat){
		if(bChat==true)	SetActiveKeyInput(message_handle);	
	}
	before_bChat = bChat;

	//入力処理
	if(bChat==true){	
		DrawKeyInputString(0, 450, message_handle);
		int condition = CheckKeyInput(message_handle);
		if(condition!=0){
			if(condition==1){//送信
				NETCHATDATA P;
				P.message[0] = '\0';
				GetKeyInputString(P.message, message_handle);
				if(P.message[0]!='\0'){
					char me[MAX_MESSAGE+MAX_NAME+8];
					wsprintf(me,"%s:%s",Profile[SAVE.User[0]].name, P.message);
					AddMessage(me,NFD[0].color);
				}
			}
			else if(condition==2){}//全削除
			DeleteKeyInput(message_handle);
			message_handle = -1;
		}
	}

	//履歴表示
	for(int i=0;i<HISTORY_NUM;i++){
		int size = GetDrawStringWidthToHandle(HisChat.message[i],MAX_MESSAGE+MAX_NAME+8,font_default);
		if(scene==GAME&&player_num!=-1){
			float x,y;
			Player[player_num].get_xy(&x,&y);
			if(x<320){
				DrawSt(640-size,420-15*i,HisChat.color[i],0,font_default,HisChat.message[i]);
			}
			else{
				DrawSt(640-size,420-15*i,HisChat.color[i],0,font_default,HisChat.message[i]);
			}
		}
		else{
			DrawSt(0,420-15*i,HisChat.color[i],0,font_default,HisChat.message[i]);
		}
	}
	
	//接続確認処理
	int con = GetLostNetWork();
	if(con!=-1){
		for(int i=0;i<MAX_CONNECT;i++){
			if(con==connect_tcp[i]){
				/*
				if(i==host_num){
					char message[128];
					wsprintf(message , "サーバとの通信が途絶えました。\nゲームを終了しタイトル画面に戻ります。");
					MessageBox(NULL, message, "通信エラー",	MB_OK |	MB_ICONINFORMATION | MB_TOPMOST);
					for(int j=0;j<MAX_CONNECT;j++){
						if(connect_tcp[j]!=-1){
							CloseNetWork(connect_tcp[j]);
							connect_tcp[j] = -1;
						}
					}
					DeleteUDPSocket(connect_udp);
					NFD[0].connect_num = 0;
					connect_udp = -1;
					change_scene(TITLE);
					return;
				}
				*/
				CloseNetWork(connect_tcp[i]);
				NFD[0].connect_num--;
				connect_tcp[i] = -1;
				/*
				char message[128];
				wsprintf(message , "通信エラーが発生しました。\nタイトル画面に戻ります");
				MessageBox(NULL, message, "通信エラー",	MB_OK |	MB_ICONINFORMATION | MB_TOPMOST);
				*/
				DeleteUDPSocket(connect_udp);
				connect_udp = -1;
				change_scene(TITLE);
				return;
				/*
				char me[MAX_MESSAGE];
				wsprintf(me, "============%sとの通信が途絶えました============",NFD[i].name[i]);
				AddMessage(me,GetColor(255,255,150));
				if(NFD[0].connect_num==0){
					char message[128];
					wsprintf(message , "通信相手が一人もいません。\nゲームを終了しタイトル画面に戻ります。");
					MessageBox(NULL, message, "通信エラー",	MB_OK |	MB_ICONINFORMATION | MB_TOPMOST);
					DeleteUDPSocket(connect_udp);
					connect_udp = -1;
					change_scene(TITLE);
					return;
				}
				*/
			}
		}
	}
	/*
	con = GetNewAcceptNetWork();
	if(con!=-1){
		for(int i=0;i<MAX_CONNECT;i++){
			if(connect_tcp[i]==-1){
				NFD[0].connect_num++;
				connect_tcp[i] = con;
				NETFIRSTDATA P;
				while(NetWorkRecv(connect_tcp[host_num], &P, sizeof(NETFIRSTDATA))==-1){}
				for(int j=0;j<MAX_NAME;j++){
					NFD[i].name[j] = P.name[j];
				}
				NFD[i].color = P.color;
				NFD[i].rate = P.rate;
				for(int j=0;j<4;j++){
					NFD[i].IP[j] = P.IP[j];
				}
				char me[MAX_MESSAGE];
				wsprintf(me, "============%sと通信を開始します============",NFD[i].name);
				AddMessage(me,GetColor(255,255,100));
				break;
			}
		}
	}
	*/

	//クライアント情報取得処理
	for(int i=0;i<MAX_CONNECT;i++){
		if(connect_tcp[i]!=-1){
			NETCHATDATA P; 
			if(NetWorkRecv(connect_tcp[i], &P, sizeof(NETCHATDATA))!=-1){
				char me[MAX_MESSAGE+MAX_NAME+8];
				wsprintf(me,"%s", P.message);
				AddMessage(me,NFD[i+1].color,false);
			}
		}
	}


	return;
}

void CLASS_NETWORK::AddMessage(char me[],int co,bool flag){
	if(co==GetColor(255,255,100))	play_sound(22);
	else if(co!=GetColor(255,255,150))	play_sound(23);
	for(int i=HISTORY_NUM-1;i>0;i--){
		for(int j=0;j<MAX_MESSAGE;j++){
			HisChat.message[i][j] = HisChat.message[i-1][j];
		}
		HisChat.color[i] = HisChat.color[i-1];
	}
	wsprintf(HisChat.message[0], "%s",me);
	HisChat.color[0] = co;
	NETCHATDATA P;
	for(int i=0;i<MAX_MESSAGE+MAX_NAME+8;i++){
		P.message[i] = me[i];
	}
	if(flag==true){
		for(int i=0;i<MAX_CONNECT;i++){//チャット情報の送信
			if(connect_tcp[i]!=-1){
				NetWorkSend(connect_tcp[i], &P, sizeof(NETCHATDATA));
			}
		}
	}
	return;
}

void CLASS_NETWORK::HostFunction(){
	host_num = -1;
	int error = -1;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);

	//入力状態取得
	static int bomb=2,cancel=2;
	int check_num = -1;
	if(SAVE.Key_Type[0]==DX_INPUT_PAD1)		check_num = 0;
	else if(SAVE.Key_Type[0]==DX_INPUT_PAD2)	check_num = 1;
	else if(SAVE.Key_Type[0]==DX_INPUT_PAD3)	check_num = 2;
	else if(SAVE.Key_Type[0]==DX_INPUT_PAD4)	check_num = 3;
	if(check_num!=-1){
		if(c_pad[check_num][SAVE.Key_Bomb[0]]>0)	bomb ++;
		else	bomb = 0;
		if(c_pad[check_num][SAVE.Key_Spell[0]]>0)	cancel ++;
		else	cancel = 0;
	}
	else{
		if(c_key[KEY_INPUT_RETURN]>0)	bomb ++;
		else if(c_key[KEY_INPUT_Z]>0)	bomb ++;
		else	bomb = 0;
		if(c_key[KEY_INPUT_X]>0)	cancel ++;
		else	cancel = 0;
	}

	//入力処理とUDPソケット取得
	if(wait_count==0){
		hostport = 0;
		for(int j=0;j<5;j++){
			hostport += draw_port[j] * pow(10,4-j);
		}
		if(PreparationListenNetWork(hostport)==-1){
			error = 0;
		}
		else{
			connect_udp = MakeUDPSocket(hostport);
			if(connect_udp==-1)	error = 2;  
			else	wait_count = 1;
		}
	}
	else if(bomb==1&&NFD[0].connect_num>0){
		hostport = 0;
		for(int j=0;j<5;j++){
			hostport += draw_port[j] * pow(10,4-j);
		}
		wait_count = -1;
		bSettingAEnd = true;	
		StopListenNetWork();
		//クライアントにデータを送信
		for(int i=0;i<MAX_CONNECT;i++){
			if(connect_tcp[i]!=-1){
				IPDATA P;
				P.d1 = NFD[i+1].IP[0];
				P.d2 = NFD[i+1].IP[1];
				P.d3 = NFD[i+1].IP[2];
				P.d4 = NFD[i+1].IP[3];
				while(NetWorkSendUDP(connect_udp, P, hostport, &bSettingAEnd, sizeof(bool))!=sizeof(bool)){}
			}
		}
		count = 0;	
		change_scene(NETSETTINGB);
		return;
	}
	else if(cancel==1&&NFD[0].connect_num==0){
		play_sound(2);
		wait_count = -1;
		StopListenNetWork();
		if(DeleteUDPSocket(connect_udp)==0){
			connect_udp = -1;
		}
		else{
			connect_udp = -1;
			error = 3;
		}
	}

	//クライアントとの接続処理
	if(wait_count>0){
		char mes[64];
		wsprintf(mes , "サーバ:接続受付中...");
		int size = GetDrawStringWidthToHandle(mes,64,font_default);
		DrawSt(320-size/2,300,GetColor(255,150,150),0,font_default,mes);
		wait_count++;
		int con = GetNewAcceptNetWork();
		if(con!=-1){
			bool flag = false;
			for(int i=0;i<MAX_CONNECT;i++){
				if(connect_tcp[i]==-1){
					wait_count = 1;
					play_sound(22);
					connect_tcp[i] = con;
					NFD[0].connect_num++;
					NFD[0].color = GetColor(255,255,255);
					wsprintf(NFD[0].name, "%s", Profile[SAVE.User[0]].name);
					NETFIRSTDATA P;
					while(NetWorkRecv(connect_tcp[i], &NFD[i+1], sizeof(NETFIRSTDATA))==-1){}//新規クライアント情報の取得
					if(i==1)	NFD[i+1].color = GetColor(255,50,50);
					if(i==2)	NFD[i+1].color = GetColor(50,50,255);
					if(i==3)	NFD[i+1].color = GetColor(255,255,50);
					if(i==4)	NFD[i+1].color = GetColor(50,255,50);
					if(i==5)	NFD[i+1].color = GetColor(50,255,255);
					if(i==6)	NFD[i+1].color = GetColor(255,50,255);
					if(i==7)	NFD[i+1].color = GetColor(255,150,150);
					if(i==8)	NFD[i+1].color = GetColor(255,200,50);
					if(i==9)	NFD[i+1].color = GetColor(150,150,150);
					IPDATA I;
					while(GetNetWorkIP(connect_tcp[i], &I)==-1){}
					NFD[i+1].IP[0] = I.d1; 
					NFD[i+1].IP[1] = I.d2; 
					NFD[i+1].IP[2] = I.d3; 
					NFD[i+1].IP[3] = I.d4;
					NFD[i+1].connect_num = NFD[0].connect_num; 
					NFD[i+1].player_num = -1; 
					NetWorkSend(connect_tcp[i], &NFD[i+1], sizeof(NETFIRSTDATA));//新規クライアントに新規クライアントを送る
					NetWorkSend(connect_tcp[i], &NFD[0], sizeof(NETFIRSTDATA));//新規クライアントにホスト情報を送る
					for(int j=0;j<MAX_CONNECT;j++){//新規クライアントに既存参加者情報を送る
						if(connect_tcp[j]!=-1&&i!=j){
							NetWorkSend(connect_tcp[i], &NFD[j+1], sizeof(NETFIRSTDATA));
						}
					}
					for(int j=0;j<MAX_CONNECT;j++){//既存の参加者に新規クライアント情報を送る
						if(connect_tcp[j]!=-1&&i!=j){
							NetWorkSend(connect_tcp[j], &NFD[i+1], sizeof(NETFIRSTDATA));
						}
					}
					flag = true;
					break;
				}
			}
			if(flag==false){
				NETFIRSTDATA P;
				P.IP[0] = -1;
				NetWorkSend(con, &P, sizeof(NETFIRSTDATA));
			}
		}
	}
	if(wait_count==3600){
		if(NFD[0].connect_num==0)	error = 1;
		else{
			hostport = 0;
			for(int j=0;j<5;j++){
				hostport += draw_port[j] * pow(10,4-j);
			}
			wait_count = -1;
			bSettingAEnd = true;	
			StopListenNetWork();
			//クライアントにデータを送信
			for(int i=0;i<MAX_CONNECT;i++){
				if(connect_tcp[i]!=-1){
					IPDATA P;
					P.d1 = NFD[i+1].IP[0];
					P.d2 = NFD[i+1].IP[1];
					P.d3 = NFD[i+1].IP[2];
					P.d4 = NFD[i+1].IP[3];
					while(NetWorkSendUDP(connect_udp, P, hostport, &bSettingAEnd, sizeof(bool))!=sizeof(bool)){}
				}
			}	
			count = 0;
			change_scene(NETSETTINGB);
		}
		wait_count = -1;
	}
	//エラー表示
	if(error>=0){
		play_sound(24);
		StopListenNetWork();
		if(connect_udp!=-1){
			if(DeleteUDPSocket(connect_udp)==0){
				connect_udp = -1;
			}
			else{
				connect_udp = -1;
				error = 3;
			}
		}	
		wait_count = -1;
		if(error==0)	wsprintf(LOG, "ERROR:ポート開放出来ない、或いは既に使われているポート（ＴＣＰ）");
		if(error==1){
			wsprintf(LOG, "ERROR:１分間接続要求が無かった");
		}
		if(error==2)	wsprintf(LOG, "ERROR:ポート開放出来ない、或いは既に使われているポート（ＵＤＰ）");
		if(error==3)	wsprintf(LOG, "PROGRAMMING ERROR:ポート閉鎖に失敗（ＵＤＰ）");
	}

	return;
}

void CLASS_NETWORK::ClientFunction(){
	int error = -1;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	
	//接続処理
	if(host_num==-1){
		char mes[64];
		wsprintf(mes , "クライアント:指定ＩＰに接続中...");
		int size = GetDrawStringWidthToHandle(mes,64,font_default);
		DrawSt(320-size/2,300,GetColor(255,150,150),0,font_default,mes);
		ScreenFlip();
		for(int i=0;i<4;i++){
			hostIP[i] = 0;
			for(int j=0;j<3;j++){
				hostIP[i] += draw_IP[i][j] * pow(10,2-j);
			}
		}
		hostport = 0;
		for(int j=0;j<5;j++){
			hostport += draw_port[j] * pow(10,4-j);
		}
		IPDATA IP;
		IP.d1 = hostIP[0];
		IP.d2 = hostIP[1];
		IP.d3 = hostIP[2];
		IP.d4 = hostIP[3];
		connect_udp = MakeUDPSocket(hostport);
		if(connect_udp==-1){
			error = 2;
		}
		else{
			for(int i=0;i<MAX_CONNECT;i++){
				if(connect_tcp[i]==-1){
					error = -1;
					connect_tcp[i] = ConnectNetWork(IP, hostport);
					if(connect_tcp[i]==-1){
						error = 1; 
					}
					else{
						play_sound(22);
						host_num = i;
						NetWorkSend(connect_tcp[i], &NFD[0], sizeof(NETFIRSTDATA));
						while(NetWorkRecv(connect_tcp[i], &NFD[0], sizeof(NETFIRSTDATA))==-1){}//自己情報の取得
						while(NetWorkRecv(connect_tcp[i], &NFD[i+1], sizeof(NETFIRSTDATA))==-1){}//ホスト情報の取得
						NFD[i+1].IP[0] = hostIP[0];
						NFD[i+1].IP[1] = hostIP[1];
						NFD[i+1].IP[2] = hostIP[2];
						NFD[i+1].IP[3] = hostIP[3];
						for(int j=0;j<NFD[0].connect_num-1;j++){
							for(int a=0;a<MAX_CONNECT;a++){
								if(connect_tcp[a]==-1){
									while(NetWorkRecv(connect_tcp[host_num], &NFD[a+1], sizeof(NETFIRSTDATA))==-1){}//既存参加者情報の取得
								}
							}
						}
					}              
					break;
				}
			}
		}
	}
	else{
		char mes[64];
		wsprintf(mes , "クライアント:サーバとの接続が確立しました。しばらくお待ちください...");
		int size = GetDrawStringWidthToHandle(mes,64,font_default);
		DrawSt(320-size/2,300,GetColor(255,150,150),0,font_default,mes);

		//データ受信処理
		for(int i=0;i<MAX_CONNECT;i++){
			if(connect_tcp[i]!=-1){
				NETFIRSTDATA P;
				if(NetWorkRecv(connect_tcp[i], &P, sizeof(NETFIRSTDATA))!=-1){//新規クライアント情報の取得
					NFD[NFD[0].connect_num+1] = P;
					NFD[0].connect_num++;
				}
			}
		}
		if(CheckNetWorkRecvUDP(connect_udp)==TRUE){
			while(NetWorkRecvUDP(connect_udp, NULL, NULL, &bSettingAEnd, sizeof(bool), FALSE)!=sizeof(bool)){}
			wait_count = -1;
			count = 0;	
			change_scene(NETSETTINGB);
		}
	}
	//エラー表示
	if(error>=0){
		play_sound(24);
		if(connect_udp!=-1){
			if(DeleteUDPSocket(connect_udp)==0){
				connect_udp = -1;
			}
			else{
				connect_udp = -1;
				error = 3;
			}
		}	
		if(error==0)	wsprintf(LOG, "ERROR:どうやら満員みたい");
		if(error==1)	wsprintf(LOG, "ERROR:指定したアドレスに接続出来ない");
		if(error==2)	wsprintf(LOG, "ERROR:ポート開放出来ない、或いは既に使われているポート（ＵＤＰ）");
		if(error==3)	wsprintf(LOG, "PROGRAMMING ERROR:ポート閉鎖に失敗（ＵＤＰ）");
		wait_count = -1;
	}

	return;
}

void CLASS_NETWORK::DrawGuest(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	int size = 0;
	for(int i=0;i<MAX_CONNECT+1;i++){
		if(NFD[i].connect_num>0){
			size += GetDrawFormatStringWidth("%s(%d)　", NFD[i].name, NFD[i].rate);
		}
	}
	float x = 320 - size/2;
	for(int i=0;i<MAX_CONNECT+1;i++){
		if(NFD[i].connect_num>0){
			DrawFormatString(x, 455, GetColor(255,255,255),"%s(%d)　", NFD[i].name, NFD[i].rate);
			x += GetDrawFormatStringWidth("%s(%d)　", NFD[i].name, NFD[i].rate);
		}
	}

	return;
}

void CLASS_NETWORK::GetInput(NETGAMEDATA *Input){
//1P~4Pとホストの入力状態を得る。ホストもクライアントも必ず同時に実行しなければならない
	NGD.input[0] = 0;
	int check_num = -1;
	if(SAVE.Key_Type[0]==DX_INPUT_PAD1)		check_num = 0;
	else if(SAVE.Key_Type[0]==DX_INPUT_PAD2)	check_num = 1;
	else if(SAVE.Key_Type[0]==DX_INPUT_PAD3)	check_num = 2;
	else if(SAVE.Key_Type[0]==DX_INPUT_PAD4)	check_num = 3;
	else					check_num = -1;
	if(check_num>=0){
		if(c_pad[check_num][SAVE.Key_Bomb[0]]>0)	NGD.input[0] += 1;
		if(c_pad[check_num][SAVE.Key_Spell[0]]>0)	NGD.input[0] += 2;
		if(c_pad[check_num][SAVE.Key_Pause[0]]>0)	NGD.input[0] += 4;
		if(c_pad[check_num][PAD_UP]>0)		NGD.input[0] += 8;
		if(c_pad[check_num][PAD_DOWN]>0)	NGD.input[0] += 16;
		if(c_pad[check_num][PAD_LEFT]>0)	NGD.input[0] += 32;
		if(c_pad[check_num][PAD_RIGHT]>0)	NGD.input[0] += 64;
	}
	else{
		if(c_key[KEY_INPUT_Z]>0)	NGD.input[0] += 1;
		if(c_key[KEY_INPUT_X]>0)	NGD.input[0] += 2;
		if(c_key[KEY_INPUT_ESCAPE]>0)	NGD.input[0] += 4;
		if(c_key[KEY_INPUT_UP]>0)	NGD.input[0] += 8;
		if(c_key[KEY_INPUT_DOWN]>0)	NGD.input[0] += 16;
		if(c_key[KEY_INPUT_LEFT]>0)	NGD.input[0] += 32;
		if(c_key[KEY_INPUT_RIGHT]>0)	NGD.input[0] += 64;
	}

	if(host_num==-1){//自分がホスト
		for(int i=1;i<PLAYER_NUM+1;i++){
			NGD.input[i] = 0;
		}
		NGD.rand_seed = rand_seed;
		NGD.input[PLAYER_NUM] = NGD.input[0];
		for(int i=0;i<PLAYER_NUM&&i<NFD[0].connect_num;i++){
			IPDATA P;
			int port;
			NETGAMEDATA Q;
			while(NetWorkRecvUDP(connect_udp, &P, &port, &Q, sizeof(NETGAMEDATA), FALSE)!=sizeof(NETGAMEDATA)){}
			for(int j=0;j<MAX_CONNECT;j++){
				if(connect_tcp[j]!=-1 && NFD[j+1].player_num>=0 && P.d1==NFD[j+1].IP[0] && P.d2==NFD[j+1].IP[1] && P.d3==NFD[j+1].IP[2] && P.d4==NFD[j+1].IP[3]){
					NGD.input[NFD[j+1].player_num] = Q.input[0]; 
				}
			}
		}
		for(int i=0;i<MAX_CONNECT;i++){
			if(connect_tcp[i]!=-1){
				IPDATA P;
				P.d1 = NFD[i+1].IP[0];
				P.d2 = NFD[i+1].IP[1];
				P.d3 = NFD[i+1].IP[2];
				P.d4 = NFD[i+1].IP[3];
				while(NetWorkSendUDP(connect_udp, P, hostport, &NGD, sizeof(NETGAMEDATA))!=sizeof(NETGAMEDATA)){}
			}
		}
	}
	else{//自分がクライアント
		IPDATA P;
		P.d1 = NFD[host_num+1].IP[0];
		P.d2 = NFD[host_num+1].IP[1];
		P.d3 = NFD[host_num+1].IP[2];
		P.d4 = NFD[host_num+1].IP[3];
		while(NetWorkSendUDP(connect_udp, P, hostport, &NGD, sizeof(NETGAMEDATA))!=sizeof(NETGAMEDATA)){}
		int port;
		while(NetWorkRecvUDP(connect_udp, &P, &port, &NGD, sizeof(NETGAMEDATA), FALSE)!=sizeof(NETGAMEDATA)){}
	}
	*Input = NGD;
	count++;

	return;
}

void CLASS_NETWORK::GetInputFlag(){
//settingBのフラグチェック。自分がホスト
	for(int i=0;i<7;i++)	SB.settingB[i] = netsettingB_carsol[i];
	while(CheckNetWorkRecvUDP(connect_udp)==TRUE){
		bool dummy;
		NetWorkRecvUDP(connect_udp, NULL, NULL, &dummy, sizeof(bool), FALSE);
		SBnum++;
	}
	if(SBnum==NFD[0].connect_num)	SB.bSettingBEnd[1] = true;
	else				SB.bSettingBEnd[1] = false;
	
	if(SB.bSettingBEnd[1]==true){
		for(int i=0;i<MAX_CONNECT;i++){
			if(connect_tcp[i]!=-1){
				IPDATA P;
				P.d1 = NFD[i+1].IP[0];
				P.d2 = NFD[i+1].IP[1];
				P.d3 = NFD[i+1].IP[2];
				P.d4 = NFD[i+1].IP[3];
				NetWorkSendUDP(connect_udp, P, hostport, &SB, sizeof(SETTINGBDATA));
			}
		}
	}
	
	return;
}

void CLASS_NETWORK::SendInputFlag(){
//settingBのフラグチェック。自分がクライアント
	if(CheckNetWorkRecvUDP(connect_udp)==TRUE){
		NetWorkRecvUDP(connect_udp, NULL, NULL, &SB, sizeof(SETTINGBDATA), FALSE);
	}

	return;
}

int CLASS_NETWORK::GetConnectTcp(int num){
	return connect_tcp[num];
}

int CLASS_NETWORK::GetConnectUdp(){
	return connect_udp;
}