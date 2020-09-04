#include "utils.h"

void Logger::log(wchar_t* format, ...) {
	va_list vl;
	va_start(vl, format);
	wchar_t szLogInfo[256];
	//wsprintf(szLogInfo, format, vl);
	wvsprintf(szLogInfo,format, vl);
	lstrcat(szLogInfo, L"\n");
	va_end(vl);
	FILE* fp = NULL;
	_wfopen_s(&fp, LOGPATH, L"at+");
	if (fp != NULL) {
		setlocale(LC_ALL, "zh_CH.utf8");//需要设置locale
		fputws(szLogInfo, fp);
		fclose(fp);
	}
}

void Logger::logw2c(wchar_t* format, ...) {
	char *pMBBuffer = this->wchar2char(format);
	strcat_s(pMBBuffer, sizeof(pMBBuffer), "\n");
	va_list vl;
	va_start(vl,pMBBuffer);
	FILE* fp = NULL;
	fopen_s(&fp, this->wchar2char(LOGPATH), "at+");
	if (fp != NULL) {
		vfprintf(fp, pMBBuffer,vl);
		fclose(fp);
	}
	va_end(vl);
}

//宽字符转多字节
char* Logger::wchar2char(const wchar_t * pWCBuffer) {
	size_t size = sizeof(wchar_t) * (wcslen(pWCBuffer) + 1);
	char *pMBBuffer = (char *)malloc(size);
	size_t i;
	wcstombs_s(&i, pMBBuffer, size, pWCBuffer, size);
	return pMBBuffer;
}


void Logger::log(char* format, ...) {
	va_list vl;
	va_start(vl, format);
	FILE* fp = NULL;
	strcat_s(format,sizeof(format),"\n");
	fopen_s(&fp, this->wchar2char(LOGPATH), "at+");
	if (fp != NULL) {
		vfprintf(fp, format, vl);
		fclose(fp);
	}
	va_end(vl);
}

