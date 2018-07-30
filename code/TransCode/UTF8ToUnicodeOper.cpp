#pragma once
#include "StdAfx.h"
#include "UTF8ToUnicodeOper.h"
#include "myLog.h"

UTF8ToUnicodeOper::UTF8ToUnicodeOper(void)
{
}


UTF8ToUnicodeOper::~UTF8ToUnicodeOper(void)
{
}

DWORD UTF8ToUnicodeOper:: transCode(byte *utf8Buf,byte *unicodeBuf,DWORD len)
{
	char *lpUTF8Buf=(char*)utf8Buf;
	WCHAR *lpUnicodeBuf=(WCHAR*)unicodeBuf;
	DWORD nRetLen = 0;
	if(!lpUTF8Buf)  
		return 0;  
	nRetLen = ::MultiByteToWideChar(CP_UTF8,NULL,lpUTF8Buf,len,NULL,0);  
	if(nRetLen>1024*10)
	{
		setLastErrInfo("一行超过10K");
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return -1;
	}
	memset(lpUnicodeBuf,0,nRetLen);
	nRetLen = ::MultiByteToWideChar(CP_UTF8,NULL,lpUTF8Buf,len,lpUnicodeBuf,nRetLen); 
	if(!nRetLen)  
	{
		DWORD e = GetLastError();
		setLastErrInfo("转码失败,错误原因："+e);
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return -1;
	}
	lpUnicodeBuf[nRetLen] = '\0';
	return 2*nRetLen;  
}