#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Standard Includes.h"
#include "Mesh.h"

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
	Mesh m_mesh;
};

#endif //!GAME_CONTROLLER_H
