#include"client.h"

Client::Client(int _id, const char* _modelpath, Shader& shader, Camera& camera, glm::vec3 initialPosition, glm::vec3 initalRotationEuler )
{
	clientModel = Model(_modelpath, shader, camera, initialPosition, initalRotationEuler);
}

Client::Client(int _id, const char* _modelpath, Shader& shader, Camera& camera, glm::vec3 initialPosition, glm::quat initalRotationEuler)
{
	clientModel = Model(_modelpath, shader, camera, initialPosition, initalRotationEuler);
}

Client::Client()
{

}

void Client::updateClientState(glm::vec3 newPosition, glm::vec3 eulerRotation)
{
	clientModel.setPosition(newPosition);
	clientModel.setRotate(eulerRotation);
}

void Client::moveClientState(glm::vec3 newPosition, glm::vec3 eulerRotation)
{

	clientModel.Move(newPosition);
	clientModel.Rotate(eulerRotation);
}

void Client::Draw()
{
	clientModel.Draw();
}

int Client::id()
{
	return clientId;
}