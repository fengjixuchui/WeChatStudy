#pragma once
#include <string>
#include <vector>

//ԭ���ṹ��,���ڶ�
struct mmString
{
public:
	mmString();
	void free();
	void assignUTF8(const char* src);
	//��΢���Լ���alloc
	void assign(const wchar_t* src, int len);
public:
	wchar_t* pUnicode;
	int Mysize;
	int Myres;
	char* pUTF8;
	int uLen;
};

std::wstring copyMMString(mmString* mmStr);

//��װ�ṹ��,���ԭ���ṹ�����������������Ϳ������캯����
struct mmStringX :public mmString
{
public:
	mmStringX();
	//�������캯��
	mmStringX(const mmStringX& obj);
	~mmStringX();
};
