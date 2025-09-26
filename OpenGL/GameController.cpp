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
}

void GameController::Initialize() {

	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f); // Blue background
	glEnable(GL_CULL_FACE);
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

	//10 NPCs Object Matrix
	int ranNumX = 0;
	int ranNumY = 0;
	int ranSign = 0;

	glm::mat4 worldMatrix = glm::mat4(1.0f);

	for (int i = 0; i < 10; i++) {

		srand(time(0));
		//ran must be within {2, 10} or {-10, -2}
		ranNumX = rand() % 11 + 2;
		ranSign = rand() % 1;

		if (ranSign == 0) {
			ranNumX = -ranNumX;
		}

		srand(time(0));
		//ran must be within {2, 10} or {-10, -2}
		ranNumY = rand() % 11 + 2;
		ranSign = rand() % 1;

		if (ranSign == 0) {
			ranNumY = -ranNumY;
		}

		//m_objectMatrices[i] = glm::translate(m_objectMatrices[i], { ranNumX, ranNumY, 0 });
	}
}

void GameController::RunGame() {

	//Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	//Create and compile our GLSL program from the shaders
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

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
		m_player.Render(m_camera.GetProjection() * m_camera.GetView()); // Gives mesh View and Projection matrices


		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	m_player.Cleanup();
	m_shader.Cleanup();
}