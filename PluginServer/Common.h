#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <winsock2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <process.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_compat.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <json/json.h>
#include <direct.h>
#include <algorithm>
#ifdef WIN32
#include <ws2tcpip.h>
#include <io.h>
#include <fcntl.h>
#include <objbase.h> 
#ifndef S_ISDIR
#define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#endif
#else
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <uuid/uuid.h> 
#endif

#ifdef WIN32
#define stat _stat
#define fstat _fstat
#define open _open
#define close _close
#define O_RDONLY _O_RDONLY
#endif

#define dd(d) #d
#define mm(d) d
#define m(x) mm(new_)##x
#define Register_Route_Get(a, b, c) { VBController::register_class(#b, m(b));VBRoute::get(a, #b, c); }
#define Register_Route_Post(a, b, c) { VBController::register_class(#b, m(b));VBRoute::post(a, #b, c); }
#define Buffer_Size 10 * 1024 * 1024

#include "../util-internal.h"

using namespace std;

struct table_entry
{
	const char *extension;
	const char *content_type;
}; 
extern struct table_entry content_type_table[];

int initialize_socket_environment();
void clear_socket_environment();
void split(string s, const char *pDelim, vector<string>& ret);
int u2g(const char *inbuf, int inlen, char *outbuf, int outlen);
int g2u(const char *inbuf, size_t inlen, char *outbuf, size_t outlen);


//以下是 Base64.cpp 的内容:

string getGUID();
void split(string s, string delim, vector<string>* ret);
int compare(string str1, string str2);

string file_md5(string sFilePath);
// trim from start 
std::string &ltrim(std::string &s);
// trim from end 
std::string &rtrim(std::string &s);

string app_root_path();