#pragma once
#include <pthread.h>
#include "PollerObject.h"
#include "ToolLock.h"
#include "List.h"
#include "ShareData.h"

class CAsyncCallSupport;

struct CmdOptPtr : public CListNode<CmdOptPtr>
{
	UINT32 cmd;
	CAsyncCallSupport* pObj;
	ASyncCallDataInst pData; 
};

class CCmdOpt : public CPollerObject
{
public:
	static CCmdOpt* GetInstance();
private:
	CCmdOpt();
	~CCmdOpt();
public:
	int Init();
	int InPutNotify();
	int OutPutNotify(){return 0;}
	int HunpUpNotiry() {return 0;}
	void SendAsyncCallBack(CAsyncCallSupport* pObj, UINT32 cmd, ASyncCallDataInst& pData);
private:
	int m_w_fd;
	CListFIFO<CmdOptPtr> m_list_aync_callback;
	CMutexLock m_mutex;
};
