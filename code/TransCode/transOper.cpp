#include "StdAfx.h"
#include "transOper.h"

transOper::transOper()
{

}

transOper::~transOper(void)
{
}

void transOper::setLastErrInfo(string lastErrInfo) {
	m_lastErrInfo = lastErrInfo;
}

string transOper::getLastErrInfo() {
	return m_lastErrInfo;
}
