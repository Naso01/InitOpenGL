#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Camera.h"
#include "PostProcessor.h"
#include "InputController.h"

class InputController;

class GameController : public Singleton<GameController>
{
public:
	//Contrutor / Destructor
	GameController();
	virtual ~GameController(){ }

	//Methods
	void Initialize();
	void RunGame();
	Mesh CreateMesh(Shader _shader, string _obj, glm::vec3 _scale, glm::vec3 _position, int _instanceCount = 1);
	static void RenderToolWindow();

private:
	//Members
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	Shader m_shaderPost;

	Camera m_camera;
	PostProcessor m_postProcessor;
	vector<Mesh> m_meshes;
	Mesh m_fishMesh;
	Skybox m_skybox;
	GLuint vao;
	InputController m_inputController;
};

#endif //!GAME_CONTROLLER_H
