#pragma once
#include <windows.h>
#include <stdio.h>
#include <locale.h>
using namespace std;
//�ο�ѧϰhttps://www.cnblogs.com/heyonggang/archive/2012/12/25/2831803.html
//https://blog.csdn.net/r5014/article/details/92788388
class Logger {
public:
	/******��־�ȼ�*****/
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
                     ��־��Ϣ�ṹ
     *******************************************/
	struct LogMsg
	{
	    DWORD       m_dwSize;       // �ṹ��С - ������Ϣ���ȶ�̬�仯
	    LogLevel    m_logLevel;     // ��־����
	    UINT        m_uiThreadID;   // �߳�ID
	    SYSTEMTIME  m_stMsgTime;    // ��¼ʱ��
	    TCHAR       m_psMsg[1];     // ��Ϣ����
	};
	//Logger();
private:
	//virtual ~Logger();
	const wchar_t* LOGPATH = L"C:\\tmp\\logon.log";//��Ҫ��д��Ȩ��
public:
	void log(wchar_t* format,...);
	void log(char* format, ...);
	void logw2c(wchar_t* format, ...);
	char* Logger::wchar2char(const wchar_t * pWCBuffer);
};