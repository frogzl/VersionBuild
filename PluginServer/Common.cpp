#include "Common.h"
struct table_entry content_type_table[] = {
	{ "txt", "text/plain" },
	{ "c", "text/plain" },
	{ "h", "text/plain" },
	{ "html", "text/html" },
	{ "htm", "text/htm" },
	{ "css", "text/css" },
	{ "gif", "image/gif" },
	{ "jpg", "image/jpeg" },
	{ "jpeg", "image/jpeg" },
	{ "png", "image/png" },
	{ "pdf", "application/pdf" },
	{ "ps", "application/postsript" },
	{ NULL, NULL },
};

int initialize_socket_environment()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		return 1;

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return 1;
	}
	return 0;
}

void clear_socket_environment()
{
	WSACleanup();
}

void split(string s, const char *pDelim, vector<string>& ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(pDelim, last);
	while (index != string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(pDelim, last);
	}
	if (index - last > 0)
	{
		ret.push_back(s.substr(last, index - last));
	}
}

string getGUID()
{
	char buffer[70] = { 0 };
	GUID guid;

	if (CoCreateGuid(&guid))
	{
		fprintf(stderr, "create guid error\n");
		return "";
	}
	_snprintf_s(buffer, sizeof(buffer),
		"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return buffer;
}

void split(string s, string delim, vector<string>* ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last > 0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}

int compare(string str1, string str2) 
{
	//相等返回0，大于返回1，小于返回-1
	if (str1.size() > str2.size()) 
		return 1; //长度长的整数大于长度小的整数
	else if (str1.size() < str2.size()) 
		return -1;
	else                              
		return str1.compare(str2); //若长度相等，则头到尾按位比较
}

// trim from start 
std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace))));
	return s;
}

// trim from end 
std::string &rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

string app_root_path()
{
	char szPath[255];
	GetModuleFileNameA(NULL, szPath, 255);
	std::string sPath(szPath);
	int nPos = (int)sPath.find("PluginServer.exe", 0);
	int nNameSize = sizeof("PluginServer.exe");
	sPath.erase(nPos, nNameSize - 1);
	return sPath;
}