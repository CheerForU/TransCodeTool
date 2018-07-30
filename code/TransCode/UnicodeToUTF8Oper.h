#pragma once
#include "transOper.h"
class UnicodeToUTF8Oper : public transOper
{
public:
	UnicodeToUTF8Oper(void);
	~UnicodeToUTF8Oper(void);
	DWORD transCode(byte *lpGBKBuf,byte *lpUTF8Buf,DWORD len);

};

