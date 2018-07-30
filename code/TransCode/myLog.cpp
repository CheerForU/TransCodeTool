#include "stdafx.h"
#include "myLog.h"

Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("logmain"));    

void InitLog()
{     
	PropertyConfigurator::doConfigure("..\\config\\log4cplus.cfg");
}
