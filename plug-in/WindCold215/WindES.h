#pragma once
#include "DataPool.h" 

class WindEms : public Device, public CTimeEventHander
{
public:
	WindEms();
	~WindEms();

private:
	PCSData m_pcsData;
	
};