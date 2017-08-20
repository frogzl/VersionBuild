#include "Common.h"
#include <openssl/md5.h>
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

void split(string& s, const char *pDelim, vector<string>& ret)
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

//代码转换:从一种编码转为另一种编码
int code_convert(char *from_charset, char *to_charset, const char *inbuf, int inlen, char *outbuf, int outlen)
{
	iconv_t cd;
	char **pin = (char **)&inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, (size_t*)&inlen, pout, (size_t*)&outlen) == -1) 
		return -1;
	iconv_close(cd);
	return 0;
}
//UNICODE码转为GB2312码
int u2g(const char *inbuf, int inlen, char *outbuf, int outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}
//GB2312码转为UNICODE码
int g2u(const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}


//===================================
//    Base64 解码
//===================================
BYTE Decode_GetByte(char c)
{
	if (c == '+')
		return 62;
	else if (c == '/')
		return 63;
	else if (c <= '9')
		return (BYTE)(c - '0' + 52);
	else if (c == '=')
		return 64;
	else if (c <= 'Z')
		return (BYTE)(c - 'A');
	else if (c <= 'z')
		return (BYTE)(c - 'a' + 26);
	return 64;
}

//解码
size_t Base64_Decode(char *pDest, const char *pSrc, size_t srclen)
{
	BYTE input[4];
	size_t i, index = 0;
	for (i = 0; i < srclen; i += 4)
	{
		//byte[0]
		input[0] = Decode_GetByte(pSrc[i]);
		input[1] = Decode_GetByte(pSrc[i + 1]);
		pDest[index++] = (input[0] << 2) + (input[1] >> 4);

		//byte[1]
		if (pSrc[i + 2] != '=')
		{
			input[2] = Decode_GetByte(pSrc[i + 2]);
			pDest[index++] = ((input[1] & 0x0f) << 4) + (input[2] >> 2);
		}

		//byte[2]
		if (pSrc[i + 3] != '=')
		{
			input[3] = Decode_GetByte(pSrc[i + 3]);
			pDest[index++] = ((input[2] & 0x03) << 6) + (input[3]);
		}
	}

	//null-terminator
	pDest[index] = 0;
	return index;
}

size_t Base64_Decode(const char *szFilePath, const char *szOpenMode, const char *pSrc, size_t srclen)
{
	BYTE input[4];
	size_t i, index, count = 0;
	char szDest[4] = { 0 };
	for (i = 0; i < srclen; i += 4)
	{
		index = 0;
		memset(szDest, 0, 4);
		//byte[0]
		input[0] = Decode_GetByte(pSrc[i]);
		input[1] = Decode_GetByte(pSrc[i + 1]);
		szDest[index++] = (input[0] << 2) + (input[1] >> 4);

		//byte[1]
		if (pSrc[i + 2] != '=')
		{
			input[2] = Decode_GetByte(pSrc[i + 2]);
			szDest[index++] = ((input[1] & 0x0f) << 4) + (input[2] >> 2);
		}

		//byte[2]
		if (pSrc[i + 3] != '=')
		{
			input[3] = Decode_GetByte(pSrc[i + 3]);
			szDest[index++] = ((input[2] & 0x03) << 6) + (input[3]);
		}
		FILE *fp = fopen(szFilePath, szOpenMode);
		if (fp)
		{
			fwrite(szDest, index, 1, fp);
			fclose(fp);
		}
		count += index;
	}
	return  i < srclen ? 0 : count;
}

//===================================
//    Base64 编码
//===================================
char Encode_GetChar(BYTE num)
{
	return
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789"
		"+/="[num];
}

//编码
string Base64_Encode(const char *pSrc, size_t srclen)
{
	string sRet = "";
	BYTE input[3], output[4], outputTmp[8];
	size_t i, index_src = 0, index_dest = 0;
	size_t tmp = 0;
	for (i = 0; i < srclen; i += 3)
	{
		tmp = 0;
		//char [0]
		input[0] = pSrc[index_src++];
		output[0] = (BYTE)(input[0] >> 2);
		outputTmp[tmp++] = Encode_GetChar(output[0]);

		//char [1]
		if (index_src < srclen)
		{
			input[1] = pSrc[index_src++];
			output[1] = (BYTE)(((input[0] & 0x03) << 4) + (input[1] >> 4));
			outputTmp[tmp++] = Encode_GetChar(output[1]);
		}
		else
		{
			output[1] = (BYTE)((input[0] & 0x03) << 4);
			outputTmp[tmp++] = Encode_GetChar(output[1]);
			outputTmp[tmp++] = '=';
			outputTmp[tmp++] = '=';
			break;
		}

		//char [2]
		if (index_src < srclen)
		{
			input[2] = pSrc[index_src++];
			output[2] = (BYTE)(((input[1] & 0x0f) << 2) + (input[2] >> 6));
			outputTmp[tmp++] = Encode_GetChar(output[2]);
		}
		else
		{
			output[2] = (BYTE)((input[1] & 0x0f) << 2);
			outputTmp[tmp++] = Encode_GetChar(output[2]);
			outputTmp[tmp++] = '=';
			break;
		}

		//char [3]
		output[3] = (BYTE)(input[2] & 0x3f);
		outputTmp[tmp++] = Encode_GetChar(output[3]);
		outputTmp[tmp] = 0;
		sRet += (char*)outputTmp;
	}
	return sRet;
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
	_snprintf(buffer, sizeof(buffer),
		"{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return buffer;
}

void split(string& s, string delim, vector<string>* ret)
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

string file_md5(string sFilePath)
{ 
	MD5_CTX ctx;
	int len = 0;
	unsigned char buffer[1024] = { 0 };
	unsigned char digest[16] = { 0 };

	FILE *pFile = fopen(sFilePath.c_str(), "rb"); // 我没有判断空指针  

	MD5_Init(&ctx);

	while ((len = fread(buffer, 1, 1024, pFile)) > 0)
	{
		MD5_Update(&ctx, buffer, len);
	}

	MD5_Final(digest, &ctx);

	fclose(pFile);


	int i = 0;
	char buf[33] = { 0 };
	char tmp[3] = { 0 };
	string sFileMd5 = "";
	for (i = 0; i < 16; i++)
	{
		sprintf(tmp, "%02X", digest[i]); // sprintf并不安全  
		sFileMd5 += tmp;
	}

	return sFileMd5;
}