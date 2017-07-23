#include "HttpRequestException.h"

HttpRequestException::HttpRequestException(int nHttpStatus, std::string sCode, std::string sMsg):
	m_nHttpStatus(nHttpStatus), m_sCode(sCode), m_sMsg(sMsg)
{
}


HttpRequestException::~HttpRequestException()
{
}
