#pragma once
#include <string>

enum WeChatVersion;
class AccountFunction
{
public:
	static AccountFunction& Instance();
	bool InitAccountModule(WeChatVersion ver);
	//�ȴ�΢�ŵ�¼
	std::string WaitUtilLogin();
public:
	static std::string currentUserWxid;
private:
	WeChatVersion WeChatVer;
};