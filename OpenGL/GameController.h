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

private:
	//Members
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shader;

	Camera m_camera;
	
	vector<Mesh> m_meshBoxes;
	//Mesh m_meshLight;
};

#endif //!GAME_CONTROLLER_H
