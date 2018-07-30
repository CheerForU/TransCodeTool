#pragma once  
#pragma comment(lib,"log4cplusS.lib")

#include <tchar.h>
#include <log4cplus/consoleappender.h>    
#include <log4cplus/fileappender.h>    
#include <log4cplus/layout.h>    
#include <log4cplus/configurator.h> 
#include <log4cplus/loggingmacros.h> 
#include <iostream>
#include <memory>
#include <time.h>
#include <errno.h>

using namespace std;
using namespace log4cplus; 
using namespace log4cplus::helpers; 

void InitLog(); 

extern Logger logger;


