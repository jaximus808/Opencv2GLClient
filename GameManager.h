#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <unordered_map>
#include"client.h"
#include"NetworkManager.h"
class GameManager
{
public: 
	GameManager(const char* setTarget, unsigned int setPort, const char* vertShader, const char* fragShader, int width, int height, glm::vec3 camPos, const char* windowName);

	void CreateClient(int modelId, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 initalRotationEuler = glm::vec3(0.0f, 0.0f, 0.0f));

	GLFWwindow* getWindow();

	void ActivateShader();


	int getShaderId();

	void endProgram();

	void UpdateFrame(float deltaTime);

	void SendData(Packet packet);

private:
	std::unordered_map<int, Client> clients;
	const char* target;
	unsigned int port;
	
	Shader shaderProgram;
	Camera camera;

	GLFWwindow* window;

	NetworkManager socket =  NetworkManager("192.168.1.13",8000);
};

#endif // !GAMEMANAGER_H
