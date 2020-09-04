#pragma once
#include <windows.h>
#include <stdio.h>
#include <locale.h>
using namespace std;
//参考学习https://www.cnblogs.com/heyonggang/archive/2012/12/25/2831803.html
//https://blog.csdn.net/r5014/article/details/92788388
class Logger {
public:
	/******日志等级*****/
	enum LogLevel
	{
	    LL_NONE = 0XFF,
	    LL_DEBUG = 1,
	    LL_TRACE = 2,
	    LL_INFO = 3,
	    LL_WARN = 4,
	    LL_ERROR = 5,
	    LL_FATAL = 6
	};
	/******************************************
                     日志信息结构
     *******************************************/
	struct LogMsg
	{
	    DWORD       m_dwSize;       // 结构大小 - 跟据消息长度动态变化
	    LogLevel    m_logLevel;     // 日志级别
	    UINT        m_uiThreadID;   // 线程ID
	    SYSTEMTIME  m_stMsgTime;    // 记录时间
	    TCHAR       m_psMsg[1];     // 消息内容
	};
	//Logger();
private:
	//virtual ~Logger();
	const wchar_t* LOGPATH = L"C:\\tmp\\logon.log";//需要有写入权限
public:
	void log(wchar_t* format,...);
	void log(char* format, ...);
	void logw2c(wchar_t* format, ...);
	char* Logger::wchar2char(const wchar_t * pWCBuffer);
};