#include "Mesh.h"
#include "Shader.h"
#include "OBJ_Loader.h"

vector <Mesh> Mesh::Lights;

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
}

Mesh::~Mesh() {

}

void Mesh::Cleanup() {
	
	glDeleteBuffers(1, &m_vertexBuffer);
	m_diffuseTexture.Cleanup();
	m_specularTexture.Cleanup();
}

void Mesh::Create(Shader* _shader , string _file) {

	m_shader = _shader;

	//Initialize Loader
	objl::Loader Loader;
	M_ASSERT(Loader.LoadFile(_file) == true, "Failed to load mesh."); // Load .obj File

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++) {

		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++) {

			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);
		}
	}

	//Remove directory if present
	string diffuseNap = Loader.LoadedMaterials[0].map_Kd;
	const size_t last_slash_idx = diffuseNap.find_last_of("\\");
	if (std::string::npos != last_slash_idx) {

		diffuseNap.erase(0, last_slash_idx + 1);
	}

	m_diffuseTexture = Texture();
	m_diffuseTexture.LoadTexture("../Assets/Textures/" + diffuseNap);
	m_specularTexture = Texture();
	m_specularTexture.LoadTexture("../Assets/Textures/" + diffuseNap);
	
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}



void Mesh::BindAttributes() {

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //Bind the vertex buffer

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
}

void Mesh::CalculateTransform() {
	
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}

string Mesh::Concat(string _s1, int _index, string _s2) {
	string index = to_string(_index);
	return (_s1 + index + _s2);
}

void Mesh::SetShaderVariables(glm::mat4 _pv) {

	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	//Configure lighting
	for (unsigned int i = 0; i < Lights.size(); i++) {

		m_shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 0.25f, 0.25f, 0.25f });
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), Lights[i].GetColor());
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 2.0f, 2.0f, 2.0f });

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);

		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
	}
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

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}