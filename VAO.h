#ifndef VAO_H
#define VAO_H

#include<glm/glm.hpp>
#include"VBO.h"
#include<glad/glad.h>

class VAO
{
public:
	GLuint ID;

	VAO();

	void Bind();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void UnBind();

	void Delete();
};

#endif // !VAO
