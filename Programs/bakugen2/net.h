#ifndef _NET_H_
#define _NET_H_


#include "extern.h"
#include "graph.h"

#define MAX_CONNECT 9
#define HISTORY_NUM 30
#define MAX_MESSAGE 201

struct NETFIRSTDATA{//TCPorUDP:�C�[�`�f�[�^�B��U�z�X�g�ɓn������A�N���C�A���g�ɍĔz�z�����
	char	name[MAX_NAME];
	int	connect_num,//�q�����Ă�l�̐�
		player_num,//�z�X�g���猩���ԍ��B0~3
		color,
		rate,
		IP[4];
};

struct NETGAMEDATA{//UDP:�v���C���[�C�[�`�f�[�^�B�Ō�̓z�X�g�̓��̓f�[�^
	unsigned char	input[PLAYER_NUM+1];
	int	rand_seed;
};

struct NETCONFIGDATA{//UDP
	int	stage,
		match_num,
		match_time;
};

struct NETCHATDATA{//TCP:�`���b�g�֘A�Ŏ�M�����
	char	message[MAX_MESSAGE+MAX_NAME+8];
};

struct HISTORYCHATDATA{//�`���b�g����
	char	message[HISTORY_NUM][MAX_MESSAGE+MAX_NAME+8];
	int	color[HISTORY_NUM];
};

struct SETTINGBDATA{//UDP
	int	settingB[7];
	bool	bSettingBEnd[2];//0:�l�I�ݒ�I�� 1:�S�̓I�ݒ�I��
	char	name[PLAYER_NUM][MAX_NAME];		
};

class CLASS_NETWORK{
private:
	int	color,
		player_num,//-1:�ϐ��
		message_handle;
	bool	bSettingAEnd;		
	NETCHATDATA Chat;//�V���ɕt��������f�[�^
	HISTORYCHATDATA HisChat;//�����B�z�X�g�Ɛڑ����A�z�X�g����󂯎��f�[�^
public:
	int	connect_tcp[MAX_CONNECT],
		connect_udp;
	int	count;
	NETGAMEDATA NGD;	
	NETFIRSTDATA NFD[MAX_CONNECT+1];
	NETCONFIGDATA NCD;
	SETTINGBDATA SB;
	int	SBnum;
	bool	bChat;//�L�[�{�[�h����p�A�`���b�g��Ԃ��ۂ�
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
		host_num,//-1:����
		wait_count;//�z�X�g�p�A�ڑ��҂�����

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