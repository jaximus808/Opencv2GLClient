#include"GameManager.h"
#include <stdlib.h>


/*

Packets:
	0: inital
	1: update 


*/
glm::vec3 EulerDegVecToRad(glm::vec3 euler)
{
	return glm::vec3(glm::radians(euler.x), glm::radians(euler.y), glm::radians(euler.z) );
}

void GameManager::ActivateShader()
{
	shaderProgram.Activate();
}

void GameManager::handlePacket(Packet _packet)
{
	int packetId = _packet.readInt();
	
	if (packetId == 0)
	{
		int setId = _packet.readInt();
		
		int clientsLength = _packet.readInt();

		
	}
	
	

}

GameManager::GameManager(const char* setTarget, unsigned int setPort, const char* vertShader, const char* fragShader, int width, int height, glm::vec3 camPos, const char* windowName)
{
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	windowWidth = width;
	windowHeight = height;
	if (window == NULL)
	{
		std::cout << "ERROR WINDOW";
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);
	target = setTarget;
	port = setPort; 
	
	shaderProgram = Shader(vertShader, fragShader);
	//glm::vec3(0.0f, 0.0f, 2.0f)
	camera = Camera(width, height, camPos, window);
	id = -1;
	localModelId = 0;
}

void GameManager::SendData(Packet packet)
{
	socket.SendData(packet);
}


void GameManager::CreateClient(int modelId, glm::vec3 initialPosition , glm::vec3 initalRotationEuler )
{
	std::string modelPath;
	if (modelId == 0)
	{
		modelPath = "Model/ClientModel/scene.gltf";
	}
	//Client client(0, modelPath.c_str(), shaderProgram, camera, glm::vec3(-25.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	
	clients.insert({ 0,Client(0, modelPath.c_str(), shaderProgram, camera, initialPosition, initalRotationEuler + EulerDegVecToRad(glm::vec3(0.0f, 0.0f, 180.0f))) });
	//clients[0].updateClientState(initialPosition, EulerDegVecToRad(glm::vec3(0.0f, 0.0f, 180.0f)));
}


void GameManager::UpdateFrame(float deltaTime)
{
	camera.Inputs(deltaTime);

	camera.updateMatrix(45.0f, 0.1f, 1000000.0f);

	//drawing the clients
	std::unordered_map<int, Client > ::iterator it = clients.begin();

	while (it != clients.end())
	{
		//it->second.moveClientState(glm::vec3(-10.0f * deltaTime, 0.0f, 0.0f), glm::vec3(10.0f * deltaTime, 0.0f, 0.0f));
		it->second.Draw();
		it++;
	}

}

void GameManager::ConnectToMeta()
{
	Packet initalPacket; 

	//metaglasses
	initalPacket.Write(0);

	//inital packet
	initalPacket.Write(0);

	initalPacket.Write(localModelId);

	std::cout << initalPacket.size() << std::endl;

	SendData(initalPacket); 
}

//convert euler to rads
void GameManager::initalGameState(int localId, std::vector<int> ids, std::vector<glm::vec3> positions, std::vector<glm::vec3> rotations, std::vector<int> modelIds)
{
	id = localId;
	for (int i = 0; i < ids[i]; i++)
	{
		CreateClient(modelIds[i], positions[i], rotations[i]);
	}
}

void GameManager::StartRecieve(std::vector<Packet>* packetQueue, bool* listeningToServer)
{
	socket.BeginThread(packetQueue, listeningToServer);
}

void GameManager::EndRecieve()
{
	socket.StopThread();
}

Camera* GameManager::getCamera()
{
	return &camera;
}

GLFWwindow* GameManager::getWindow()
{
	return window;
}

int GameManager::getShaderId()
{
	return shaderProgram.ID;
}

void GameManager::endProgram()
{
	shaderProgram.Delete(); 
	glfwDestroyWindow(window);
	glfwTerminate();
}