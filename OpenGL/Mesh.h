#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
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
	GLuint m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;
	glm::mat4 m_world;
};

#endif // !MESH_H