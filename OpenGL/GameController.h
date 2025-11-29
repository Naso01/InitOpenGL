#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"

class GameController : public Singleton<GameController>
{
public:
	//Contrutor / Destructor
	GameController();
	virtual ~GameController(){ }

	//Methods
	void Initialize();
	void RunGame();
	Mesh CreateMesh(Shader* _shader, string _obj, glm::vec3 _scale, glm::vec3 _position, int _instanceCount = 1);

	void SetMeshPosition(glm::vec3 _pos);
	void SetLightPosition(glm::vec3 _pos);
	void SetColorByPosition(bool _ColorByPosition);

	void MoveCubesToSphere(bool _moveCubeToSphere);
	void CreateCube();

	void UpdateCubeMovement(float _deltaTime);

	//Member
	static bool m_leftMouseHeld;
	static GameController* Active;

private:
	//Methods
	//Methods
	static void RenderToolWindow();
	void MoveMesh(GLFWwindow* _window);

	//Members
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	Camera m_camera;
	
	vector<Mesh> m_meshes;
	Mesh m_meshSphere;
	Skybox m_skybox;
	GLuint vao;
};

#endif //!GAME_CONTROLLER_H
