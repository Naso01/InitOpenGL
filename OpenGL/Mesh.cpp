#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
	m_shader = nullptr;
	
	m_diffuseTexture = { };
	m_specularTexture = { };
	
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_lightPosition = { 0, 0, 0 };
	m_lightColor = { 1, 1, 1 }; //White light

	//m_cameraPosition = { };
}

Mesh::~Mesh() {

}

void Mesh::Cleanup() {
	
	glDeleteBuffers(1, &m_vertexBuffer);
	m_diffuseTexture.Cleanup();
	m_specularTexture.Cleanup();
}

void Mesh::Create(Shader* _shader) {

	m_shader = _shader;

	m_diffuseTexture = Texture();
	m_diffuseTexture.LoadTexture("../Assets/Textures/MetalFrameWood.jpg");
	m_specularTexture = Texture();
	m_specularTexture.LoadTexture("../Assets/Textures/MetalFrame.jpg");

#pragma region VertexData
	m_vertexData = {
		/*	  Position    */  /*    Normals    */  /* Texture Coords */
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
#pragma endregion

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::BindAttributes() {
	//1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attribute we want to configure
		3,							//size (3 vertices per primitive)
		GL_FLOAT,					//type
		GL_FALSE,					//normalized?
		8 * sizeof(float),			//stride (8 floats per vertex definition
		(void*)0);//Array buffer offset

	//2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),	//The attribute we want to configure
		3,							//size (3 vertices per primitive)
		GL_FLOAT,					//type
		GL_FALSE,					//normalized?
		8 * sizeof(float),			//stride (8 floats per vertex definition
		(void*)(3 * sizeof(float)));//Array buffer offset


	// 3rd attribute buffer :  texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(),//The attribute we want to configure
		2,							//size (3 vertices per primitive)
		GL_FLOAT,					//type
		GL_FALSE,					//normalized?
		8 * sizeof(float),			//stride (8 floats per vertex definition
		(void*)(6 * sizeof(float)));//Array buffer offset

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //Bind the vertex buffer
}

void Mesh::CalculateTransform() {
	
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv) {

	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);

	//Configure lighting
	m_shader->SetVec3("light.color", m_lightColor);
	m_shader->SetFloat("light.constant", 1.0f);
	m_shader->SetFloat("light.linear", 0.09f);
	m_shader->SetFloat("light.quadratic", 0.032f);

	m_shader->SetVec3("light.ambientColor", { 0.1f, 0.1f, 0.1f });
	m_shader->SetVec3("light.diffuseColor", { 1.0f, 1.0f, 1.0f });
	m_shader->SetVec3("light.specularColor", { 3.0f, 3.0f, 3.0f });

	m_shader->SetVec3("light.position", m_lightPosition);
	m_shader->SetVec3("light.direction", glm::normalize(glm::vec3({0, 0, 0}) - m_lightPosition));
	m_shader->SetFloat("light.coneAngle", glm::radians(15.0f));
	m_shader->SetFloat("light.falloff", 100);

	//Configure material
	m_shader->SetFloat("material.specularStrength", 8);
	m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_diffuseTexture.GetTexture());
	m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_specularTexture.GetTexture());
}

void Mesh::Render(glm::mat4 _pv) {

	glUseProgram(m_shader->GetProgramID()); // Use the shader

	m_rotation.y += 0.001f;
	
	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 8);
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}