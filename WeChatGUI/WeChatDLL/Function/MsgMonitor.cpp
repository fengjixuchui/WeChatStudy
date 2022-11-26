#include "MsgMonitor.h"
#include <json.hpp>
#include <fstream>
#include <vector>
#include <httplib.h>
#include <AnyCall/AnyCall.h>
#include "../InlineHook/InlineHook.h"
#include "../WeChatDLL.h"
#include "../TinyXml/tinyxml2.h"
#include "../public/Strings.h"
#include "../public/Public.h"
#include "../public/WinApi.h"
#include "../WeChat/ChatMsg.h"
#include "../WeChatDLL.h"
#include "../΢��ƫ��.h"
#include "ContactFunction.h"
#include "AccountFunction.h"

InlineHook gHook_AddChatMsg;
InlineHook gHook_ImageDownload;

void Handle_ImageChatMsg(MyChatMsg& chatMsg)
{
	MsgUploadInfo tmpMsg;
	tmpMsg.msgType = chatMsg.msgType;
	tmpMsg.robotID = AccountFunction::Instance().getCurrentUserWxid();
	tmpMsg.postTime = chatMsg.CreateTime;
	tmpMsg.msgID = chatMsg.msgID;
	tmpMsg.wxid = chatMsg.FromUserName;
	if (!tmpMsg.wxid.empty()) {
		tmpMsg.name = ContactModule::Instance().GetContactInfoDynamic(tmpMsg.wxid).nickName;
	}
	tmpMsg.senderWxid = chatMsg.sendWxid;
	tmpMsg.senderName = ContactModule::Instance().GetContactInfoDynamic(chatMsg.sendWxid).nickName;
	tmpMsg.msgContent = chatMsg.imagePath;
	MsgMonitor::Instance().AddMsg(tmpMsg);
}

//����ҵ��ú���,NetSceneGetMsgImgCDN::onDownloadSuccessed

void __stdcall MyOnDownloadImageSuccessed_3_7_6_44(HookContext* hookContext)
{
	char* pNetSceneGetMsgImgCDN = (char*)hookContext->ECX;
	ChatMsg* pChatMsg = (ChatMsg*)(pNetSceneGetMsgImgCDN + 0x5AC);
	MyChatMsg tmpMsg = CopyChatMsg(pChatMsg);
	mmString* pImageDownloadPath = (mmString*)(pNetSceneGetMsgImgCDN + 0x954);
	tmpMsg.imagePath = copyMMString(pImageDownloadPath);
	if (tmpMsg.IsOwner) {
		tmpMsg.sendWxid = AccountFunction::Instance().getCurrentUserWxid();
	}
	Handle_ImageChatMsg(tmpMsg);
}

void __stdcall MyOnDownloadImageSuccessed_3_8_0_33(HookContext* hookContext)
{
	char* pNetSceneGetMsgImgCDN = (char*)hookContext->ECX;
	ChatMsg* pChatMsg = (ChatMsg*)(pNetSceneGetMsgImgCDN + 0x5AC);
	MyChatMsg tmpMsg = CopyChatMsg(pChatMsg);
	mmString* pImageDownloadPath = (mmString*)(pNetSceneGetMsgImgCDN + 0x964);
	tmpMsg.imagePath = copyMMString(pImageDownloadPath).c_str();
	if (tmpMsg.IsOwner) {
		tmpMsg.sendWxid = AccountFunction::Instance().getCurrentUserWxid();
	}
	Handle_ImageChatMsg(tmpMsg);
}


void HandleChatMsg(MyChatMsg& chatMsg)
{
	MsgUploadInfo tmpMsg;
	tmpMsg.msgType = chatMsg.msgType;
	tmpMsg.robotID = AccountFunction::Instance().getCurrentUserWxid();
	tmpMsg.postTime = chatMsg.CreateTime;
	tmpMsg.msgID = chatMsg.msgID;
	tmpMsg.wxid = chatMsg.FromUserName;
	if (!tmpMsg.wxid.empty()) {
		tmpMsg.name = ContactModule::Instance().GetContactInfoDynamic(tmpMsg.wxid).nickName;
	}
	tmpMsg.senderWxid = chatMsg.sendWxid;
	tmpMsg.senderName = ContactModule::Instance().GetContactInfoDynamic(chatMsg.sendWxid).nickName;
	tmpMsg.msgContent = chatMsg.msgContent;
	MsgMonitor::Instance().AddMsg(tmpMsg);
}

