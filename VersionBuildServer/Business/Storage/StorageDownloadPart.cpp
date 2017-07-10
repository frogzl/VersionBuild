#include "StorageDownloadPart.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"

namespace B
{
	StorageDownloadPart::StorageDownloadPart(Controller::Controller *pController) :StorageBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	StorageDownloadPart::~StorageDownloadPart()
	{
	}

	void StorageDownloadPart::process_task()
	{
		long long llStart = 0, llEnd = 0, llTotle = 0;
		sscanf(m_inputHeaders["Range"].c_str(), "bytes %ld-%ld/%ld", &llStart, &llEnd, &llTotle);

		FILE *fp = fopen(m_inputParameters["path"].c_str(), "rb");
		if (fp)
		{
			string sBase64 = "";
			fseek(fp, llStart, SEEK_SET);
			if (llEnd == 0)
			{
				// 下载全部文件
				fseek(fp, 0, SEEK_END);
				llTotle = ftell(fp);
				fseek(fp, llStart, SEEK_SET);
				if (Buffer_Size <= llTotle)
				{
					fread(m_szBuf, 1, Buffer_Size, fp);
					llEnd = llStart + Buffer_Size;
					sBase64 = Base64_Encode(m_szBuf, Buffer_Size);
				}
				else
				{
					fread(m_szBuf, 1, llTotle, fp);
					llEnd = llStart + llTotle;
					sBase64 = Base64_Encode(m_szBuf, llTotle);
				}
			}
			else
			{
				if (Buffer_Size < llEnd - llStart)
				{
					fread(m_szBuf, 1, Buffer_Size, fp);
					llEnd = llStart + Buffer_Size;
					sBase64 = Base64_Encode(m_szBuf, Buffer_Size);
				}
				else
				{
					fread(m_szBuf, 1, llEnd - llStart, fp);
					sBase64 = Base64_Encode(m_szBuf, llEnd - llStart);
				}
			}
			fclose(fp);
			char szBuf[255];
			sprintf(szBuf, "bytes %ld-%ld/%ld", &llStart, &llEnd, &llTotle);
			set_respond_header("Range", szBuf);
			set_respond_back(HTTP_OK, "0", "successed", "", sBase64);
			return;
		}
		else
		{
			set_respond_back(HTTP_INTERNAL, "1", "open target file failed.", "");
			return;
		}
	}

	void StorageDownloadPart::background_process()
	{

	}
}