#include "StdAfx.h"
#include "UTF8FileOper.h"
#include "myLog.h"

UTF8FileOper::UTF8FileOper()
{
	m_flagLen=1;
}

UTF8FileOper:: ~UTF8FileOper()
{
}

bool UTF8FileOper::ifEnd(byte* buffer,int i,int len){
	if ((i+1<len)&&(buffer[i] == 0x0D)&&(buffer[i+1] == 0x0A)){
		return true;
	}
	return false;
}
