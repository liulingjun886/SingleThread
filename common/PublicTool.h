#pragma once
#include <string>

class PublicTool
{
public:
	static const std::string& GetProgramLocation();//获取可执行文件存放路径
	static bool FileIsExists(const std::string& file_name);//判断文件是否存在
	static void* OpenSo(const std::string& soPath); //加载SO库
	static void* LoadFunAddr(void* pHander,const std::string& funName);	//加载动态库方法
};