#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include<vector>

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(std::vector<GLuint>& indicies);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void UnBind();
	// Deletes the EBO
	void Delete();
};

#endif