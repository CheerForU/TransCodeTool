#pragma once
#include "StdAfx.h"
#include "UnicodeToUTF8Oper.h"
#include "myLog.h"

UnicodeToUTF8Oper::UnicodeToUTF8Oper(void)
{
}

UnicodeToUTF8Oper::~UnicodeToUTF8Oper(void)
{
}

DWORD UnicodeToUTF8Oper:: transCode(byte *unicodeBuf,byte *utf8Buf,DWORD len)
{
	char *lpUTF8Buf=(char*)utf8Buf;
	wchar_t *lpUnicodeBuf=(wchar_t*)unicodeBuf;
	DWORD nRetLen = 0;
	DWORD nUTF8StrLen = 0;
	if(!lpUnicodeBuf)  
		return 0;  
	len=len/sizeof(wchar_t);
	nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeBuf,len,NULL,0,NULL,NULL); 
	if(nRetLen>1024*10)
	{
		setLastErrInfo("一行超过10K");
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return -1;
	}
	memset(lpUTF8Buf,0,nRetLen);
	nRetLen = ::WideCharToMultiByte(CP_UTF8,0,lpUnicodeBuf,len,lpUTF8Buf,nRetLen,NULL,NULL);
	if(!nRetLen)
	{
		DWORD e = GetLastError();
		setLastErrInfo("转码失败,错误原因："+e);
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return -1;
	}
	return nRetLen;  
}
