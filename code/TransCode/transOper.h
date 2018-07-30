#pragma once
#include "afxwin.h"
#include <string>
#include "afxcmn.h"
using namespace std;
class transOper
{
	
public:
	transOper::transOper(void);
	~transOper(void);
	virtual DWORD transCode(byte* srcBuf, byte* desBuf,DWORD len)=0;
	void transOper::setLastErrInfo(string lastErrInfo);
	string transOper::getLastErrInfo();
	string m_lastErrInfo;
};



