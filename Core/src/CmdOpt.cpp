#include "CmdOpt.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "ASyncCallSupport.h"
#include "Reactor.h"
#include "unistd.h"
#include "ShareData.h"

CCmdOpt* CCmdOpt::GetInstance()
{
	static CCmdOpt m_SingleObj;
	return &m_SingleObj;
}

CCmdOpt::CCmdOpt():m_w_fd(-1)
{
	
}

CCmdOpt::~CCmdOpt()
{
	if(m_w_fd > 0)
		close(m_w_fd);
	
	if(m_n_poll_id > 0)
		close(m_n_poll_id);
}


int CCmdOpt::Init()
{
	int socket_pair[2] = {0};
	if(::socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair) == -1)
	{
		return -1;
	}
	
	m_n_poll_id = socket_pair[1];
	m_w_fd = socket_pair[0];
	EnableInput();
	CReactor::GetInstance()->RegisterPoller(this);
	return 0;
}

int CCmdOpt::InPutNotify()
{
	static int buff;
	int ret = ::recv(m_n_poll_id,&buff,sizeof(buff),0);
	CmdOptPtr *pData;
	do
	{
		{
			CToolLock lock(&m_mutex);
			pData = m_list_aync_callback.Pop();
		}
		if(!pData)
			return 0;
		pData->pObj->OnActionDoneCallBack(pData->cmd, pData->pData);
		delete pData;
	}while(true);
	return 0;
}

void CCmdOpt::SendAsyncCallBack(CAsyncCallSupport* pObj, UINT32 cmd, ASyncCallDataInst& CallData)
{
	CmdOptPtr *pData = new CmdOptPtr;
	pData->pObj = pObj;
	pData->cmd = cmd;
	pData->pData = CallData;

	CToolLock lock(&m_mutex);
	if(m_list_aync_callback.IsEmpty())
	{
		static const char a = 1;
		send(m_w_fd, &a, sizeof(a), 0);
	}
	m_list_aync_callback.Push(pData);
}
