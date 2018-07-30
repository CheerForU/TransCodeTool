#include "StdAfx.h"
#include "UnicodeFileOper.h"
#include "myLog.h"

UnicodeFileOper::UnicodeFileOper()
{
	m_flagLen=3;
}

UnicodeFileOper:: ~UnicodeFileOper()
{

}


bool UnicodeFileOper::ifEnd(byte* buffer,int i,int len){
	if ((i+3<len)&&(buffer[i] == 0x0D)&&(buffer[i+1] == 0x00)&&(buffer[i+2] == 0x0A)&&(buffer[i+3] == 0x00)){
		return true;
	}
	return false;
}