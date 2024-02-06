#include "WorkThread.h"
#include "Reactor.h"
#include "ASyncCallSupport.h"
#include "ShareData.h"

void *Run(void *pArgs)
{
	CWorkThread* pThread = (CWorkThread*)pArgs;
	pThread->run();
	return NULL;
}

CWorkThread::CWorkThread():m_b_sleep(false)
{
}

CWorkThread::~CWorkThread()
{
	
}

int CWorkThread::start()
{
	if(pthread_create(&m_pid,NULL,Run,this))
		return -1;
	return 0;
}

void CWorkThread::stop()
{
	m_cond.WakeUp();
	pthread_join(m_pid,NULL);
}


void CWorkThread::run()
{
	AsyncCallListNode *p = nullptr;
	int ret = -1;
	while(CReactor::GetInstance()->IsRun())
	{
		m_mutex.Lock();
		p = m_list_req.Pop();
		if(!p)
		{
			m_b_sleep = true;
			m_cond.Wait(m_mutex);
			m_b_sleep = false;
			m_mutex.UnLock();
			continue;
		}
		m_mutex.UnLock();
		
		ASyncCallDataInst RespData;
		ret = p->pObj->DoAction(p->cmd,p->pData,RespData);
		CReactor::GetInstance()->SendAsyncCallBack(p->pObj,p->cmd,RespData);
		delete p;
	}
}

int CWorkThread::AddAsyncCallReq(CAsyncCallSupport* pObj,UINT32 cmd, ASyncCallDataInst& pData)
{
	AsyncCallListNode *p = new AsyncCallListNode;
	p->pObj = pObj;
	p->cmd = cmd;
	p->pData = pData;

	CToolLock lock(&m_mutex);
	m_list_req.Push(p);
	if(m_b_sleep)
		m_cond.WakeUp();

	return 0;
}
