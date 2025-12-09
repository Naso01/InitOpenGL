#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "OBJ_Loader.h"

class Shader;

class Mesh
{
public:
	// Contructor / Destructor
	Mesh();
	virtual ~Mesh();

	//Accessors
	glm::vec3 GetPosition() { return m_position; }
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	void SetRotation(glm::vec3 _rotation) { m_rotation = _rotation; }
	glm::vec3 GetColor() { return m_color; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }
	void SetSpecularStrength(float _strength) { m_specularStrength = _strength; }
	float GetSpecularStrength() { return m_specularStrength; }
	glm::vec3 GetSpecularColor() { return m_specularColor; }
	void SetSpecularColor(glm::vec3 _specularColor) { m_specularColor = _specularColor; }


	//Methods
	void Create(Shader * _shader, string _file, int _instanceCount = 1);
	void Cleanup();
	void Render(glm::mat4 _wvp);
	void CalculateTransform();

	//Members
	static vector<Mesh> Lights;

private:
	//Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);
	string RemoveFolder(string _map);
	void CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);

	//Members
	Shader* m_shader;
	Texture m_diffuseTexture;
	Texture m_specularTexture;
	Texture m_normalTexture;

	bool m_enableNormalMap;
	int m_elementSize;
	bool m_enableInstancing;
	int m_instanceCount;

	GLuint m_vertexBuffer;//GPU Buffer
	GLuint m_indexBuffer; //GPU Buffer
	GLuint m_instanceBuffer; //GPU Buffer

	vector<GLfloat> m_vertexData; //Store vertex data in RAM
	vector<GLubyte> m_indexData; //Store index data in RAM
	vector<GLfloat> m_instanceData; // Store instance data in RAM

	//Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;

	//Lighting
	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;
	unsigned short m_specularStrength;
	glm::vec3 m_specularColor;
};

#endif // !MESH_H