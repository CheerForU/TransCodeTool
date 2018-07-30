#pragma once
#include "afxwin.h"
#include <string>
#include "afxcmn.h"
#include "fileOper.h"
#include "transOper.h"
#include "operFactory.h"
using namespace std;

struct threadParams  
{  
	string srcPath;
	string srcCode;
	string destPath;
	string destCode;
};

struct threadState
{
	DWORD rest;
	DWORD finished;
	int endFlag;
	string errInfo;
};


class threadOper
{
public:
	threadOper::threadOper(string srcPath,string srcCode,string destPath,string destCode);
	~threadOper(void);
	static DWORD WINAPI threadOper::thdFun (LPVOID lpvoid);
	BOOL threadOper::ExitThread(DWORD dwTimeOut);
	int threadOper::trans();
	void threadOper::getState(threadState &state);
	void threadOper::clearState();

	threadParams m_thdParams;
	threadState m_thdState;
	bool m_thdExit;   
	operFactory m_factory;
	transOper *m_transCode ;
	fileOper *m_srcFileOper;
	fileOper *m_destFileOper ;
	DWORD m_bufLineSize;
	HANDLE m_srcFile;
	HANDLE m_destFile;
	HANDLE m_thdHandle;
	CRITICAL_SECTION m_cs;
};

