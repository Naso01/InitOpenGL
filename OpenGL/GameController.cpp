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

	//Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	

	//10 NPCs Object Matrix
	int ranNumX = 0;
	int ranNumY = 0;
	int ranSign = 0;
	srand(time(0));



	std::vector<glm::vec3> randomVectors;

	for (int i = 1; i < 11; i++) {
		Mesh* npc = new Mesh();

		ranNumX = RandomNumber();
		ranNumY = RandomNumber();

		cout <<"X: " << ranNumX << endl;
		cout <<"y: " << ranNumX << endl;

		if (ranSign == 0) { ranNumY = -ranNumY; }

		randomVectors.push_back({ ranNumX, ranNumY, 0 });
		
		npc->Create(&m_shader, 1);
		m_Triangles.push_back(npc);
	}
	
	Mesh* player = new Mesh();
	player->Create(&m_shader, 0);
	m_Triangles.push_back(player);

	do {
		System::Windows::Forms::Application::DoEvents(); // Handle Windows events

		/*
		//Checkbox states from the tool window
		GLint loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);

		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);

		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
		*/

		glClear(GL_COLOR_BUFFER_BIT); //Clear the screen

		for (int i = 0; i < m_Triangles.size(); i++) {
			//Player
			if(i == 0)
				m_Triangles[i]->Render(glm::translate((m_camera.GetProjection() * m_camera.GetView()), m_playerLocation));
			//NPCs
			else
			m_Triangles[i]->Render(glm::translate((m_camera.GetProjection() * m_camera.GetView()), randomVectors[i-1]));
		}

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed


	for (int i = 0; i < m_Triangles.size(); i++) {
		m_Triangles[i]->Cleanup();
	}
	m_shader.Cleanup();
}