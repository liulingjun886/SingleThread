#pragma once

class PCSDevice : public Device
{
public:
	PCSDevice();
	~PCSDevice();
	
public:
	const PCSData& GetPcsData();

protected:
	PCSData *m_pcs_data; //这里用指针，方便后期做内存映射
};