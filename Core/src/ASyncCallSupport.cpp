#include "ASyncCallSupport.h"
#include "Reactor.h"


CAsyncCallSupport::CAsyncCallSupport():m_n_thread_index(0)
{
	
}

CAsyncCallSupport::~CAsyncCallSupport()
{
	
}


int CAsyncCallSupport::GetThreadIndex()
{
	return m_n_thread_index;
}

void CAsyncCallSupport::SendAsyncCallRequest(UINT32 cmd, ASyncCallDataInst& callData)
{
	CReactor::GetInstance()->SendAsyncCallRequest(this, cmd, callData);
}

void CAsyncCallSupport::SetDestroylater()
{
}

void CAsyncCallSupport::SetThreadIndex(int nIndex)
{
	m_n_thread_index = nIndex;
}


void CAsyncCallSupport::OnActionDoneCallBack(UINT32 cmd, ASyncCallDataInst& pResp)
{
	return DoActionCallBack(cmd,pResp);
}


