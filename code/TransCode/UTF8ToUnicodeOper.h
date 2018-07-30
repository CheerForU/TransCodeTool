#pragma once
#include "transOper.h"
class UTF8ToUnicodeOper : public transOper
{
public:
	UTF8ToUnicodeOper(void);
	~UTF8ToUnicodeOper(void);
	DWORD transCode(byte *lpUTF8Buf,byte *lpGBKBuf,DWORD len);
};

