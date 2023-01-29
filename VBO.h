#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>

#include<glad/glad.h>
#include<vector>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	
	GLuint  ID;
	
	VBO(std::vector<Vertex>& vertices);

	VBO(GLfloat vertices[], GLsizeiptr size);
	
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void UnBind();
	// Deletes the VBO
	void Delete();
};

#endif