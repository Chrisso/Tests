// TestCurl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define CURL_STATICLIB
#include <curl/curl.h>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
	_tprintf(_T("\t%d * %d\n"), size, nmemb);
	return size * nmemb;
}

int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	_tprintf(_T("-> %d/ %d\n"), (int)dlnow, (int)dltotal);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);
	
	CURL *curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.tagesschau.de/xml/rss2");
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif

	return 0;
}

