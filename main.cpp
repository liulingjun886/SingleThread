#include "Reactor.h"
#include "TimeNode.h"
#include "TimeEventHander.h"
#include <iostream>
#include <unistd.h>
#include "TcpV4Server.h"
#include "TcpSocketItem.h"
#include "ASyncCallSupport.h"
#include "ShareData.h"
#include "stdlib.h"
#include "Log.h"

static int i = 0;

class TestTimer : public CTimeEventHander, public CAsyncCallSupport
{
public:
	TestTimer():m_i(++i)
	{
		m_timer.InitTimerNode(this,1);
		m_timer.StartTimer(1000,-1);
		SetThreadIndex((m_i % 3)+1);
	}
	
	int ProcessTimeOutEvent(UINT32 nTimeId)
	{
		SendAsyncCallRequest(1);
		printf("ProcessTimeOutEvent\n");
		return 0;
	}

	virtual int DoAction(UINT32 cmd, ASyncCallDataInst& Req,ASyncCallDataInst& Resp)
	{
		//printf("DoAction = %d, len = %d\n",cmd,Req.length());
		Resp.fill(0, 512);
		return 0;
	}

	void DoActionCallBack(UINT32 cmd, ASyncCallDataInst& Resp)
	{
		log_debug("DoActionCallBack len = %d,m_i = %d", Resp.length(),m_i);
		//_exit(0);
	}
private:
	CTimer m_timer;
	int m_i;
};


int main()
{
	CReactor::GetInstance()->Init(4);
	Log::GetInstance()->SetLogFileName("SmartEms");

	TestTimer t[2000]; 
	
	CReactor::GetInstance()->RunLoop();
	return 0;
}
