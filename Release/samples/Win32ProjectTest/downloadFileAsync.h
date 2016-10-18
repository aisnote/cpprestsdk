#pragma once

#include <cpprest/containerstream.h>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/producerconsumerstream.h>
#include <iostream>
#include <sstream>

using namespace ::pplx;
using namespace utility;
using namespace concurrency::streams;

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;


class downloadFileAsync
{
public:
	downloadFileAsync();
	virtual ~downloadFileAsync();


	void DisplayJSONValue(json::value v);
	pplx::task<void> HTTPGetAsync();
};

