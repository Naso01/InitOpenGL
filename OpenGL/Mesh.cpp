#include "Mesh.h"

Mesh::Mesh() {
	m_vertexBuffer = 0;
}

Mesh::~Mesh() {

}

void Mesh::Create() {

	//m_shader = _shader;

	//Cordinates for a triangle
	m_vertexData = { -1.0f ,-1.0f, 0.0f,   1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f };

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render() {

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 
		3			/*size*/, 
		GL_FLOAT	/*type*/, 
		GL_FALSE	/*normalized*/, 
		0			/*stride*/, 
		(void*)0	/*offset*/);

	//Draw the Triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(0);
}