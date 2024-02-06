#pragma once

#include "List.h"
#include <pthread.h>
#include "UserTypeDefines.h"
#include "ToolLock.h"
#include "ShareData.h"

class CAsyncCallSupport;

struct AsyncCallListNode : public CListNode<AsyncCallListNode>
{
	UINT32 cmd;
	CAsyncCallSupport* pObj;
	ASyncCallDataInst pData;
};

class CWorkThread
{
public:
	CWorkThread();
	~CWorkThread();
public:
	int start();
	void stop();
	void run();
	int AddAsyncCallReq(CAsyncCallSupport* pObj,UINT32 cmd, ASyncCallDataInst& pData);	
private:
	bool m_b_sleep;
	pthread_t m_pid;
	CListFIFO<AsyncCallListNode> m_list_req;
	CMutexLock m_mutex;
	CWaitCond m_cond;
};