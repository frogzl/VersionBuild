#pragma once
#include <exception>
#include <string>

class HttpRequestException : public std::exception
{
public:
	HttpRequestException(int nHttpStatus, std::string sCode, std::string sMsg);
	~HttpRequestException();

	int m_nHttpStatus;
	std::string m_sCode;
	std::string m_sMsg;
};

