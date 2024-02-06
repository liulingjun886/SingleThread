#pragma once

#include <vector>
#include <string>

enum RUNSTATE
{
	OFFLINE = 0, //离线
	ONLINE		//在线
};

class Device
{
public:
	Device();
	virtual ~Device();
public:
	int Init(std::string& sn);
	const std::string& getDevSn()
	{
		return m_str_device_sn;
	}
	void SetParent(Device* pDev);
	Device GetParent();
	void AddChild(Device* pDev);
	void SetRunState(int state);

public:
	virtual bool GetFirstLevelAlarm();			//是否有一级告警
	virtual bool GetSecondLevelAlarm();			//是否有二级告警
	virtual bool GetThirdLevelAlarm();			//是否有三级告警
	virtual bool GetFourthLevelAlarm();			//是否有四级告警
protected:
	virtual int Initialize();
protected:
	std::string m_str_device_sn;				//设备SN
	std::string m_str_model;					//设备型号
	RUNSTATE  m_n_run_state;					//设备在线状态
	Device* m_p_parent;							//父设备
	std::vector<Device*> m_vec_children; 		//子设备
};