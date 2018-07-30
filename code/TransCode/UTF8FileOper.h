#pragma once
#include "fileOper.h"
class UTF8FileOper :  public fileOper
{
public:
	UTF8FileOper(void);
	~UTF8FileOper(void);
	bool  UTF8FileOper::openFile(string srcPath);
	DWORD UTF8FileOper::ReadBufFile(DWORD bufOffSet);
	DWORD UTF8FileOper::ReadStringFile(byte* lineByte);
	int   UTF8FileOper::WriteStringFile(byte* bufByte, DWORD bufSize);
	bool UTF8FileOper::ifEnd(byte* buffer,int i,int len);
};
