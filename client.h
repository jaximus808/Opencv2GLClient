#ifndef CLIENT_H
#define CLIENT_H

#include"Model.h"
#include"Mesh.h"



class Client
{
public:

	Client(int _id, const char* _modelpath, Shader& shader, Camera& camera, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 initalRotationEuler = glm::vec3(0.0f, 0.0f, 0.0f));

	Client(int _id, const char* _modelpath, Shader& shader, Camera& camera, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat initalRotationEuler = glm::quat(0.0f, 0.0f, 0.0f, 0.0f));

	Client();

	int id();

	void updateClientState(glm::vec3 newPosition, glm::vec3 eulerRotation);

	void moveClientState(glm::vec3 displacement, glm::vec3 rotation);


	void Draw();
private: 
	int clientId;
	const char* modelPath;
	Model clientModel;

};

#endif // !CLIENT_H
