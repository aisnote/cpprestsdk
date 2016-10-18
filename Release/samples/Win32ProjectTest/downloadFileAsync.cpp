#include "stdafx.h"
#include "downloadFileAsync.h"


downloadFileAsync::downloadFileAsync()
{
}


downloadFileAsync::~downloadFileAsync()
{
}

// The code includes the most frequently used includes necessary to work with C++ REST SDK


void downloadFileAsync::DisplayJSONValue(json::value v)
{
	if (!v.is_null())
	{
		// Loop over each element in the object
// 		for (auto iter = v.arr; iter != v.cend(); ++iter)
// 		{
// 			// It is necessary to make sure that you get the value as const reference
// 			// in order to avoid copying the whole JSON value recursively (too expensive for nested objects)
// 			const json::value &key = iter->first;
// 			const json::value &value = iter->second;
//
// 			if (value.is_object() || value.is_array())
// 			{
// 				// We have an object with children or an array
// 				if ((!key.is_null()) && (key.is_string()))
// 				{
// 					std::wcout << L"Parent: " << key.as_string() << std::endl;
// 				}
// 				// Loop over each element in the object by calling DisplayJSONValue
// 				DisplayJSONValue(value);
// 				if ((!key.is_null()) && (key.is_string()))
// 				{
// 					std::wcout << L"End of Parent: " << key.as_string() << std::endl;
// 				}
// 			}
// 			else
// 			{
// 				// Always display the value as a string
// 				std::wcout << L"Key: " << key.as_string() << L", Value: " << value.to_string() << std::endl;
// 			}
// 		}
	}
}

pplx::task<void> downloadFileAsync::HTTPGetAsync()
{
	// I want to make the following HTTP GET: http://localhost:58957/api/groups
	http_client client(U("https://guest-a.wbx2.com/guest/api/v1/ping"));

	// Manually build up an HTTP request with a header that specifies the content type and the request URI
	http_request request(methods::GET);
	request.headers().set_content_type(L"application/json");
	request.set_request_uri(U("groups"));


	// Make an HTTP GET request and asynchronously process the response
	return client
		.request(request)
		// The following code executes when the response is available
		.then([](http_response response) -> pplx::task<json::value>
	{
		std::wostringstream stream;
		stream.str(std::wstring());
		stream << L"Content type: " << response.headers().content_type() << std::endl;
		stream << L"Content length: " << response.headers().content_length() << L"bytes" << std::endl;
		std::wcout << stream.str();

		// If the status is OK extract the body of the response into a JSON value
		if (response.status_code() == status_codes::OK)
		{
			return response.extract_json();
		}
		else
		{
			// return an empty JSON value
			return pplx::task_from_result(json::value());
		}
		// Continue when the JSON value is available
	}).then([this](pplx::task<json::value> previousTask)
	{
		// Get the JSON value from the task and call the DisplayJSONValue method
		try
		{
			json::value const & value = previousTask.get();
			DisplayJSONValue(value);
		}
		catch (http_exception const & e)
		{
			std::wcout << e.what() << std::endl;
		}
	});
}