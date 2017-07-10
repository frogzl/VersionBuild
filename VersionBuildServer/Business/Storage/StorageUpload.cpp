#include "StorageUpload.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"
#include "../../Tools/HttpClient.h"
#include "../../Database/Resource_Host.h"
#include "../../Database/Storage.h"
namespace B
{
	StorageUpload::StorageUpload(Controller::Controller *pController) :StorageBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	StorageUpload::~StorageUpload()
	{
	}

	void StorageUpload::process_task()
	{
		long long llStart = 0, llEnd = 0, llTotle = 0;
		sscanf(input_headers()["Range"].c_str(), "bytes %ld-%ld/%ld", &llStart, &llEnd, &llTotle);

		string sFileName = input_data()["filename"].asString();
		u2g(sFileName.c_str(), sFileName.length(), m_szBuf, Buffer_Size);
		sFileName = m_szBuf;
		string sStorageID = input_data()["storageid"].asString();

		if (sStorageID.compare("") == 0)
			sStorageID = getGUID();
		string sTmpPath = SystemConfig::instance()->getStorageTmpPath() + "\\" + sStorageID;
		int stReal = Base64_Decode(sTmpPath.c_str(), "ab", input_data()["data"].asString().c_str(), input_data()["data"].asString().length());

		// 判断是否是分次上传
		if (llEnd == llTotle)
		{
			// 分包上传
			DB::Resource_Host dbHost;
			vector<DB::Resource_HostData> *vecHostDatas = dbHost.query()->where("`type`=0x00000001")->all();
			if (vecHostDatas)
			{
				int nHostCount = vecHostDatas->size();
				for (int nHostIndex = 0; nHostIndex < nHostCount; nHostIndex++)
				{
					DB::Resource_HostData &dbHostData = (*vecHostDatas)[nHostIndex];
					
					Json::Value jsonStorageHostList;
					Json::Value jsonStorage;
					Json::Reader reader;
					if (reader.parse(dbHostData.storage, jsonStorage))
					{
						bool bIsFound = false;
						string sPath = "";
						Json::Value jsonPartitionName = jsonStorage["partitionName"];
						Json::Value jsonAvailableSpace = jsonStorage["availableSpace"];
						for (int nAvaSpaceIndex = 0; nAvaSpaceIndex < jsonAvailableSpace.size(); nAvaSpaceIndex++)
						{
							string sSpace = jsonAvailableSpace[nAvaSpaceIndex].asString();
							long lSpace = atol(sSpace.c_str());
							if (lSpace > llTotle)
							{
								string sPath = jsonPartitionName[nAvaSpaceIndex].asString() + ":/storage/";
								HttpClient httpClient;
								if (httpClient.upload_file_part(dbHostData.address, dbHostData.port, sFileName, sTmpPath, sPath, 0, llTotle))
								{
									sPath += httpClient.repsonse_data()["data"].asString();
									Json::Value jsonHost;
									jsonHost["hostid"] = dbHostData.guid;
									char szBuf[255] = { 0 };
									sprintf(szBuf, "0-%ld", llTotle);
									jsonHost["range"] = szBuf;
									jsonHost["name"] = sFileName;
									jsonHost["path"] = sPath;
									jsonStorageHostList.append(jsonHost);
									bIsFound = true;
									break;
								}
							}
						}
						if (bIsFound)
						{
							DB::StorageData dbStorageData;
							dbStorageData.guid = sStorageID;
							dbStorageData.storagehostlist =  Json::FastWriter().write(jsonStorageHostList);
							dbStorageData.name = sFileName;
							dbStorageData.size = (int)llTotle;
							dbStorageData.md5 = file_md5(sTmpPath);
							DB::Storage dbStorage;
							if (dbStorage.create(dbStorageData)->exec())
								break;
						}
					}
				}
			}
			else
				set_respond_back(HTTP_INTERNAL, "1", "no storage host!", "");
		}

		set_respond_back(HTTP_OK, "0", "successed", "", sStorageID);
	}

	void StorageUpload::background_process()
	{

	}
}