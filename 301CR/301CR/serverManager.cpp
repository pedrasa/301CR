#include "serverManager.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <enet\enet.h>
#include <Box2D\Box2D.h>

using namespace std;


PhysicsData* serverData;
ClientData* clientData;

int* packetType;
int clientIndex;

ClientPacket* clientPacket;

serverManager::serverManager()
{
	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	client = getClient();
	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		cout << "Client failed to initialise!" << "\n\n";
	}

	address = getAdress();

	enet_address_set_host(&address, "localhost");
	address.port = 1234;

	peer = getPeer();
	peer = enet_host_connect(client, &address, 2, 0); //connecting

	if (peer == NULL) {
		cout << "No available peers for initializing an ENet connection.\n";
	}

	//Vector2* newPosition = new Vector2;

	clientPacket = new ClientPacket;

	serverData = new PhysicsData;
	clientData = new ClientData;
	packetType = new int;
	clientIndex = -1;
	*packetType = -1;

	cout << "Client initialised!" << "\n\n";

}

serverManager::~serverManager()
{
}

void serverManager::connect()
{
	enetEvent = getEvent();
	dataPacket = getPacket();
	while (enet_host_service(getClient(), &enetEvent, 0) > 0)
	{
		switch (enetEvent.type) {
		case ENET_EVENT_TYPE_RECEIVE:

			memcpy(packetType, enetEvent.packet->data, sizeof(int));

			if (*packetType == 0)
			{
				cout << "Packet Received!\n";
				memcpy(clientData, enetEvent.packet->data, sizeof(ClientData));
				clientIndex = clientData->clientIndex;

				/*if (clientIndex == 0)
				{
					avatarInitialised = true;
					avatarBodyDef.position.Set(clientData->position[0].x, clientData->position[0].y);
					avatarBody = world.CreateBody(&avatarBodyDef);
					avatarBody->CreateFixture(&avatarFixDef);

				}
				else
				{
					enemyInitialised = true;
					enemyBodyDef.position.Set(clientData->position[0].x, clientData->position[0].y);
					enemyBody = world.CreateBody(&enemyBodyDef);
					enemyBody->CreateFixture(&enemyFixDef);

					avatarInitialised = true;
					avatarBodyDef.position.Set(clientData->position[1].x, clientData->position[1].y);
					avatarBody = world.CreateBody(&avatarBodyDef);
					avatarBody->CreateFixture(&avatarFixDef);
				}*/
			}
			else if (*packetType == 1)
			{
				memcpy(serverData, enetEvent.packet->data, sizeof(PhysicsData));

				/*if (!enemyInitialised)
				{
					if (serverData->clients == 2)
					{
						enemyInitialised = true;
						enemyBodyDef.position.Set(clientData->position[1].x, clientData->position[1].y);
						enemyBody = world.CreateBody(&enemyBodyDef);
						enemyBody->CreateFixture(&enemyFixDef);
					}
				}*/

				memcpy(serverData, enetEvent.packet->data, sizeof(PhysicsData));
				/*for (int i = 0; i < 2; i++)
				{
					b2Vec2 direction;
					b2Vec2 targetPos;
					b2Vec2 currentPos;

					if (clientIndex == 0)
					{
						if (avatarInitialised && avatarBody != nullptr) {
							targetPos.x = serverData->positions[0].x;
							targetPos.y = serverData->positions[0].y;
							currentPos.x = avatarBody->GetPosition().x;
							currentPos.y = avatarBody->GetPosition().y;

							direction = targetPos - currentPos;
							direction.Normalize();

							direction.x = direction.x * speed;
							direction.y = direction.y * speed;

							avatarBody->SetLinearVelocity(direction);
						}
						if (enemyInitialised && enemyBody != nullptr) {
							targetPos.x = serverData->positions[1].x;
							targetPos.y = serverData->positions[1].y;
							currentPos.x = enemyBody->GetPosition().x;
							currentPos.y = enemyBody->GetPosition().y;

							direction = targetPos - currentPos;
							direction.Normalize();

							direction.x = direction.x * speed;
							direction.y = direction.y * speed;
							enemyBody->SetLinearVelocity(direction);
						}
					}
					else if (clientIndex == 1)
					{
						if (avatarInitialised && avatarBody != nullptr) {
							targetPos.x = serverData->positions[1].x;
							targetPos.y = serverData->positions[1].y;
							currentPos.x = avatarBody->GetPosition().x;
							currentPos.y = avatarBody->GetPosition().y;

							direction = targetPos - currentPos;
							direction.Normalize();

							direction.x = direction.x * speed;
							direction.y = direction.y * speed;

							avatarBody->SetLinearVelocity(direction);
						}
						if (enemyInitialised && enemyBody != nullptr) {
							targetPos.x = serverData->positions[0].x;
							targetPos.y = serverData->positions[0].y;
							currentPos.x = enemyBody->GetPosition().x;
							currentPos.y = enemyBody->GetPosition().y;

							direction = targetPos - currentPos;
							direction.Normalize();

							direction.x = direction.x * speed;
							direction.y = direction.y * speed;
							enemyBody->SetLinearVelocity(direction);
						}
					}
				}*/
			}

			break;
		}

		clientPacket->clientIndex = clientIndex;
		dataPacket = enet_packet_create(clientPacket, sizeof(ClientPacket), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(getPeer(), 0, dataPacket);
	}
}

void serverManager::disconnect()
{
	if (getPeer() != NULL)
	{
		enet_peer_disconnect_now(peer, 0);
		atexit(enet_deinitialize);
	}
}

ENetHost* serverManager::getClient()
{
	return client;
}

ENetPeer* serverManager::getPeer()
{
	return peer;
}

ENetAddress serverManager::getAdress()
{
	return address;
}

ENetEvent serverManager::getEvent()
{
	return enetEvent;
}

ENetPacket* serverManager::getPacket()
{
	return dataPacket;
}



