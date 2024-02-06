#include "PollerObject.h"
#include "Reactor.h"

CPollerObject::CPollerObject():m_n_poll_id(-1),m_n_new_event(ERROR)
{
	CReactor::GetInstance()->RegisterPoller(this);
}

CPollerObject::~CPollerObject()
{
	CReactor::GetInstance()->UnRegisterPoller(this);
}

int CPollerObject::GetEvent()
{
	return m_n_new_event;
}

int CPollerObject::getPoller() 
{
	return m_n_poll_id;
}

void CPollerObject::EnableInput()
{
	m_n_new_event |= READ;
}
void CPollerObject::EnableOutput()
{
	m_n_new_event |= WRITE;
}
void CPollerObject::DisableInput()
{
	m_n_new_event &= ~READ;
}
void CPollerObject::DisableOutPut()
{
	m_n_new_event &= ~WRITE;
}


