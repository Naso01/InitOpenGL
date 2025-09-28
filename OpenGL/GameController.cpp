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

	m_player = { };
	m_NPCTriangles = { };
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

	for (int i = 0; i < 10; i++) {

		m_NPCTriangles.push_back(new Mesh());

		ranNumX = RandomNumber();
		ranNumY = RandomNumber();

		cout <<"X: " << ranNumX << endl;
		cout <<"y: " << ranNumX << endl;

		if (ranSign == 0) { ranNumY = -ranNumY; }

		randomVectors.push_back({ ranNumX, ranNumY, 0 });

		int colorCode[4] = { 0, 1, 0, 1 };
		//m_NPCTriangles[i]->ChangeColor(colorCode);
		m_NPCTriangles[i]->Create(&m_shader);
	}

	System::Windows::Forms::Application::DoEvents();

	m_player = Mesh();
	m_player.Create(&m_shader);

	do {
		System::Windows::Forms::Application::DoEvents(); // Handle Windows events

		//Checkbox states from the tool window
		GLint loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);

		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);

		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);


		glClear(GL_COLOR_BUFFER_BIT); //Clear the screen

		//Player
		m_player.Render(glm::translate((m_camera.GetProjection() * m_camera.GetView()), { 0, 0, 0 })); // Gives mesh View and Projection matrices

		//NPCs
		for (int i = 0; i < m_NPCTriangles.size(); i++) {

			m_NPCTriangles[i]->Render(glm::translate((m_camera.GetProjection() * m_camera.GetView()), randomVectors[i]));
		}


		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	m_player.Cleanup();
	for (int i = 0; i < m_NPCTriangles.size(); i++) {
		m_NPCTriangles[i]->Cleanup();
	}
	m_shader.Cleanup();
}