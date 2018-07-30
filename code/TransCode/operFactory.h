#pragma once
#include <string>

#include "UTF8FileOper.h"
#include "UnicodeFileOper.h"
#include "UnicodeToUTF8Oper.h"
#include "UTF8ToUnicodeOper.h"

using namespace std;
class operFactory
{
public:

	fileOper* operFactory::createFileOper(string srcCode);
	transOper *operFactory::createTransOper(string srcCode,string destCode);
	
};
