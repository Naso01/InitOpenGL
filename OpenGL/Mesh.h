#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class Mesh
{
public:
	// Contructor / Destructor
	Mesh();
	virtual ~Mesh();

	//Methods
	void Create(Shader * _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp);

private:
	//Members
	Shader* m_shader;
	Texture m_texture;
	GLuint m_vertexBuffer;//GPU Buffer
	GLuint m_indexBuffer; //GPU Buffer
	
	std::vector<GLfloat> m_vertexData; //Store vertex data in RAM
	std::vector<GLubyte> m_indexData; //Store index data in RAM
	
	glm::vec3 m_position;
	glm::vec3 m_rotation;
};

#endif // !MESH_H