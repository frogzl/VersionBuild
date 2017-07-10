// VersionBuildServer.cpp : 定义控制台应用程序的入口点。
//
/*
A trivial static http webserver using Libevent's evhttp.

This is not the best code in the world, and it does some fairly stupid stuff
that you would never want to do in a production webserver. Caveat hackor!

*/

#include "Common.h"
#include "SystemConfig.h"
#include "VBTaskServer.h"
#include "VBHttpServer.h"
#include "VBRoute.h"
#include "VBController.h"
#include "Controller/ProductController.h"
#include "Controller/StorageController.h"
#include "Controller/CompressionPackageController.h"
#include "Controller/SourceCodeController.h"
#include "Controller/ServerController.h"
#include "Controller/BuildResultController.h"
#include "Controller/BuildRuleController.h"
#include "Controller/BuildRuleDeployController.h"
#include "Controller/BuildRuleDependController.h"
#include "Controller/HostController.h"
#include "Controller/SoftwarePackageController.h"
#include "Controller/ResourceController.h"
#define THREAD_COUNT 10
#define PORT 10001

using namespace std;
using namespace Controller;

void register_routing();
void register_task();
int main(int argc, char **argv)
{
	if (initialize_socket_environment()) 
		return 1;

	git_libgit2_init();
	SystemConfig::instance()->initConfig();

	// 注册路由
	register_routing();
	// 注册任务
	register_task();


	// 启动Task服务
	VBTaskServer ts;
	ts.start();

	// 启动http服务
	VBHttpServer hs(SystemConfig::instance()->m_nWorker);
	hs.start(SystemConfig::instance()->m_nNetworkPort, SystemConfig::instance()->m_nBacklog);

	// 等待结束
	hs.wait_for_end();
	ts.wait_for_end();

	clear_socket_environment();
	return 0;
}

void register_routing()
{
	// 注册路由
	Register_Route_Post("/server/init", ServerController, "init");
	Register_Route_Get("/server/resource/query", ServerController, "resource_query");

	Register_Route_Post("/product/create", ProductController, "create");
	Register_Route_Get("/product/query", ProductController, "query");
	Register_Route_Post("/product/modify", ProductController, "modify");
	Register_Route_Post("/product/delete", ProductController, "delete");
	Register_Route_Post("/product/build", ProductController, "build");
	Register_Route_Post("/product/publish", ProductController, "publish");
	Register_Route_Post("/product/deploy", ProductController, "deploy");

	// ResourceController
	Register_Route_Get("/resource/query", ResourceController, "query");

	// SourceCodeController
	Register_Route_Post("/sourcecode/create", SourceCodeController, "create");
	Register_Route_Get("/sourcecode/query", SourceCodeController, "query");
	Register_Route_Post("/sourcecode/modify", SourceCodeController, "modify");
	Register_Route_Post("/sourcecode/deploy", SourceCodeController, "deploy");
	Register_Route_Post("/sourcecode/build", SourceCodeController, "build");
	Register_Route_Post("/sourcecode/delete", SourceCodeController, "delete");

	// CompressionPackageController
	Register_Route_Post("/compressionpackage/create", CompressionPackageController, "create");
	Register_Route_Get("/compressionpackage/query", CompressionPackageController, "query");
	Register_Route_Post("/compressionpackage/modify", CompressionPackageController, "modify");
	Register_Route_Post("/compressionpackage/delete", CompressionPackageController, "delete");

	// HostController
	Register_Route_Post("/host/create", HostController, "create");
	Register_Route_Get("/host/query", HostController, "query");
	Register_Route_Get("/host/query/physical_information", HostController, "query_physical_information");
	Register_Route_Post("/host/modify", HostController, "modify");
	Register_Route_Post("/host/delete", HostController, "delete");

	// BuildRuleController
	Register_Route_Post("/buildrule/create", BuildRuleController, "create");
	Register_Route_Get("/buildrule/query", BuildRuleController, "query");
	Register_Route_Post("/buildrule/modify", BuildRuleController, "modify");
	Register_Route_Post("/buildrule/build", BuildRuleController, "build");	
	Register_Route_Post("/buildrule/deploy", BuildRuleController, "deploy");
	Register_Route_Post("/buildrule/delete", BuildRuleController, "delete");

	// BuildRuleDeployController
	Register_Route_Post("/buildruledeploy/create", BuildRuleDeployController, "create");
	Register_Route_Get("/buildruledeploy/query", BuildRuleDeployController, "query");
	Register_Route_Post("/buildruledeploy/modify", BuildRuleDeployController, "modify");
	Register_Route_Post("/buildruledeploy/delete", BuildRuleDeployController, "delete");

	// BuildRuleDependController
	Register_Route_Post("/buildruledepend/create", BuildRuleDependController, "create");
	Register_Route_Get("/buildruledepend/query", BuildRuleDependController, "query");
	Register_Route_Post("/buildruledepend/modify", BuildRuleDependController, "modify");
	Register_Route_Post("/buildruledepend/delete", BuildRuleDependController, "delete");

	// BuildResultController
	Register_Route_Post("/buildresult/create", BuildResultController, "create");
	Register_Route_Get("/buildresult/query", BuildResultController, "query");
	Register_Route_Post("/buildresult/modify", BuildResultController, "modify");
	Register_Route_Post("/buildresult/delete", BuildResultController, "delete");
	// StorageController
	Register_Route_Get("/Storage/download", StorageController, "download");
	Register_Route_Get("/Storage/download/part", StorageController, "download_part");
	Register_Route_Post("/Storage/upload", StorageController, "upload");
	Register_Route_Post("/Storage/upload/part", StorageController, "upload_part");

}

void register_task()
{

}