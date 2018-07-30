#pragma once
#include "threadOper.h"

using namespace std;


class function
{
public:
	function(string srcPath,string srcCode,string destPath,string destCode);
	~function(void);


public:
	bool function::transAll();
	int function::getRate();
	void function::terminateThd();
	void function::setLastErrInfo(string lastErrInfo);
	string function::getLastErrInfo();

	threadState m_thdState;
	string m_lastErrInfo;
	string m_srcPath;
	string m_srcCode;
	string m_destPath;
	string m_destCode;
	threadOper *m_thdOper;
};
