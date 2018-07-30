#include "StdAfx.h"
#include "operFactory.h"


fileOper* operFactory::createFileOper(string srcCode)
{
	if (srcCode.compare("UTF-8")==0)
	{
		return(new UTF8FileOper());
	}
	else if (srcCode.compare("Unicode")==0)
	{
		return(new UnicodeFileOper());
	}
	else
	{
		return NULL;
	}

}

transOper* operFactory::createTransOper(string srcCode,string destCode)
{
	if (srcCode.compare("Unicode")==0&&destCode.compare("UTF-8")==0)
	{
		return(new UnicodeToUTF8Oper());
	}
	else if (srcCode.compare("UTF-8")==0&&destCode.compare("Unicode")==0)
	{
		return(new UTF8ToUnicodeOper());
	}
	else
	{
		return NULL;
	}
}
