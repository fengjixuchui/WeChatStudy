#include "Public.h"
#include <fstream>
#include <sstream>

const char ���[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string ReadFileToString(const char* filepath)
{
	std::string ret;
	FILE* hFile = NULL;
	if (fopen_s(&hFile, filepath, "rb")) {
		return ret;
	}
	fseek(hFile, 0, SEEK_END);
	unsigned int fileSize = ftell(hFile);
	if (!fileSize) {
		fclose(hFile);
		return ret;
	}
	fseek(hFile, 0, SEEK_SET);
	ret.resize(fileSize);
	fread(&ret[0],fileSize,1,hFile);
	fclose(hFile);
	return ret;
}

unsigned int ReadUint(void* lp)
{
	return *(unsigned int*)lp;
}


std::string base64_encode(std::vector<unsigned char>& ��������)
{
	char BASE64_PAD = '=';
	std::string ������;
	������.resize((��������.size() + 2) / 3 * 4);

	int s = 0;
	unsigned int Len = 0;
	unsigned char lastC = 0;
	for (unsigned int n = 0; n < ��������.size(); ++n)
	{
		unsigned char c = ��������[n];

		switch (s)
		{
		case 0:
			s = 1;
			������[Len++] = ���[(c >> 2) & 0x3F];
			break;
		case 1:
			s = 2;
			������[Len++] = ���[((lastC & 0x3) << 4) | ((c >> 4) & 0xF)];
			break;
		case 2:
			s = 0;
			������[Len++] = ���[((lastC & 0xF) << 2) | ((c >> 6) & 0x3)];
			������[Len++] = ���[c & 0x3F];
			break;
		}
		lastC = c;
	}

	switch (s)
	{
	case 1:
		������[Len++] = ���[(lastC & 0x3) << 4];
		������[Len++] = BASE64_PAD;
		������[Len++] = BASE64_PAD;
		break;
	case 2:
		������[Len++] = ���[(lastC & 0xF) << 2];
		������[Len++] = BASE64_PAD;
		break;
	}

	return ������;
}