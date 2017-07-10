#pragma once
#include <string>
#include <map>
#include "../Common.h"
using namespace std;
namespace Controller
{
#define dd(d) #d
#define mm(d) d
#define m(x) mm(new_)##x
#define Declare_Controller_Class(own, parent) parent* m(own)(struct evhttp_request  *req);\
 class own: public parent{ 
#define Declare_Controller_Class_End() };
#define Declare_Controller_Class_Common(own) public:own(struct evhttp_request  *req);mm(~)##own();void call_function(string sFunctionName);
#define Declare_Controller_Class_Function(funName) void mm(vb_)funName();

#define Define_Controller_Class_Common(own, parent) own::##own(struct evhttp_request  *req):parent(req){} \
own::##mm(~)##own(){}\
 parent* m(own)(struct evhttp_request  *req) { return new own(req);}\
 void own::call_function(string sFunctionName){
#define Define_Controller_Class_Common_End() }
#define Define_Controller_Class_Function(own, funName) void own::mm(vb_)funName()
#define Controller_Class_Function_Filter(funName) 	if (sFunctionName.compare(dd(funName)) == 0) mm(vb_)funName();

	class Controller
	{
	public:
		Controller(struct evhttp_request  *req);
		~Controller();
	public:
		virtual void call_function(string sFunctionName) = 0;
		void do_business(void *pBusiness = NULL);
		bool get_input_parameters(map<string, string> &mapParameter);

		char* get_input_buffer();
		char* get_input_buffer(struct evhttp_request  *req);
		bool get_input_headers(map<string, string> &mapHeader);
		bool get_input_headers(struct evhttp_request  *req, map<string, string> &mapHeader);
	private:
		static void http_request_done(struct evhttp_request *req, void *arg);
		void send_respond(void *pBusiness = NULL);
		void send_respond_success(char *szBuf);
		void redirect_request_get(string sHost, int nPort);
		void redirect_request_post(string sHost, int nPort);
	protected:
		struct evhttp_request *m_req;
	};

	typedef Controller* (*Fun)(struct evhttp_request *req);
}