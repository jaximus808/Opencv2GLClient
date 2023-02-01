#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <unordered_map>
#include"client.h"
#include"NetworkManager.h"
#include<thread>
#include"Packet.h"
class GameManager
{
public: 
	GameManager(const char* setTarget, unsigned int setPort, const char* vertShader, const char* fragShader, int width, int height, glm::vec3 camPos, const char* windowName);

	void CreateClient(int modelId, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 initalRotationEuler = glm::vec3(0.0f, 0.0f, 0.0f));

	GLFWwindow* getWindow();

	Camera* getCamera();

	void ActivateShader();

	void StartRecieve(std::vector<Packet>* packetQueue, bool* listeningToServer);

	int getShaderId();

	void endProgram();

	void UpdateFrame(float deltaTime);

	void SendData(Packet packet);

	void handlePacket(Packet packet);

	void initalGameState(int localId, std::vector<int> ids, std::vector<glm::vec3> positions, std::vector<glm::vec3> rotations, std::vector<int> modelId);

	void CreateClient(int modelId, glm::vec3 initialPosition, glm::quat initalRotationQuat);

	void updatePlayerState(int updateId, std::vector<glm::vec3> positions, std::vector<glm::vec3> rotations);

	void handlePacket(Packet _packet);

	void ConnectToMeta();

	void EndRecieve();

private:
	std::unordered_map<int, Client> clients;
	const char* target;
	unsigned int port;
	
	Shader shaderProgram;
	Camera camera;

	GLFWwindow* window;

	NetworkManager socket =  NetworkManager("192.168.1.8",8000);
	int id; 
	int localModelId; 

	bool listeningRecieve; 

	int windowWidth;
	int windowHeight;
};

#endif // !GAMEMANAGER_H
