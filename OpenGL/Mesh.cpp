#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_vertexData = { };
	m_indexBuffer = 0;
	m_world = glm::mat4(1.0f); // Identity matrix 
}

Mesh::~Mesh() {

}

void Mesh::Create(Shader* _shader) {

	m_shader = _shader;

	//Triangles
	m_vertexData = {
		/* Position */ /*	RGBA Color	*/
		1, 0, 0, 1.0f, 0.0f, 0.0f, 1.0f, // Red
		0, 2, 0, 1.0f, 0.0f, 0.0f, 1.0f, // Red
		-1, 0, 0, 1.0f, 0.0f, 0.0f, 1.0f, // Red
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_indexBuffer);  
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
	//m_world = glm::rotate(m_world, 0.001f, { 0, 1, 0 });
	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]); // Send our transformation to the currently bound shader, in the "WVP" uniform

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //Bind the vertex buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); //Bind the index buffer
	//glDrawArrays(GL_LINES, 0, m_vertexData.size() / 7); // Starting from vertex 0; n * 2 = vertices | n = number of lines
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7);
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}