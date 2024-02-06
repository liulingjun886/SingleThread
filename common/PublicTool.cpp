#include "PublicTool.h"
#include <unistd.h>
#include <string.h>
#include "Log.h"

const std::string& PublicTool::GetProgramLocation()
{
	static std::string strProgramLocation = "";
	if(0 == strProgramLocation.length())
	{
		char buf[256] = {0};
		readlink("/proc/self/exe", buf, sizeof(buf));
		for(int i = strlen(buf); i >= 0; --i)
		{
			if(buf[i] != '/')
				buf[i] = 0;
			else
				break;
		}
		strProgramLocation = buf;
	}
	return strProgramLocation; // 0 is for heap memory
}

bool PublicTool::FileIsExists(const std::string& file_name)
{
    return (0 == access(file_name.c_str(), 0));
}

void* PublicTool::OpenSo(const std::string& soPath)
{
	void* pHander = dlopen(soPth.c_str(),RTLD_LAZY);
	if(!pHander)
	{
		log_error("%s load failer", soPath.c_str());
	}
	return PHand;
}

void* PublicTool::LoadFunAddr(void* pHander,const std::string& funName)
{
	void* pFun = dlsym(pHander,funName.c_str());
	if(!pFun)
	{
		log_error("load %s fun failer", funName.c_str());
	}
	return pFun;
}