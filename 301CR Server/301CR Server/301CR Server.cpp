// 301CR Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>


using namespace std;

struct Vector2 {
	float x;
	float y;
};

struct PhysicsData {
	int packetType = 1;
	Vector2 positions[2];
};

struct ClientData {
	int packetType = 0;
	int clientIndex;
};

struct ClientPacket {
	int clientIndex;
	Vector2 position;
};

void main()
{
	int clientCount = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Server Window");
	sf::Event e;

	sf::RectangleShape background;
	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0.0f, 0.0f);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../Textures/background.png"))
	{
		cout << "Texture did not load!" << "\n";
	}

	background.setTexture(&backgroundTexture);

	//upper part is sfml preamble so we know the server

	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	ENetAddress address; //server adress
	ENetHost* server; //host server
	ENetEvent enetEvent; //arbitrary Event Enet is event driven 

	ENetPacket* dataPacket;
	/* We set the address to be a local host */

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	//create the server

	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}

	PhysicsData* physicsData = new PhysicsData;

	physicsData->positions[0].x = 600.0f;
	physicsData->positions[0].y = 300.0f;
	physicsData->positions[1].x = 100.0f;
	physicsData->positions[1].y = 300.0f;

	ClientPacket* clientPacket = new ClientPacket;

	clientPacket->clientIndex = 0;
	clientPacket->position.x = 0.0f;
	clientPacket->position.y = 0.0f;

	ClientData* clientData = new ClientData;

	string DataIdentityClient = "This is a client";

	while (window.isOpen())
	{
		window.pollEvent(e);

		if (e.type == sf::Event::Closed) {
			window.close();

		}

		//checkif connected or disconnected

		while (enet_host_service(server, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:

				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";

				clientData->clientIndex = clientCount;

				dataPacket = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(enetEvent.peer, 0, dataPacket);

				enetEvent.peer->data = &DataIdentityClient;
				clientCount++;

				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";

				enetEvent.peer->data = NULL;

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				memcpy(clientPacket, enetEvent.packet->data, enetEvent.packet->dataLength);
				int currentClient = clientPacket->clientIndex;
				//physicsData->positions[clientPacket->clientIndex] = clientPacket->position;
			}
		}

		/* Now we handle out keyboard inputs, manipulating the values of the
		position variable. Notice that these values are lower position changes
		than the equivalents Client-side - that's because if you set them
		equivalent, the server 'game loop' iterates far quicker than the client,
		letting it 'move faster'. This illustrates the dangers of untimed game
		loops which we highlighted last week. */

		//if (e.type == sf::Event::KeyPressed)
		//{
		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		//	{
		//		position.x += -0.2f;
		//	}

		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		//	{
		//		position.x += 0.2f;
		//	}
		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		//	{
		//		position.y += -0.2f;
		//	}
		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		//	{
		//		position.y += 0.2f;
		//	}

		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		//	{
		//		window.close();
		//	}

		//	cout << "The position of the entity is (" << position.x << "," << position.y << ")\n";

		//	dataPacket = enet_packet_create(&position, sizeof(Vector2), ENET_PACKET_FLAG_RELIABLE);
		//	enet_host_broadcast(server, 0, dataPacket);
		//}

		dataPacket = enet_packet_create(physicsData, sizeof(PhysicsData), ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(server, 0, dataPacket);

		window.clear(sf::Color::Blue);
		window.draw(background);
		window.display();
	}

	//destroy eveything on shutdown

	delete physicsData;
	delete clientData;
	delete clientPacket;

	enet_host_destroy(server);
	atexit(enet_deinitialize);
}

