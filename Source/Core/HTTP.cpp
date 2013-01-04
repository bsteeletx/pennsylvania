#include "agk.h"
#include "HTTP.h"

HTTP::HTTP()
{
	httpID = createConnection();
}

HTTP::~HTTP()
{
	deleteConnection();
}

void HTTP::close()
{
	agk::CloseHTTPConnection(httpID);
}

int HTTP::getFile(Text CompleteURLPath, Text LocalStorage, Text PostData)
{
	return agk::GetHTTPFile(httpID, CompleteURLPath.getString(), LocalStorage.getString(), PostData.getString());
}

int HTTP::getFile(Text CompleteURLPath, Text LocalStorage)
{
	return agk::GetHTTPFile(httpID, CompleteURLPath.getString(), LocalStorage.getString());
}

bool HTTP::getFileComplete()
{
	if (agk::GetHTTPFileComplete(httpID) == 1)
		return true;

	return false;
}

float HTTP::getFileProgress()
{
	return agk::GetHTTPFileProgress(httpID);
}

Text HTTP::getResponse()
{
	return Text(agk::GetHTTPResponse(httpID));
}

bool HTTP::getResponseReady()
{
	if (agk::GetHTTPResponseReady(httpID) == 1)
		return true;

	return false;
}

int HTTP::sendFile(Text Page, Text PostData, Text LocalFile)
{
	return agk::SendHTTPFile(httpID, Page.getString(), PostData.getString(), LocalFile.getString());
}

Text HTTP::sendRequest(Text Page)
{
	return Text(agk::SendHTTPRequest(httpID, Page.getString()));
}

Text HTTP::sendRequest(Text Page, Text PostData)
{
	return Text(agk::SendHTTPRequest(httpID, Page.getString(), PostData.getString()));
}

int HTTP::sendRequestASync(Text Page, Text PostData)
{
	return agk::SendHTTPRequestASync(httpID, Page.getString(), PostData.getString());
}

int HTTP::sendRequestASync(Text Page)
{
	return agk::SendHTTPRequestASync(httpID, Page.getString());
}

int HTTP::setHost(Text Host, bool isSecure)
{
	if (isSecure)
		return agk::SetHTTPHost(httpID, Host.getString(), 1);

	return agk::SetHTTPHost(httpID, Host.getString(), 0);
}

int HTTP::setHost(Text Host, bool isSecure, Text Username, Text Password)
{
	if (isSecure)
		return agk::SetHTTPHost(httpID, Host.getString(), 1, Username.getString(), Password.getString());

	return agk::SetHTTPHost(httpID, Host.getString(), 0, Username.getString(), Password.getString());
}

unsigned int HTTP::createConnection()
{
	return agk::CreateHTTPConnection();
}

void HTTP::deleteConnection()
{
	agk::DeleteHTTPConnection(httpID);
}