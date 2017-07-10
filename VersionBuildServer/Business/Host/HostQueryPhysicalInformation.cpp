#include "HostQueryPhysicalInformation.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"

namespace B
{


	HostQueryPhysicalInformation::HostQueryPhysicalInformation(Controller::Controller *pController) :HostBusiness(pController)
	{
	}

	HostQueryPhysicalInformation::~HostQueryPhysicalInformation()
	{
	}

	void HostQueryPhysicalInformation::process_task()
	{
		Json::Value jsonData;
		jsonData["operatingsystem"] = getOperatingSystem();
		jsonData["cpu"] = getCPU();
		jsonData["memory"] = getMemory();
		jsonData["storage"] = getStorage();
		jsonData["environmentvariable"] = getEnvironmentVariable();

		set_respond_back(HTTP_OK, "0", "successed", "", jsonData);
	}

	void HostQueryPhysicalInformation::background_process()
	{

	}

	Json::Value HostQueryPhysicalInformation::getOperatingSystem()
	{
		string sOSName = "";
		string sOSMask = "";
		string sOSPlatform = "";
		SYSTEM_INFO si;
		GetNativeSystemInfo(&si);
		if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
			si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_IA64)
			sOSPlatform = "x64";
		else
			sOSPlatform = "x86";


		OSVERSIONINFOEXA osvi;
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
		if (GetVersionExA((OSVERSIONINFOA*)&osvi))
		{
			switch (osvi.dwMajorVersion)
			{                        //判断主版本号  
			case 4:
				switch (osvi.dwMinorVersion)
				{                //判断次版本号  
				case 0:
					if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
						sOSName = "Microsoft Windows NT 4.0";  //1996年7月发布  
					else if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
						sOSName = "Microsoft Windows 95";
					break;
				case 10:
					sOSName = "Microsoft Windows 98";
					break;
				case 90:
					sOSName = "Microsoft Windows Me";
					break;
				}
				break;
			case 5:
				switch (osvi.dwMinorVersion)
				{               //再比较dwMinorVersion的值  
				case 0:
					sOSName = "Microsoft Windows 2000";    //1999年12月发布  
					if (osvi.wSuiteMask == VER_SUITE_ENTERPRISE)
						sOSMask = "Advanced Server";
					break;
				case 1:
					sOSName = "Microsoft Windows XP";      //2001年8月发布  
					if (osvi.wSuiteMask == VER_SUITE_EMBEDDEDNT)
						sOSMask = "Embedded";
					else if (osvi.wSuiteMask == VER_SUITE_PERSONAL)
						sOSMask = "Home Edition";
					else
						sOSMask = "Professional";
					break;
				case 2:
					if (osvi.wProductType == VER_NT_WORKSTATION &&
						si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
						sOSName = "Microsoft Windows XP Professional x64 Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0)
						sOSName = "Microsoft Windows Server 2003";   //2003年3月发布  
					else if (GetSystemMetrics(SM_SERVERR2) != 0)
						sOSName = "Microsoft Windows Server 2003 R2";

					if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_BLADE)  //Windows Server 2003  
						sOSMask = "Web Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_COMPUTE_SERVER)
						sOSMask = "Compute Cluster Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_STORAGE_SERVER)
						sOSMask = "Storage Server";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_DATACENTER)
						sOSMask = "Datacenter Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_ENTERPRISE)
						sOSMask = "Enterprise Edition";
					else if (GetSystemMetrics(SM_SERVERR2) != 0 && osvi.wSuiteMask == VER_SUITE_STORAGE_SERVER)
						sOSMask = "Storage Server";
					break;
				}
				break;
			case 6:
				switch (osvi.dwMinorVersion)
				{
				case 0:
					if (osvi.wProductType == VER_NT_WORKSTATION)
						sOSName = "Microsoft Windows Vista";
					else
						sOSName = "Microsoft Windows Server 2008";   //服务器版本  

					if (osvi.wProductType != VER_NT_WORKSTATION && osvi.wSuiteMask == VER_SUITE_DATACENTER)
						sOSMask = "Datacenter Server";
					else if (osvi.wProductType != VER_NT_WORKSTATION &&osvi.wSuiteMask == VER_SUITE_ENTERPRISE)
						sOSMask = "Enterprise";
					else if (osvi.wProductType == VER_NT_WORKSTATION &&osvi.wSuiteMask == VER_SUITE_PERSONAL)  //Windows Vista  
						sOSMask = "Home";
					break;
				case 1:
					if (osvi.wProductType == VER_NT_WORKSTATION)
						sOSName = "Microsoft Windows 7";
					else
						sOSName = "Microsoft Windows Server 2008 R2";
					break;
				case 2:
					if (osvi.wProductType == VER_NT_WORKSTATION)
						sOSName = "Microsoft Windows 8";
					else
						sOSName = "Microsoft Windows Server 2012";

					if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_BLADE)  //Windows Server 2003  
						sOSMask = "Web Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_COMPUTE_SERVER)
						sOSMask = "Compute Cluster Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_STORAGE_SERVER)
						sOSMask = "Storage Server";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_DATACENTER)
						sOSMask = "Datacenter Edition";
					else if (GetSystemMetrics(SM_SERVERR2) == 0 && osvi.wSuiteMask == VER_SUITE_ENTERPRISE)
						sOSMask = "Enterprise Edition";
					else if (GetSystemMetrics(SM_SERVERR2) != 0 && osvi.wSuiteMask == VER_SUITE_STORAGE_SERVER)
						sOSMask = "Storage Server";
					break;
				}
				break;
			case 10:
				switch (osvi.dwMinorVersion)
				{
				case 0:
					if (osvi.wProductType == VER_NT_WORKSTATION)
						sOSName = "Microsoft Windows 10";
					else
						sOSName = "Windows Server 2016";
					break;
				}
				break;
			default:
				sOSName = "unknow system";
			}
		}


		Json::Value replyData;
		replyData["name"] = sOSName;
		replyData["platform"] = sOSPlatform;
		replyData["mask"] = sOSMask;
		return replyData;
	}

	Json::Value HostQueryPhysicalInformation::getCPU()
	{
		return "";
	}

	Json::Value HostQueryPhysicalInformation::getMemory()
	{
		MEMORYSTATUS   Mem;
		GlobalMemoryStatus(&Mem);

		unsigned long ulSize = (unsigned long)Mem.dwTotalPhys;
		unsigned long ulVirtSize = (unsigned long)Mem.dwTotalVirtual;

		char szBuf[255];
		Json::Value replyData;
		sprintf(szBuf, "%lu", ulSize);
		replyData["physicalmemory"] = szBuf;
		sprintf(szBuf, "%lu", ulVirtSize);
		replyData["virtualmemory"] = szBuf;
		return replyData;
	}

	Json::Value HostQueryPhysicalInformation::getStorage()
	{
		Json::Value replyData;
		DWORD dwSize = GetLogicalDriveStringsA(0, NULL);
		char *szDriveStrings = new char[dwSize + 1];
		dwSize = GetLogicalDriveStringsA(dwSize + 1, szDriveStrings);
		char *pszBegin = szDriveStrings;
		char *pszEnd = szDriveStrings + dwSize + 1;
		while (pszBegin != pszEnd)
		{
			ULARGE_INTEGER nFreeBytesAvailable;
			ULARGE_INTEGER nTotalNumberOfBytes;
			ULARGE_INTEGER nTotalNumberOfFreeBytes;
			if (GetDiskFreeSpaceExA(pszBegin, &nFreeBytesAvailable, &nTotalNumberOfBytes, &nTotalNumberOfFreeBytes))
			{
				char szFreeBytesAvailable[256];
				char szTotalNumberOfBytes[256];
				char szTotalNumberOfFreeBytes[256];
				sprintf(szFreeBytesAvailable, "%lld", nFreeBytesAvailable);
				sprintf(szTotalNumberOfBytes, "%lld", nTotalNumberOfBytes);
				sprintf(szTotalNumberOfFreeBytes, "%lld", nTotalNumberOfFreeBytes);

				Json::Value partitionData;
				partitionData["name"] = pszBegin;
				partitionData["freebytesavailable"] = szFreeBytesAvailable;
				partitionData["totalnumberofbytes"] = szTotalNumberOfBytes;
				partitionData["totalnumberoffreebytes"] = szTotalNumberOfFreeBytes;
				replyData.append(partitionData);
			}
			pszBegin += (strlen(pszBegin) + 1);
		}
		return replyData;
	}

	Json::Value HostQueryPhysicalInformation::getEnvironmentVariable()
	{
		Json::Value replyData;
		char *szEnv = NULL;
		szEnv = getenv("include");
		if (szEnv)
		{
			Json::Value includeData;
			includeData["name"] = "include";
			includeData["value"] = szEnv;
			replyData.append(includeData);
		}
		szEnv = getenv("lib");
		if (szEnv)
		{
			Json::Value libpathData;
			libpathData["name"] = "lib";
			libpathData["value"] = szEnv;
			replyData.append(libpathData);
		}
		szEnv = getenv("path");
		if (szEnv)
		{
			Json::Value pathData;
			pathData["name"] = "path";
			pathData["value"] = szEnv;
			replyData.append(pathData);
		}
		return replyData;
	}
}