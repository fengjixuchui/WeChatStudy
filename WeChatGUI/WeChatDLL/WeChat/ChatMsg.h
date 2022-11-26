#pragma once
#include "common.h"
#include <windows.h>
#include <string>

#pragma pack (push,1)
struct ConfigInfoStorage
{
	int field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	char field_1C;
	char field_1D;
	char field_1E;
	char field_1F;
	int field_20;
};

struct MixExtra
{
	int vTable;
	ConfigInfoStorage m_ConfigInfoStorage;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
	int field_38;
	int field_3C;
	mmString sendWxid;
	mmString msgMD5;
	mmString thumbPath;
	mmString imagePath;
	int field_90;
	int field_94;
	int field_98;
	int field_9C;
	int field_A0;
	int field_A4;
	int field_A8;
	int field_AC;
	int field_B0;
	int field_B4;
	int field_B8;
	int field_BC;
	int field_C0;
	int field_C4;
	int field_C8;
	int field_CC;
	int field_D0;
	int field_D4;
	int field_D8;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	int field_EC;
	int field_F0;
	int field_F4;
	int field_F8;
	int field_FC;
	int field_100;
	int field_104;
	int field_108;
	int field_10C;
	int field_110;
	int field_114;
	int field_118;
	int field_11C;
	int field_120;
	int field_124;
	int field_128;
	int field_12C;
	int field_130;
};


//3.7.6.44,��СΪ0x2A0
//3.8.0.33,��СΪ0x2A8
//����жϽṹ���С,MsgMergeMgr::mergeSendMsgs
//��ͬ�汾�в�ͬ�Ĵ�С,����ȡ���ֵ
struct ChatMsg
{
	int vTable;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int msgSeq;
	int field_1C;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	std::uint64_t newMsgId;
	int msgType;
	int isOwner;
	int status_40;
	int createTime;
	mmString fromUserName;
	mmString field_5C;
	mmString msgContent;
	int field_84;
	int field_88;
	char* BytesExtra;
	int BytesExtraLen;
	int field_94;
	int field_98;
	int field_9C;
	int field_A0;
	int field_A4;
	int field_A8;
	int field_AC;
	int field_B0;
	int field_B4;
	int field_B8;
	int field_BC;
	int field_C0;
	int field_C4;
	int field_C8;
	int field_CC;
	int field_D0;
	int field_D4;
	char unknow_D8;
	char field_D9;
	char field_DA;
	char field_DB;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	int field_EC;
	char field_F0;
	char field_F1;
	char field_F2;
	char field_F3;
	int field_F4;
	int field_F8;
	int field_FC;
	int field_100;
	int field_104;
	int field_108;
	int field_10C;
	int field_110;
	int field_114;
	int field_118;
	int field_11C;
	int field_120;
	int field_124;
	int field_128;
	int field_12C;
	int field_130;
	MixExtra mixExtra;
	int field_264;
	char field_268;
	char field_269;
	char field_26A;
	char field_26B;
	int setFlag;
	int field_270;
	int field_274;
	int field_278;
	int field_27C;
	int field_280;
	int field_284;
	int field_288;
	int field_28C;
	int field_290;
	int field_294;
	int field_298;
	int field_29C;
	int field_2A0;
};
#pragma pack(pop)

struct ChatMsgX :public ChatMsg
{
public:
	ChatMsgX();
	~ChatMsgX();
};

struct MyChatMsg
{
	int msgType;				//��Ϣ����
	unsigned long long msgID;	//��Ϣid
	bool IsOwner;				//��Ϣ�Ƿ�Ϊ�Լ�����
	unsigned int CreateTime;	//��Ϣʱ���
	std::wstring FromUserName;	//��Ϣ��Դ,΢��Ⱥwxid
	std::wstring sendWxid;		//�����ߵ�wxid
	std::wstring msgContent;		//��Ϣ����
	std::wstring imagePath;		//ͼƬ��Ϣ·��
};

MyChatMsg CopyChatMsg(ChatMsg* pChatMsg);


