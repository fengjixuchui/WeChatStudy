#pragma once
#include <vector>
#include <string>
#include <list>
#include <mutex>
#include <nlohmann/json.hpp>
#include "../public/RWMutex.h"

enum msgCategory
{
	WX_Undefine = 0x0,
	//˽����Ϣ
	WX_PrivateMsg = 0x1,
	//Ⱥ��Ϣ
	WX_GroupMsg,
	//���ں�
	WX_PublicMsg,
};

struct MsgUploadInfo
{
	nlohmann::json msg;
	//��Ϣ����
	//int msgType;
	//��Ϣ����ʱ��
	//unsigned int postTime;
	//��Ϣid
	//unsigned long long msgID;
	//��Ϣ��Դ
	//std::wstring wxid;
	//��Ϣ��Դ����
	//std::wstring name;
	//�����ߵ�����
	//std::wstring senderName;
	//�����ߵ�WXID
	//std::wstring senderWxid;
	//��Ϣ����
	//std::wstring msgContent;
	//�����˵�wxid
	//std::wstring robotID;
};

class MsgBuffer
{
public:
	MsgBuffer();
	void pushMsg(MsgUploadInfo& msg);
	void popMsg(std::vector<MsgUploadInfo>& outMsgList);
private:
	std::list<MsgUploadInfo> buffer;
	std::mutex mute;
};

enum WeChatVersion;
class MsgMonitor
{
public:
	static MsgMonitor& Instance();
	bool InitMsgMonitor(WeChatVersion ver);
	std::vector<MsgUploadInfo> SyncMsg();
	void AddMsg(MsgUploadInfo& msg);

	//��ȡȺ��Ա�¼�
	bool getAddMemberEventMsg(std::wstring& eventName, MsgUploadInfo& outInfo);
	//���Ⱥ��Ա�¼�
	void pushAddMemberEventMsg(std::wstring& eventName,MsgUploadInfo& msg);
private:
	WeChatVersion WeChatVer;
	MsgBuffer msgBuffer;

	//�¼���Ϣ��
	std::map<std::wstring, MsgUploadInfo> addMemberEventMap;
	std::mutex addEventMutex;
};