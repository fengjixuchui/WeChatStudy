#pragma once
#include <string>
#include <vector>

//ʮ�������ַ���ת�ֽڼ�
std::vector<unsigned char> HexStrToBin(std::string& HexCode);

//�ֽڼ�תʮ�������ַ���
std::string BinToHex(unsigned char* pBuf, unsigned int len);


bool startsWith(const std::wstring& str, const std::wstring prefix);

bool endsWith(const std::wstring& str, const std::wstring suffix);

std::string ReplaceString(std::string& str,std::string to_replaced,const std::string& newchars);

std::string UnicodeToAnsi(const wchar_t* szStr);

std::string UnicodeToUtf8(const wchar_t* szStr);

std::wstring AnsiToUnicode(const char* szStr);

std::wstring Utf8ToUnicode(const char* szStr);

//תutf8
std::string LocalCpToUtf8(const char* str);