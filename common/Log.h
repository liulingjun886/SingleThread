#pragma once

#include "ASyncCallSupport.h"
#include "TimeNode.h"
#include "TimeEventHander.h"
#include <stdarg.h>
#include <unistd.h>

enum LOG_LEVEL
{
	LOG_NONE = 0,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

class Log : public CAsyncCallSupport,public CTimeEventHander
{
public:
	Log();
	~Log();
	static Log *GetInstance();
public:
	void SetLogFileName(const char * const szFileName);
	void WriteLog(LOG_LEVEL level, const char *pFileName, const char* pFunName,unsigned long cLine,const char *fmt, ...);
	int DoAction(UINT32 cmd, ASyncCallDataInst& pReq, ASyncCallDataInst& pResp);
	int ProcessTimeOutEvent(UINT32 nTimeId);
private:
	void CheckNewFile();
	
private:
	char m_szFileName[256];
	INT32 m_nMon;
	INT32 m_nDay;
	UINT32 m_nIndex;
	FILE* m_pFile;
	CTimeNode m_timerCheck;
};

#define filename(x) (strrchr(x,'/') != NULL ? strrchr(x,'/')+1:x)
#define log_debug(fmt,...) Log::GetInstance()->WriteLog(LOG_DEBUG,filename(__FILE__),__func__,__LINE__,fmt,##__VA_ARGS__);
#define log_info(fmt,...) Log::GetInstance()->WriteLog(LOG_INFO,filename(__FILE__),__func__,__LINE__,fmt,##__VA_ARGS__);
#define log_warn(fmt,...) Log::GetInstance()->WriteLog(LOG_WARNING,filename(__FILE__),__func__,__LINE__,fmt,##__VA_ARGS__);
#define log_error(fmt,...) Log::GetInstance()->WriteLog(LOG_ERROR,filename(__FILE__),__func__,__LINE__,fmt,##__VA_ARGS__);