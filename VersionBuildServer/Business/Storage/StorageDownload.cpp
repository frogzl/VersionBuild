#include "StorageDownload.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Database/Storage.h"
#include "../../Database/Resource_Host.h"
#include "../../Tools/HttpClient.h"
namespace B
{
	StorageDownload::StorageDownload(Controller::Controller *pController) :StorageBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	StorageDownload::~StorageDownload()
	{
	}

	void StorageDownload::process_task()
	{
		long long llStart = 0, llEnd = 0, llTotle = 0;
		sscanf(m_inputHeaders["Range"].c_str(), "bytes %ld-%ld/%ld", &llStart, &llEnd, &llTotle);

		// ��ȡ�洢��Ϣ
		DB::Storage dbStorage;
		DB::Conditions conditions;
		conditions.insert(pair<string, string>("guid", m_inputParameters["storageid"].c_str()));
		DB::StorageData *pDBStorageData = dbStorage.query()->where(conditions)->first();
		if (!pDBStorageData)
		{
			set_respond_back(HTTP_INTERNAL, "1", "get storage data failed.", "");
			return;
		}

		// �����洢λ��
		Json::Reader reader;
		Json::Value jsonHosts;
		if (!reader.parse(pDBStorageData->storagehostlist, jsonHosts))
		{
			set_respond_back(HTTP_INTERNAL, "1", "storage host list parse failed.", "");
			return;
		}

		// ����Ҫ�����ļ�����ʼ�ͽ���λ��
		memset(m_szBuf, 0, Buffer_Size);
		if (llEnd == 0)
		{
			// �״�����
			llTotle = pDBStorageData->size;
			if (Buffer_Size <= llTotle)
				llEnd = llStart + Buffer_Size;
			else
				llEnd = llStart + llTotle;
		}
		else
		{
			if (Buffer_Size < llEnd - llStart)
				llEnd = llStart + Buffer_Size;
		}

		// ����llStart��llEnd����
		long long llTmpStart = llStart, llTmpEnd = llEnd;
		long long llPartStart = 0, llPartEnd = 0;
		long long llFileDataSize = 0; // �˴λ�ȡ���ļ����ݴ�ѧ
		int nCount = jsonHosts.size();
		for (int nIndex = 0; nIndex < nCount; nIndex++)
		{
			Json::Value jsonHost = jsonHosts[nIndex];
			conditions.clear();
			conditions.insert(pair<string, string>("guid", m_inputParameters["guid"].c_str()));
			DB::Resource_Host dbHost;
			DB::Resource_HostData *pHostData = dbHost.query()->where(conditions)->first();
			if (!pHostData)
			{
				set_respond_back(HTTP_INTERNAL, "1", "get host data failed.", "");
				return;
			}

			string sRange = jsonHost["range"].asString();
			sscanf(sRange.c_str(), "%ld-%ld", &llPartStart, &llPartEnd);
			if (llPartStart >= llTmpStart && llTmpStart <= llPartEnd)
			{
				int nSize = 0;
				HttpClient httpClient;
				if (llTmpEnd <= llPartEnd)
				{
					// ����llTmpStart��llEnd��ȡ�ļ�����
					if (!httpClient.download_file_part(pHostData->address, pHostData->port, m_szBuf + llFileDataSize, jsonHost["path"].asString(), llTmpStart, llTmpEnd, nSize))
					{
						set_respond_back(HTTP_INTERNAL, "1", "get_file_part failed.", "");
						return;
					}
					llFileDataSize += nSize;
					break;
				}
				else
				{
					// ����llTmpStart��llPartEnd��ȡ�ļ����ݣ�Ȼ������llTmpStart				
					if (!httpClient.download_file_part(pHostData->address, pHostData->port, m_szBuf + llFileDataSize, jsonHost["path"].asString(), llTmpStart, llPartEnd, nSize))
					{
						set_respond_back(HTTP_INTERNAL, "1", "get_file_part failed.", "");
						return;
					}
					llFileDataSize += nSize;
					llTmpStart += nSize;
				}
			}
		}

		string sBase64 = Base64_Encode(m_szBuf, llFileDataSize);
		char szBuf[255];
		sprintf(szBuf, "bytes %ld-%ld/%ld", &llStart, &llEnd, &llTotle);
		set_respond_header("Range", szBuf);
		set_respond_back(HTTP_OK, "0", "successed", "", sBase64);
	}

	void StorageDownload::background_process()
	{

	}
}