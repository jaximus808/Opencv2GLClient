#include"GameManager.h"
#include <stdlib.h>
void GameManager::ActivateShader()
{
	shaderProgram.Activate();
}

GameManager::GameManager(const char* setTarget, unsigned int setPort, const char* vertShader, const char* fragShader, int width, int height, glm::vec3 camPos, const char* windowName)
{
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
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
		modelPath = "Model/sword/scene.gltf";
	}
	//Client client(0, modelPath.c_str(), shaderProgram, camera, glm::vec3(-25.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	clients.insert({ 0,Client(0, modelPath.c_str(), shaderProgram, camera, initialPosition, initalRotationEuler) });
}

void GameManager::UpdateFrame(float deltaTime)
{
	camera.Inputs(deltaTime);

	camera.updateMatrix(45.0f, 0.1f, 1000000.0f);

	//drawing the clients
	std::unordered_map<int, Client > ::iterator it = clients.begin();

	while (it != clients.end())
	{
		it->second.moveClientState(glm::vec3(-10.0f * deltaTime, 0.0f, 0.0f), glm::vec3(10.0f * deltaTime, 0.0f, 0.0f));
		it->second.Draw();
		it++;
	}

	/*clients[0].moveClientState(glm::vec3(-5.0f * deltaTime, 0.0f, 0.0f), glm::vec3(10.0f * deltaTime, 0.0f, 0.0f)); 
	clients[0].Draw();*/
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