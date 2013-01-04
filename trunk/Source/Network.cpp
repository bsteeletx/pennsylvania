#include "Network.h"
#include "agk.h"

Network::Network()
{
	networkID = 0;
	port = 1025;
	isHost = false;
}

Network::~Network()
{
	if (isActive())
		close();
}


//host
Network::Network(Text NetworkName, Text MyName)
{
	while (!isActive())
	{
		networkID = agk::HostNetwork(NetworkName.getString(), MyName.getString(), port);
		if (!networkID)
			port++;
	}

	isHost = true;
}

//join
Network::Network(Text NetNameOrIP, Text MyName, unsigned short portNumber)
{
	if (isANum(NetNameOrIP.getChar(0)))
		networkID = agk::JoinNetwork(NetNameOrIP.getString(), portNumber, MyName.getString());
	else
		networkID = agk::JoinNetwork(NetNameOrIP.getString(), MyName.getString());
}

unsigned int Network::getServerID(void)
{
	return agk::GetNetworkServerID(networkID);
}

bool Network::isActive(void)
{
	if (agk::IsNetworkActive(networkID) == 1)
		return true;
	
	return false;
}

void Network::setLatency(unsigned short latency)
{
	if (latency > 0.0f)
		agk::SetNetworkLatency(networkID, latency);
}

void Network::setLocalFloat(Text VariableName, float value, bool resetAfterRead)
{
	if (resetAfterRead)
		agk::SetNetworkLocalFloat(networkID, VariableName.getString(), value, 1);
	else
		agk::SetNetworkLocalFloat(networkID, VariableName.getString(), value, 0);
}

void Network::setLocalInt(Text VariableName, int value, bool resetAfterRead)
{
	if (resetAfterRead)
		agk::SetNetworkLocalInteger(networkID, VariableName.getString(), value, 1);
	else
		agk::SetNetworkLocalInteger(networkID, VariableName.getString(), value, 0);
}

void Network::setNoMoreClients(void)
{
	agk::SetNetworkNoMoreClients(networkID);
}

void Network::close(void)
{
	agk::CloseNetwork(networkID);
}

bool Network::isANum(char text)
{
	switch (text)
	{
	case '0': return true;
	case '1': return true;
	case '2': return true;
	case '3': return true;
	case '4': return true;
	case '5': return true;
	case '6': return true;
	case '7': return true;
	case '8': return true;
	case '9': return true;
	default: return false;
	}
}