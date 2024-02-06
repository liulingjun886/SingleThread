#pragma once

#include "UserTypeDefines.h"
#include "ShareData.h"

class CAsyncCallSupport
{
public:
	CAsyncCallSupport();
	virtual ~CAsyncCallSupport();
public:
	//工作线程处理
	virtual int DoAction(UINT32 cmd, ASyncCallDataInst& pReq, ASyncCallDataInst& pResp) {return 0;}
	//主线程处理
	virtual void DoActionCallBack(UINT32 cmd, ASyncCallDataInst& pResp) {return;}
public:
	int GetThreadIndex();
	void SetThreadIndex(int nIndex);
	void SetDestroylater();
	void SendAsyncCallRequest(UINT32 cmd,  ASyncCallDataInst& callData = ASyncCallDataInst::GetInstance());
	void OnActionDoneCallBack(UINT32 cmd, ASyncCallDataInst& pResp);
private:
	int m_n_thread_index;
};