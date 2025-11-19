#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
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
	
	void SetMeshPosition(glm::vec3 _pos);
	void SetColorByPosition(bool _ColorByPosition);
	
	void MoveCubesToSphere(bool _moveCubeToSphere);
	void CreateCube();

	//Member
	static bool m_leftMouseHeld;
	static GameController* Active;

private:
	//Methods
	static void RenderToolWindow();
	void MoveLight(GLFWwindow* _window);

	//Members
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderLight;

	Camera m_camera;
	
	vector<Mesh> m_meshBoxes;
};

void MouseClickCallback(GLFWwindow* window, int button, int action, int mods);
#endif //!GAME_CONTROLLER_H
