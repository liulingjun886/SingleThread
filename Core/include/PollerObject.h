#pragma once

#include "UserTypeDefines.h"

enum {
	READ = 2,
	WRITE = 3,
	ERROR = 1
};

class CPollerObject
{
public:
	CPollerObject();
	~CPollerObject();
public:
	virtual int Init() = 0;
	virtual int InPutNotify() = 0;
	virtual int OutPutNotify() = 0;
	virtual int HunpUpNotiry() = 0;
public:
	void ApplyEvents();
	int GetEvent();
	int getPoller();
protected:
	void EnableInput();
	void EnableOutput();
	void DisableInput();
	void DisableOutPut();
protected:
	int m_n_poll_id;
private:
	UINT32 m_n_new_event;
};
