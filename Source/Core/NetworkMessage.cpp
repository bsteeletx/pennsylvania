#include "NetworkMessage.h"
#include "agk.h"

NetworkMessage::NetworkMessage(void)
{
	messageID = create();
}

NetworkMessage::~NetworkMessage(void)
{
	deleteNM();
}

void NetworkMessage::addFloat(float value)
{
	agk::AddNetworkMessageFloat(messageID, value);
}

void NetworkMessage::addInt(int value)
{
	agk::AddNetworkMessageInteger(messageID, value);
}

void NetworkMessage::addString(Text Value)
{
	agk::AddNetworkMessageString(messageID, Value.getString());
}

unsigned int NetworkMessage::get(void)
{
	return agk::GetNetworkMessage(networkID);
}

float NetworkMessage::getFloat(void)
{
	return agk::GetNetworkMessageFloat(messageID);
}

unsigned int NetworkMessage::getFromClient(void)
{
	return agk::GetNetworkMessageFromClient(messageID);
}

Text NetworkMessage::getFromIP(void)
{
	return Text(agk::GetNetworkMessageFromIP(messageID));
}

int NetworkMessage::getInt(void)
{
	return agk::GetNetworkMessageInteger(messageID);
}

Text NetworkMessage::getString(void)
{
	return Text(agk::GetNetworkMessageString(messageID));
}

void NetworkMessage::send(unsigned int clientID)
{
	agk::SendNetworkMessage(networkID, clientID, messageID);
}

unsigned int NetworkMessage::create(void)
{
	return agk::CreateNetworkMessage();
}

void NetworkMessage::deleteNM(void)
{
	agk::DeleteNetworkMessage(messageID);
}