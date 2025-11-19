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

	//Accessors
	glm::vec3 GetPosition() { return m_position; }
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }
	void SetColorByPosition(bool _colorByPosition) { m_colorByPosition = _colorByPosition; }

	//Methods
	void Create(Shader * _shader, string _file);
	void Cleanup();
	void Render(glm::mat4 _pv);
	void Render(glm::mat4 _pv, glm::vec4 _specular);
	void CalculateTransform();

	//Members
	static vector<Mesh> Lights;

private:
	//Methods
	void SetShaderVariables(glm::mat4 _pv);
	void SetShaderVariables(glm::mat4 _pv, glm::vec4 _specular);

	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);

	//Members
	Shader* m_shader;
	Texture m_diffuseTexture;
	Texture m_specularTexture;
	GLuint m_vertexBuffer;//GPU Buffer
	GLuint m_indexBuffer; //GPU Buffer
	
	std::vector<GLfloat> m_vertexData; //Store vertex data in RAM
	std::vector<GLubyte> m_indexData; //Store index data in RAM
	
	//Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;

	//Lighting
	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;

	bool m_hasTexture;
	bool m_colorByPosition;
};

#endif // !MESH_H