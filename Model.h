#ifndef  MODEL_H
#define MODEL_H

#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;

class Model
{
public: 
	Model(const char* file, Shader& shader, Camera& camera, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 initalRotationEuler = glm::vec3(0.0f, 0.0f, 0.0f));


	Model(const char* file, Shader& shader, Camera& camera, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::quat initalRotationEuler = glm::quat(0.0f, 0.0f, 0.0f, 0.0f));

	Model();

	void Draw();

	void Move(glm::vec3 displacement);

	void Rotate(glm::vec3 eulerRotation);

	void setPosition(glm::vec3 newPosition);

	void setRotate(glm::quat quaterRotation );

	void setRotate(glm::vec3 eulerRotation);

private: 
	const char* file;
	std::vector<unsigned char> data;
	json JSON; 

	glm::vec3 position; 
	glm::vec3 eulerRotation;
	glm::quat rotation;

	Shader *crntShader;
	Camera *crntCamera;
	std::vector<Mesh> meshes; 
	std::vector<glm::vec3> translationMeshes;
	std::vector<glm::quat> rotationMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	void loadMesh(unsigned int indMesh);

	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	std::vector<unsigned char> getData();
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	std::vector<Vertex> assembleVertices(std::vector<glm::vec3> position, std::vector<glm::vec3> normals, std::vector<glm::vec2> texUVs);


	std::vector < glm::vec2 > groupFloatsVec2(std::vector<float> floatVec);
	std::vector < glm::vec3 > groupFloatsVec3(std::vector<float> floatVec);
	std::vector < glm::vec4 > groupFloatsVec4(std::vector<float> floatVec);

};

#endif // ! MODEL_H
