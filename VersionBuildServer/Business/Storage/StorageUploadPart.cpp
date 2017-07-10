#include "StorageUploadPart.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"

namespace B
{
	StorageUploadPart::StorageUploadPart(Controller::Controller *pController) :StorageBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	StorageUploadPart::~StorageUploadPart()
	{
	}

	void StorageUploadPart::process_task()
	{
		long long llStart = 0, llEnd = 0, llTotle = 0;
		sscanf(input_headers()["Range"].c_str(), "bytes %ld-%ld/%ld", &llStart, &llEnd, &llTotle);

		// 读取body数据
		string sFileName = input_data()["filename"].asString();
		u2g(sFileName.c_str(), sFileName.length(), m_szBuf, Buffer_Size);
		sFileName = m_szBuf;
		string sStoragePartID = input_data()["storagepartid"].asString();
		if (sStoragePartID.compare("") == 0)
			sStoragePartID = getGUID();

		// 判断是否是分次上传
		FILE *fp = NULL;
		if (llTotle == llEnd && llStart == 0)
		{
			// 整体提交			
			string sPath = input_data()["path"].asString()  + sStoragePartID;
			{
				for (int nIndex = 0; nIndex < sPath.length(); nIndex++)
					if (sPath[nIndex] == '\\')
						sPath[nIndex] = '/';
				size_t stReal = Base64_Decode(sPath.c_str(), "ab", input_data()["data"].asString().c_str(), input_data()["data"].asString().length());
				if (stReal != 0)
				{
					set_respond_back(HTTP_OK, "0", "successed", "", sStoragePartID);
				}
				else
					set_respond_back(HTTP_INTERNAL, "1", "create file failed!", "");
			}
		}
		else
		{
			// 分段提交
			string sPath = input_data()["path"].asString() + sStoragePartID;
			size_t stReal = Base64_Decode(m_szBuf, input_data()["data"].asString().c_str(), input_data()["data"].asString().length());
			for (int nIndex = 0; nIndex < sPath.length(); nIndex++)
				if (sPath[nIndex] == '\\')
					sPath[nIndex] = '/';
			fp = fopen(sPath.c_str(), "ab");
			if (fp)
			{
				fseek(fp, llStart, SEEK_SET);
				fwrite(m_szBuf, 1, stReal, fp);
				fclose(fp);
				set_respond_back(HTTP_OK, "0", "successed", "", sStoragePartID);
			}
			else
				set_respond_back(HTTP_INTERNAL, "1", "create file failed!", "");
		}
	}

	void StorageUploadPart::background_process()
	{

	}
}