//����
#include "΢�Ŷ࿪.h"
#include "../΢��ƫ��.h"
#include "../public/WinApi.h"
#include "../WeChatDLL.h"

bool Patch_΢�Ŷ࿪(WeChatVersion ver)
{
	//����cmp eax, 0B7h����һ��
	switch (ver) {
	case WeChat_3_7_6_44:
		return д�ڴ�_HEX(-1, WeChatDLL::Instance().getWinMoudule() + 0xE7FCBE, "EB");
	case WeChat_3_8_0_33:
		return д�ڴ�_HEX(-1, WeChatDLL::Instance().getWinMoudule() + 0x1477F84, "EB");
		return true;
	}
	return false;
}
