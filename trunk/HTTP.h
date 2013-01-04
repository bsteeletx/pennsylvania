#pragma once
#include "Text.h"

class HTTP
{
public:
	HTTP();
	~HTTP();

	void close();

	int getFile(Text CompleteURLPath, Text LocalStorage, Text PostData);
	int getFile(Text CompleteURLPath, Text LocalStorage);
	bool getFileComplete();
	float getFileProgress();
	Text getResponse();
	bool getResponseReady();

	int sendFile(Text Page, Text PostData, Text LocalFile);
	Text sendRequest(Text Page);
	Text sendRequest(Text Page, Text PostData);
	int sendRequestASync(Text Page, Text PostData);
	int sendRequestASync(Text Page);
	int setHost(Text Host, bool isSecure);
	int setHost(Text Host, bool isSecure, Text Username, Text Password);

private:
	unsigned int httpID;

	unsigned int createConnection();
	
	void deleteConnection();
};