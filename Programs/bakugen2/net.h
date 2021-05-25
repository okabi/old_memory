#ifndef _NET_H_
#define _NET_H_


#include "extern.h"
#include "graph.h"

#define MAX_CONNECT 9
#define HISTORY_NUM 30
#define MAX_MESSAGE 201

struct NETFIRSTDATA{//TCPorUDP:イーチデータ。一旦ホストに渡った後、クライアントに再配布される
	char	name[MAX_NAME];
	int	connect_num,//繋がってる人の数
		player_num,//ホストから見た番号。0~3
		color,
		rate,
		IP[4];
};

struct NETGAMEDATA{//UDP:プレイヤーイーチデータ。最後はホストの入力データ
	unsigned char	input[PLAYER_NUM+1];
	int	rand_seed;
};

struct NETCONFIGDATA{//UDP
	int	stage,
		match_num,
		match_time;
};

struct NETCHATDATA{//TCP:チャット関連で受信される
	char	message[MAX_MESSAGE+MAX_NAME+8];
};

struct HISTORYCHATDATA{//チャット履歴
	char	message[HISTORY_NUM][MAX_MESSAGE+MAX_NAME+8];
	int	color[HISTORY_NUM];
};

struct SETTINGBDATA{//UDP
	int	settingB[7];
	bool	bSettingBEnd[2];//0:個人的設定終了 1:全体的設定終了
	char	name[PLAYER_NUM][MAX_NAME];		
};

class CLASS_NETWORK{
private:
	int	color,
		player_num,//-1:観戦者
		message_handle;
	bool	bSettingAEnd;		
	NETCHATDATA Chat;//新たに付け加えるデータ
	HISTORYCHATDATA HisChat;//履歴。ホストと接続時、ホストから受け取るデータ
public:
	int	connect_tcp[MAX_CONNECT],
		connect_udp;
	int	count;
	NETGAMEDATA NGD;	
	NETFIRSTDATA NFD[MAX_CONNECT+1];
	NETCONFIGDATA NCD;
	SETTINGBDATA SB;
	int	SBnum;
	bool	bChat;//キーボード操作用、チャット状態か否か
	int	bomb[PLAYER_NUM+1],
		spell[PLAYER_NUM+1],
		pause[PLAYER_NUM+1],
		up[PLAYER_NUM+1],
		down[PLAYER_NUM+1],
		left[PLAYER_NUM+1],
		right[PLAYER_NUM+1];
	int	draw_IP[4][3],
		draw_port[5],
		hostIP[4],
		hostport,
		host_num,//-1:自分
		wait_count;//ホスト用、接続待ち時間

	void Load();
	void Reset();
	void ChatFunction();
	void AddMessage(char me[],int co,bool flag=true);
	void HostFunction();
	void ClientFunction();
	void DrawGuest();
	void GetInput(NETGAMEDATA *Input);
	void GetInputFlag();
	void SendInputFlag();
	int GetConnectTcp(int num);
	int GetConnectUdp();
};


extern CLASS_NETWORK NetWork;

#endif