#pragma once
#include "fileOper.h"
class UnicodeFileOper : public fileOper
{
public:
	UnicodeFileOper(void);
	~UnicodeFileOper(void);
	bool  UnicodeFileOper::openFile(string srcPath);
	DWORD UnicodeFileOper::ReadBufFile(DWORD bufOffSet);
	DWORD UnicodeFileOper::ReadStringFile(byte* lineByte);
	int   UnicodeFileOper::WriteStringFile(byte* bufByte, DWORD bufSize);
	bool UnicodeFileOper::ifEnd(byte* buffer,int i,int len);

};
