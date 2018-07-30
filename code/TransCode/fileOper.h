#pragma once
#include <string>
#include <iostream>
using namespace std;

class fileOper
{
public:
	fileOper(void);
	~fileOper(void);

	void fileOper::setLastErrInfo(string lastErrInfo);
	string fileOper::getLastErrInfo();
	bool fileOper::openFile(string srcPath);
	DWORD fileOper::ReadBufFile(DWORD bufOffSet);
	DWORD fileOper::ReadStringFile(byte* line,DWORD linesize);
	int fileOper::WriteStringFile(byte* bufByte, DWORD bufSize);
	bool fileOper::closeFile();
	virtual bool fileOper::ifEnd(byte* buffer,int i,int len)=0;

	string m_lastErrInfo;
	DWORD m_bufferWrite;
	HANDLE m_handle;
	DWORD m_bufferSize;
	DWORD m_lastPos;
	DWORD m_bytesRead;
	DWORD m_bytesWrite;
	DWORD m_bufferRead;
	DWORD m_len;
	DWORD m_flagLen;
	byte* m_buffer ;
	DWORD m_fileLen;
	DWORD m_myLen;
};
