#pragma once
#include <string>
#include <vector>
class Device;

class DeviceManager
{
public:
	static DeviceManager* GetInstance();
public:
	Device* CreateDevice(std::string& model);
	
	const std::vector<Device*>& GetDevices();
	Device* GetDeviceByUuid(std::string& uuid);

	bool RegisterDevice(Device* pDev);
private:
	std::vector<Device*> m_vec_device;
};