void Handle_AppChatMsg(MyChatMsg& chatMsg)
{
	MsgUploadInfo tmpMsg;
	tmpMsg.msgType = chatMsg.msgType;
	tmpMsg.robotID = AccountFunction::Instance().getCurrentUserWxid();
	tmpMsg.postTime = chatMsg.CreateTime;
	tmpMsg.msgID = chatMsg.msgID;
	tmpMsg.wxid = chatMsg.FromUserName;
	if (!tmpMsg.wxid.empty()) {
		tmpMsg.name = ContactModule::Instance().GetContactInfoDynamic(tmpMsg.wxid).nickName;
	}
	tmpMsg.senderWxid = chatMsg.sendWxid;
	tmpMsg.senderName = ContactModule::Instance().GetContactInfoDynamic(chatMsg.sendWxid).nickName;
	tmpMsg.msgContent = chatMsg.msgContent;
	MsgMonitor::Instance().AddMsg(tmpMsg);
}


void __stdcall MyAddChatMsg(HookContext* hookContext)
{
	ChatMsg* pChatMsg = (ChatMsg*)hookContext->ECX;
	if (pChatMsg->msgType == 51) {
		return;
	}

	MyChatMsg tmpMsg = CopyChatMsg(pChatMsg);
	if (tmpMsg.IsOwner) {
		tmpMsg.sendWxid = AccountFunction::Instance().getCurrentUserWxid();
	}
	
	switch (tmpMsg.msgType)
	{
	case 1:			//��ͨ��Ϣ	
	case 42:		//��Ƭ��Ϣ
	case 43:		//��Ƶ��Ϣ
	case 47:		//������Ϣ
	case 49:		//Ӧ����Ϣ
	case 10000:		//ϵͳ֪ͨ + �������������Ⱥ
		HandleChatMsg(tmpMsg);
		break;
	case 10002:		//�Լ����������Ⱥ
		break;
	case 3:
		//�������ﴦ��ͼƬ��Ϣ
		break;
	default:
		break;
	}
}


MsgMonitor& MsgMonitor::Instance()
{
	static MsgMonitor gMsgMonitor;
	return gMsgMonitor;
}

bool MsgMonitor::InitMsgMonitor(WeChatVersion v)
{
	WeChatVer = v;

	DWORD hWeChatWinDLL = WeChatDLL::Instance().getWinMoudule();
	
	switch (WeChatVer) {
	case WeChat_3_7_6_44:
		gHook_AddChatMsg.AddHook((LPVOID)(hWeChatWinDLL + 0x5F7423), MyAddChatMsg);
		gHook_ImageDownload.AddHook((LPVOID)(hWeChatWinDLL + 0x6C0D50), MyOnDownloadImageSuccessed_3_7_6_44);
		//����ͼƬ�Զ�����
		д�ڴ�_HEX(-1, hWeChatWinDLL + 0x5262B0, "B001C3");
		return true;
	case WeChat_3_8_0_33:
		gHook_AddChatMsg.AddHook((LPVOID)(hWeChatWinDLL + 0xB94296), MyAddChatMsg);
		gHook_ImageDownload.AddHook((LPVOID)(hWeChatWinDLL + 0xC63740), MyOnDownloadImageSuccessed_3_8_0_33);
		//����ͼƬ�Զ�����
		д�ڴ�_HEX(-1, hWeChatWinDLL + 0xB94344, "E9CE00");
		return true;
	default:
		break;
	}
	return false;
}

std::vector<MsgUploadInfo> MsgMonitor::SyncMsg()
{
	std::vector<MsgUploadInfo> retMsgList;
	msgBuffer.popMsg(retMsgList);
	return retMsgList;
}

void MsgMonitor::AddMsg(MsgUploadInfo& msg)
{
	msgBuffer.pushMsg(msg);
}

MsgBuffer::MsgBuffer()
{
	
}

inline void MsgBuffer::pushMsg(MsgUploadInfo& msg)
{
	mute.lock();
	if (buffer.size() >= 1000) {
		buffer.pop_front();
	}
	buffer.push_back(msg);
	mute.unlock();
}

void MsgBuffer::popMsg(std::vector<MsgUploadInfo>& outMsgList)
{
	mute.lock();
	unsigned int msgCount = 0;
	for (std::list<MsgUploadInfo>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
		outMsgList.push_back(*it);
		if (++msgCount >= 10) {
			break;
		}
	}
	for (unsigned int n = 0; n < msgCount; ++n) {
		buffer.pop_front();
	}
	mute.unlock();
	return;
}
