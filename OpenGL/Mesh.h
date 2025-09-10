#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"

class Mesh
{
public:
	// Contructor / Destructor
	Mesh();
	virtual ~Mesh();

	//Methods
	void Create();
	void Cleanup();
	void Render();

private:
	GLuint m_vertexBuffer;
	std::vector<GLfloat> m_vertexData;
};

#endif // !MESH_H