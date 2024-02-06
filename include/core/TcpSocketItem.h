#pragma once

#include "PollerObject.h"
#include "TimeNode.h"
#include "Reactor.h"

class CRecvCache
{
public:
    CRecvCache();
    ~CRecvCache();

    char* data();
    UINT32 data_len();
    void append(const char* data, UINT32 data_len);
    void skip(UINT32 length);
	void clear();
	void fix_block_size(UINT32 data_len);
private:
	//CLockMemPool& _mp;
    //内存基址
    char* _mem;
    //内存大小
    UINT32 _block_size;
    //实际使用内存起始偏移量
    UINT32 _data_head;
    //实际使用内存长度
    UINT32 _data_len;
};

class CTcpSocketItem : public CPollerObject //适用于V4 V6 的服务端套接字
{
public:
	CTcpSocketItem():m_b_reconnect(false),m_b_connected(false)
	{
		
	}
	~CTcpSocketItem()
	{
		Close();
	}
public:
	virtual int Init()
	{
		m_b_reconnect = true;
		return 0;
	}
	
	virtual int InPutNotify();
	virtual int OutPutNotify();
	virtual int HunpUpNotiry()
	{
		Close();
		return onDisConnected(); 
	}
	
	virtual int ConnectToHost()
	{
		EnableOutput();
		return 0;
	}

	virtual void onConnected()
	{
		m_b_connected = true;
		DisableOutPut();
		EnableInput();
		//std::cout << "onConnected" << std::endl;
	}

	virtual int onDisConnected()
	{
		delete this;
		return -1;
	}

	virtual int onRecvCompelete(char* pData, UINT32 nLen)
	{
		//std::cout << nLen << std::endl;
		//CReactor::GetIntance()->SendAsyncCallBack(NULL, 1, (char*)pData, nLen);
		return nLen;
	}
public:
	int SendData(const char* pData, UINT32 nLen);
	int  RecvNetData(char* pBuff,UINT32 nBuffSize);
	void Close();	
	void attach(int fd);
	const std::string& GetRemoteIp() const {return m_str_ip;}
	UINT16 GetRemotePort() const {return m_n_port;}
	void SetRemoteIpStr(const std::string& ip) {m_str_ip = ip;}
	void SetRemotePort(UINT16 port) {m_n_port = port;}
	void SetRemoteAddr(const std::string& ip, UINT16 port);
protected:
	bool m_b_reconnect;
	bool m_b_connected;
	std::string m_str_ip;
	UINT16 m_n_port;
	CRecvCache m_recv_buff;
};