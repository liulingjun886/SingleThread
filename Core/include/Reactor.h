#pragma once
#include "UserTypeDefines.h"

class CPollerObject;
class CTimeNode;
class CAsyncCallSupport;
class ASyncCallDataInst;

class CReactor
{
public:
	static CReactor* GetInstance();
private:
	CReactor():m_b_running(true)
	{
		
	}
public:
	~CReactor()
	{
	
	}
	int Init(unsigned int num);
	bool IsRun();
	void RunLoop();
	void StopLoop();
	void RegisterPoller(CPollerObject* poller);
	void UnRegisterPoller(CPollerObject* poller);
	void RegisterTimer(CTimeNode* const timerNode);
	void UnRegisterTimer(CTimeNode* const timerNode);
	void SendAsyncCallRequest(CAsyncCallSupport* pObj,UINT32 cmd,     ASyncCallDataInst& pReq);
	void SendAsyncCallBack(CAsyncCallSupport* pObj, UINT32 cmd, ASyncCallDataInst& data);
private:
	bool m_b_running;
};

