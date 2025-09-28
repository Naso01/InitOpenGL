#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
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
	int RandomNumber();
	void PlayerTransform(GLFWwindow* window, unsigned int key);

private:
	Shader m_shader;
	Camera m_camera;
	Mesh m_mesh;
	std::vector < glm::mat4> m_objectMatrices;
	std::vector <Mesh> m_Triangles;
	glm::vec3 m_playerLocation;
	Mesh m_player;
};

#endif //!GAME_CONTROLLER_H
