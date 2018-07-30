#pragma once
#include "StdAfx.h"
#include <iostream>
#include "function.h"
#include "myLog.h"
using namespace std;


function::function(string srcPath,string srcCode,string destPath,string destCode)
{
	m_srcPath = srcPath;
	m_srcCode = srcCode;
	m_destPath = destPath;
	m_destCode = destCode;
	m_thdOper = NULL;
}

function::~function(void)
{
}

void function::setLastErrInfo(string lastErrInfo) {
	m_lastErrInfo = lastErrInfo;
}

string function::getLastErrInfo() {
	return m_lastErrInfo;
}


bool function::transAll()
{
	terminateThd();
	m_thdOper = new threadOper(m_srcPath,m_srcCode,m_destPath,m_destCode);
	m_thdOper->m_thdHandle = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)m_thdOper->thdFun,m_thdOper,0,NULL);
	m_thdOper->getState(m_thdState);
	if (m_thdOper->m_thdHandle==NULL)
	{
		DWORD e = GetLastError();
		setLastErrInfo("线程创建失败，错误原因："+e);
		LOG4CPLUS_ERROR(logger,m_lastErrInfo);
		return false;
	}
	setLastErrInfo(m_thdState.errInfo);
	return true;
}


int function::getRate()
{
	if (m_thdOper!=NULL)
	{
		m_thdOper->getState(m_thdState);

		if (m_thdState.endFlag == 1)
		{
			return 100;
		}
		if (m_thdOper->m_thdState.endFlag== -1)
		{
			setLastErrInfo(m_thdState.errInfo);
			LOG4CPLUS_ERROR(logger,m_lastErrInfo);
			return 0;
		}
		else 
		{
			return (int)((float)(m_thdState.finished) * 100 / (float)(m_thdState.rest));
		}
	}
	return 0;
}


void function::terminateThd()
{
	if (m_thdOper!=NULL)
	{
		if (m_thdOper->m_thdExit!=true)
		{
			m_thdOper->ExitThread(5000);
			delete m_thdOper;
			m_thdOper = NULL;
		}
	}
}


