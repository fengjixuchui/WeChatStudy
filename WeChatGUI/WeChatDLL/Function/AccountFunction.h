#pragma once
#include <string>
#include <mutex>
#include <vector>

enum WeChatVersion;
class AccountFunction
{
public:
	static AccountFunction& Instance();
	bool InitAccountModule(WeChatVersion ver);
	//�ȴ�΢�ŵ�¼
	std::wstring WaitUtilLogin();
	//�����¼��ά��
	void setLoginQRCode(char* pImgBuf, int imgLen);
	//��ȡ��¼��ά��
	bool getLoginQRCode(std::vector<unsigned char>& outQRCode);

	//��ȡ��ǰwxid
	std::wstring getCurrentUserWxid();
public:
	std::wstring currentUserWxid;
	std::vector<unsigned char> currentQRCode;
	std::mutex qrcodeMutex;
private:
	WeChatVersion WeChatVer;
};