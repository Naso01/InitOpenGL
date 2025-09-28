#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()

GameController::GameController() {
	m_mesh = { };
	m_camera = { };
	m_shader = { };
	m_playerLocation = { 0,0,0 };
	m_Triangles = { };
}

void GameController::Initialize() {

	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f); // Blue background
	glEnable(GL_CULL_FACE);
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

}

int GameController::RandomNumber() {
	int ranNum = rand() % 9 + 2;
	int ranSign = rand() % 2;

	if (ranSign == 0) { ranNum = -ranNum; }

	return ranNum;
}

void GameController::RunGame() {

	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	//Player
	Mesh player;
	player.Create(&m_shader);
	m_Triangles.push_back(player);


	//10 NPCs Object Matrix
	int ranNumX = 0;
	int ranNumY = 0;
	int ranSign = 0;
	srand(time(0));
	std::vector<glm::vec3> npcLocations;
	for (int i = 0; i < 10; i++) {
		Mesh npc;

		ranNumX = RandomNumber();
		ranNumY = RandomNumber();

		cout <<"X: " << ranNumX << endl;
		cout <<"y: " << ranNumX << endl;

		if (ranSign == 0) { ranNumY = -ranNumY; }

		npcLocations.push_back({ ranNumX, ranNumY, 0 });
		
		npc.Create(&m_shader);
		m_Triangles.push_back(npc);
	}
	std::vector<bool> npcIsBlue(npcLocations.size(), false);


	WindowController* window = new WindowController;

	do {		

		System::Windows::Forms::Application::DoEvents(); // Handle Windows events
		
		glClear(GL_COLOR_BUFFER_BIT); //Clear the screen 

		//Player
		GLint colorLoc = glGetUniformLocation(m_shader.GetProgramID(), "OverrideColor");
		glUniform3f(colorLoc, 1.0f, 0.0f, 0.0f); // Red color

		GLint useOverrideLoc = glGetUniformLocation(m_shader.GetProgramID(), "UseOverrideColor");
		glUniform1i(useOverrideLoc, 0);

		m_Triangles[0].Render(glm::translate((m_camera.GetProjection() * m_camera.GetView()), m_playerLocation));

		if (glfwGetKey(window->GetInstance().GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
			//cout << "w" << endl;
			m_playerLocation.y += 0.003f;
		}
		if (glfwGetKey(window->GetInstance().GetWindow(), GLFW_KEY_S) == GLFW_PRESS){
			m_playerLocation.y -= 0.003f;
			//cout << "s" << endl;
		}
		if (glfwGetKey(window->GetInstance().GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
			m_playerLocation.x -= 0.003f;
			//cout << "a" << endl;
		}
		if (glfwGetKey(window->GetInstance().GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
			m_playerLocation.x += 0.003f;
			//cout << "d" << endl;
		}

            
            for (int i = 1; i < m_Triangles.size(); i++) {
				// Render NPC facing the player
                glm::vec3 npcToPlayer = glm::normalize(m_playerLocation - npcLocations[i - 1]);
                float cosa = glm::dot(glm::vec3{0, 1, 0}, npcToPlayer);
                cosa = glm::clamp(cosa, -1.0f, 1.0f);
                float angle = glm::degrees(glm::acos(cosa));
                float crossZ = glm::cross(glm::vec3{0, 1, 0}, npcToPlayer).z;
                float signedAngle = crossZ < 0 ? -angle : angle;

                float distance = glm::distance(m_playerLocation, npcLocations[i-1]);

                if (distance > 11) {
                    glm::vec3 destination = m_playerLocation - npcToPlayer;
                    npcLocations[i - 1] += (glm::normalize((destination - npcLocations[i - 1])) * 0.0015f);
                }
                if (distance < 10) {
                    glm::vec3 destination = m_playerLocation - npcToPlayer;
                    npcLocations[i - 1] -= (glm::normalize((destination - npcLocations[i - 1])) * 0.0015f);
                }

                // Change color if distance <= 1
				if (distance <= 1) {
					npcIsBlue[i - 1] = true;
				}
				//if npc is tagged, turn blue
				if (npcIsBlue[i - 1]) {
					GLint colorLoc = glGetUniformLocation(m_shader.GetProgramID(), "OverrideColor");
					glUniform3f(colorLoc, 0.0f, 0.0f, 1.0f); // Blue color

					GLint useOverrideLoc = glGetUniformLocation(m_shader.GetProgramID(), "UseOverrideColor");
					glUniform1i(useOverrideLoc, 2);
				}
				else {
					GLint colorLoc = glGetUniformLocation(m_shader.GetProgramID(), "OverrideColor");
					glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f); // Green color

					GLint useOverrideLoc = glGetUniformLocation(m_shader.GetProgramID(), "UseOverrideColor");
					glUniform1i(useOverrideLoc, 1);
				}

                m_Triangles[i].Render(
                    glm::rotate(
                        glm::translate((m_camera.GetProjection() * m_camera.GetView()), npcLocations[i - 1]),
                        glm::radians(signedAngle),
                        glm::vec3{0, 0, 1}
                    )
                );
            }

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed


	for (int i = 0; i < m_Triangles.size(); i++) {
		m_Triangles[i].Cleanup();
	}
	m_shader.Cleanup();
}
