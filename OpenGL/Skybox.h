#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"

class Skybox {
public:
	//Constructors / Destructors
	Skybox();
	virtual ~Skybox();

	//Methods
	void Create(Shader* _shader, string _file, vector<string> _faces);
	void Cleanup();
	void Render(glm::mat4 _pv);

private:
	//Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();

	//Members
	Shader* m_shader;
	Texture m_texture;
	GLuint m_vertexBuffer; // GPU buffer
	vector<GLfloat> m_vertexData; // Store vertex data in RAM
};

#endif //!SKYBOX_H