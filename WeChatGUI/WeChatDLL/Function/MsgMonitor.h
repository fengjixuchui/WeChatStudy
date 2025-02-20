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
	//私人消息
	WX_PrivateMsg = 0x1,
	//群消息
	WX_GroupMsg,
	//公众号
	WX_PublicMsg,
};

struct MsgUploadInfo
{
	nlohmann::json msg;
	//消息类型
	//int msgType;
	//消息发送时间
	//unsigned int postTime;
	//消息id
	//unsigned long long msgID;
	//消息来源
	//std::wstring wxid;
	//消息来源名称
	//std::wstring name;
	//发送者的名称
	//std::wstring senderName;
	//发送者的WXID
	//std::wstring senderWxid;
	//消息内容
	//std::wstring msgContent;
	//机器人的wxid
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

	//获取群成员事件
	bool getAddMemberEventMsg(std::wstring& eventName, MsgUploadInfo& outInfo);
	//添加群成员事件
	void pushAddMemberEventMsg(std::wstring& eventName,MsgUploadInfo& msg);
private:
	WeChatVersion WeChatVer;
	MsgBuffer msgBuffer;

	//事件消息表
	std::map<std::wstring, MsgUploadInfo> addMemberEventMap;
	std::mutex addEventMutex;
};