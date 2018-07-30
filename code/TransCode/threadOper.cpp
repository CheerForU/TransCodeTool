#include "stdafx.h"
#include <afxwin.h>  
#include "threadOper.h"
#include "myLog.h"

threadOper::threadOper(string srcPath,string srcCode,string destPath,string destCode)
{
	m_thdParams.srcPath = srcPath;
	m_thdParams.srcCode = srcCode;
	m_thdParams.destPath = destPath;
	m_thdParams.destCode = destCode;
	InitializeCriticalSection(&m_cs);  
	clearState();
}

threadOper::~threadOper(void)
{
}


DWORD WINAPI threadOper::thdFun(LPVOID lpvoid)
{
	DWORD res =0;
	threadOper *thd_Oper = (threadOper*)lpvoid;
	res = thd_Oper->trans();
	return res;
}


int threadOper::trans()
{
	m_srcFileOper = m_factory.createFileOper(m_thdParams.srcCode);
	m_destFileOper = m_factory.createFileOper(m_thdParams.srcCode);
	m_transCode = m_factory.createTransOper(m_thdParams.srcCode,m_thdParams.destCode);
	if (!m_srcFileOper||!m_destFileOper||!m_transCode)
	{
		m_srcFileOper=NULL;
		m_destFileOper=NULL;
		m_transCode=NULL;
		delete[] m_srcFileOper;
		delete[] m_destFileOper;
		delete[] m_destFileOper;
		return -1;
	}

	//设置一行缓存为10K
	m_bufLineSize=1024*10;
	byte* m_srcLine = new byte[m_bufLineSize];
	byte* m_destLine = new byte[m_bufLineSize];
	DWORD m_srcLineSize = 0;
	DWORD m_destLineSize = 0;

	if( !(m_srcFileOper->openFile(m_thdParams.srcPath)))
	{
		EnterCriticalSection(&m_cs);
		m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
		LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
		LeaveCriticalSection(&m_cs);

		if(!(m_srcFileOper->closeFile()))
		{
			EnterCriticalSection(&m_cs);
			m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
			LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
			LeaveCriticalSection(&m_cs);
			DeleteCriticalSection(&m_cs);
			return -1;
		}
		EnterCriticalSection(&m_cs);
		m_thdState.endFlag = -1;
		LeaveCriticalSection(&m_cs);
		return -1;
	}
	EnterCriticalSection(&m_cs);
	m_thdState.rest = m_srcFileOper->m_myLen;
	LeaveCriticalSection(&m_cs);

	if( !(m_destFileOper->openFile(m_thdParams.destPath)) )
	{
		EnterCriticalSection(&m_cs);
		m_thdState.errInfo = m_destFileOper->getLastErrInfo();
		LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
		LeaveCriticalSection(&m_cs);

		if(!(m_destFileOper->closeFile()))
		{
			EnterCriticalSection(&m_cs);
			m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
			LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
			LeaveCriticalSection(&m_cs);
			DeleteCriticalSection(&m_cs);
			return -1;
		}
		EnterCriticalSection(&m_cs);
		m_thdState.endFlag = -1;
		LeaveCriticalSection(&m_cs);
		DeleteCriticalSection(&m_cs);
		return -1;
	}

	do
	{
		m_srcLineSize = m_srcFileOper->ReadStringFile(m_srcLine,m_bufLineSize);
		if(m_srcLineSize == -1)
		{	
			EnterCriticalSection(&m_cs);
			m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
			m_thdState.endFlag = -1;
			LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
			LeaveCriticalSection(&m_cs);
			goto fail;
		}
		m_destLineSize = m_transCode->transCode(m_srcLine,m_destLine,m_srcLineSize);
		if(m_destLineSize == -1)
		{	
			EnterCriticalSection(&m_cs);
			m_thdState.errInfo = m_transCode->getLastErrInfo();
			m_thdState.endFlag = -1;
			LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
			LeaveCriticalSection(&m_cs);
			goto fail;
			
		}
		m_destFileOper->WriteStringFile(m_destLine, m_destLineSize);
		if(m_srcLineSize == -1)
		{	
			EnterCriticalSection(&m_cs);
			m_thdState.errInfo = m_destFileOper->getLastErrInfo();
			m_thdState.endFlag = -1;
			LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
			LeaveCriticalSection(&m_cs);
			goto fail;
		}
		EnterCriticalSection(&m_cs);
		m_thdState.finished = m_srcFileOper->m_bufferWrite;
		LeaveCriticalSection(&m_cs);
		
	}while(m_srcFileOper->m_bufferWrite != m_srcFileOper->m_myLen);
	EnterCriticalSection(&m_cs);
	m_thdState.endFlag = 1;
	LeaveCriticalSection(&m_cs);
	delete[] m_srcLine;
	delete[] m_destLine;

	if(!(m_srcFileOper->closeFile()))
	{
		EnterCriticalSection(&m_cs);
		m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
		LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
		LeaveCriticalSection(&m_cs);
		DeleteCriticalSection(&m_cs);
		return -1;
	}
	if(!(m_destFileOper->closeFile()))
	{
		EnterCriticalSection(&m_cs);
		m_thdState.errInfo = m_destFileOper->getLastErrInfo();
		LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
		LeaveCriticalSection(&m_cs);
		DeleteCriticalSection(&m_cs);
		return -1;
	}
	m_srcFileOper=NULL;
	m_destFileOper=NULL;
	m_transCode=NULL;
	delete[] m_srcFileOper;
	delete[] m_destFileOper;
	delete[] m_destFileOper;
	return 1;

fail:	
	if(!(m_srcFileOper->closeFile()))
	{
		EnterCriticalSection(&m_cs);
		m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
		LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
		LeaveCriticalSection(&m_cs);
		DeleteCriticalSection(&m_cs);
		return -1;
	}
	if(!(m_srcFileOper->closeFile()))
	{
		EnterCriticalSection(&m_cs);
		m_thdState.errInfo = m_srcFileOper->getLastErrInfo();
		LOG4CPLUS_ERROR(logger,m_thdState.errInfo);
		LeaveCriticalSection(&m_cs);
		DeleteCriticalSection(&m_cs);
		return -1;
	}
	DeleteCriticalSection(&m_cs);
	delete[] m_srcLine;
	delete[] m_destLine;
	m_srcFileOper=NULL;
	m_destFileOper=NULL;
	m_transCode=NULL;
	delete[] m_srcFileOper;
	delete[] m_destFileOper;
	delete[] m_destFileOper;
	return -1;

}



void threadOper::getState(threadState &state)
{
	EnterCriticalSection(&m_cs);
	state.rest = m_thdState.rest;
	state.finished = m_thdState.finished;
	state.endFlag = m_thdState.endFlag;
	LeaveCriticalSection(&m_cs);
}

void threadOper::clearState()
{
	EnterCriticalSection(&m_cs);
	m_thdState.endFlag=0;
	m_thdState.finished=0;
	m_thdState.rest=0;
	m_thdState.errInfo="";
	LeaveCriticalSection(&m_cs);
	
}

BOOL threadOper::ExitThread(DWORD dwTimeOut)
{
	m_thdExit = TRUE;
	DWORD dwRet = WaitForSingleObject(m_thdHandle,dwTimeOut);
	if(dwRet == WAIT_TIMEOUT)
	{
		int iRet = TerminateThread(m_thdHandle,-1);
		return FALSE;
	}
	return TRUE;
}


