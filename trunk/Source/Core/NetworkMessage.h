#pragma once

//#include "Text.h"
#include "Network.h"

class NetworkMessage : public Network
{
public:
	NetworkMessage();
	~NetworkMessage();

	void addFloat(float value);
	void addInt(int value);
	void addString(Text Value);

	unsigned int get(void);
	float getFloat(void);
	unsigned int getFromClient(void);
	Text getFromIP(void);
	int getInt(void);
	Text getString(void);

	void send(unsigned int clientID);

private:
	unsigned int messageID;

	unsigned int create(void);
	
	void deleteNM(void);
};