#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_vertexData = { };
}

Mesh::~Mesh() {

}

void Mesh::Create(Shader* _shader) {

	m_shader = _shader;

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

	glUseProgram(m_shader->GetProgramID()); // Use the shader

	//1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3			/*size*/, 
		GL_FLOAT	/*type*/, 
		GL_FALSE	/*normalized*/, 
		0			/*stride*/, 
		(void*)0	/*offset*/);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//Draw the Triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}