#include "Download.h"
#include "../Common.h"
#include "../Exception/HttpRequestException.h"
#include "../Database/Storage.h"
#include "../Database/Block.h"
#include  "Helper.h"
#include <string>
using namespace std;
using namespace Helper;
Download::Download(ServiceData *pD) :m_pD(pD)
{
}

Download::~Download()
{
}

void Download::process_task()
{
	char szBuf[255];
	if (check_input_data())
	{
		sprintf(szBuf, " `guid`=\"%s\" and `status`=0x02 ", _sStorageID.c_str());
		DB::StorageData *pSD = DB::Storage().query()->where(szBuf)->first();
		if (pSD)
		{
			_llTotal = pSD->size;
			if (_llEnd == 0)
				_llEnd = _llTotal - 1;

			sprintf(szBuf, " `storage_id`=\"%s\" and (`start`>=%I64d and `start`<=%I64d) or (`end`>=%I64d and `end`<=%I64d)", _sStorageID.c_str(), _llStart, _llEnd, _llStart, _llEnd);
			vector<DB::BlockData> *pBlocks = DB::Block().query()->where(szBuf)->all();
			if (pBlocks)
			{
				int nCount = pBlocks->size();
				char *szData = new char[_llEnd - _llStart + 1];
				for (int nIndex = 0; nIndex < nCount; nIndex++)
				{
					DB::BlockData &bd = (*pBlocks)[nIndex];
					Network::download()
				}
			}
			else
			{
				delete pSD;
				sprintf(szBuf, "available block for storage %s is not found.", _sStorageID.c_str());
				m_pD->set_respond_back(499, "1", szBuf, "");
			}
		}
		else
		{
			sprintf(szBuf, "available storage %s is not found.", _sStorageID.c_str());
			m_pD->set_respond_back(499, "1", szBuf, "");
		}
	}
}

bool Download::check_input_data()
{
	// 文件名
	_sFileName = "";

	// 唯一标识
	_sStorageID = m_pD->request_data().vecParameters[0];

	// 解析Range头信息
	string sRange = m_pD->request_data().mHeaders["range"];
	sscanf_s(sRange.c_str(), "bytes %I64d-%I64d/%I64d", &_llStart, &_llEnd, &_llTotal);

	return true;
}
