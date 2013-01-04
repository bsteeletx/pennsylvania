#pragma once

#include "Text.h"

class Network
{
public:
	Network();
	~Network();
	Network(Text NetworkName, Text MyName);
	Network(Text NetNameOrIP, Text MyName, unsigned short portNumber = 1025);

	unsigned int getServerID(void);

	bool isActive(void);

	void setLatency(unsigned short latency);
	void setLocalFloat(Text VariableName, float value, bool resetAfterRead);
	void setLocalInt(Text VariableName, int value, bool resetAfterRead);
	void setNoMoreClients(void);

protected:
	unsigned int networkID;
	unsigned short port;

private:
	bool isHost;

	void close(void);

	bool isANum(char test);
};