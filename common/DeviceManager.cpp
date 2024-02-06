#include "DeviceManager.h"
#include "PublicTool.h"

typedef Device*(*CreateDevice)();

DeviceManager* DeviceManager::GetInstance()
{
	static DeviceManager mp_instance;
	return &mp_instance;
}

Device* DeviceManager::CreateDevice(std::string& model)
{
	Device* pDev = nullptr;
	void* pHander = PublicTool::OpenSo(model)
	if(!pHander)
	{
		return pDev;
	}

	CreateDevice pCreate = (CreateDevice)PublicTool::LoadFunAddr(pHander, "CreateDevice");
	if(!pCreate)
	{
		return pDev;
	}

	pDev = pCreate();
	return pDev;
}

const std::vector<Device*>& DeviceManager::GetDevices()
{
	return m_vec_device;
}

Device* DeviceManager::GetDeviceByUuid(std::string& uuid)
{
	for(std::vector<Device*>::itertor it = m_vec_device.begin(); it != m_vec_device.end(); ++it)
	{
		if((*it)->getDevSn == uuid)
			return (*it)
	}
	return nullptr;
}

bool DeviceManager::RegisterDevice(Device* pDev)
{
	for(std::vector<Device*>::itertor it = m_vec_device.begin(); it != m_vec_device.end(); ++it)
	{
		if((*it) == pDev)
			return false;
	}
	return true;
}


