#pragma once

#include "MinHeap.h"
#include "UserTypeDefines.h"

class CTimeEventHander;

class CTimeNode : public CHeapNode<CTimeNode>
{
	friend class CTimerUnit;
public:
	CTimeNode();
	~CTimeNode();

public:
	void InitTimerNode(CTimeEventHander* pHand,UINT32 nTimeId);
	void StartTimer(UINT32 nExpired,UINT64 nCnt=1);
	void StartTimerSec(UINT32 nExpired,UINT64 nCnt=1);
	void StopTimer();
	void TimerNotify();
	UINT64 GetExpireTime() const 
	{
		return m_n_expired;
	}
public:
	bool operator<(const CTimeNode& node)
	{
		return m_n_expired < node.m_n_expired;
	}
private:
	UINT32 m_n_time_id;					//定时器编号
	UINT32 m_n_trig_interval;			//触发间隔
	UINT64 m_n_expired;					//下次触发时间 当前时间+触发间隔
	UINT64 m_n_repeat;					//触发次数
	CTimeEventHander* m_timer_node;		//定时器处理对象
};

typedef CTimeNode CTimer;