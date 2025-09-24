#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_vertexData = { };
	m_world = glm::mat4(1.0f); // Identity matrix
}

Mesh::~Mesh() {

}

void Mesh::Create(Shader* _shader) {

	m_shader = _shader;

	//Cordinates for a triangle
	m_vertexData = {
		/*  Position  */ /*	    RGBA Color     */
		0.2f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f };

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp) {

	glUseProgram(m_shader->GetProgramID()); // Use the shader

	//1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3					/*size*/, 
		GL_FLOAT			/*type*/, 
		GL_FALSE			/*normalized*/, 
		7 * sizeof(float)	/*stride (7 floats per vertex definition)*/,
		(void*)0);			/*offset*/

	//2nd attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(),
		4,							//size (4 components per color value)
		GL_FLOAT,					//type
		GL_FALSE,					//normalized?
		7 * sizeof(float),			//stride (7 floats per vertex definition
		(void*)(3 * sizeof(float)));//Array buffer offset


	// 3rd attribute  :  WVP
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]); // Send our transformation to the currently bound shader, in the "WVP" uniform

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//Draw the Triangle !
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7); // Starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}