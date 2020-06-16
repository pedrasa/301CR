#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <enet\enet.h>
#include <Box2D\Box2D.h>

struct Vector2
{
	float x;
	float y;
};

struct PhysicsData
{
	int packetType = 1;
	int clients;
	Vector2 positions[2];
};

struct ClientData
{
	int packetType = 0;
	int clientIndex;
	Vector2 position[2];
};

struct ClientPacket
{
	int clientIndex;
	int direction;
};

using namespace std;
class serverManager
{
public:
	serverManager();
	~serverManager();

	void connect();
	void disconnect();

	ENetHost* getClient();
	ENetPeer* getPeer();
	ENetAddress getAdress();
	ENetEvent getEvent();
	ENetPacket* getPacket();
private:
	ENetHost* client;
	ENetPeer* peer;
	ENetAddress address;
	ENetEvent enetEvent;
	ENetPacket* dataPacket;

};

