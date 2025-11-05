#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
//#include "ToolWindow.h"

GameController::GameController() {
	
	//m_meshBoxes.clear();	- Implemented by default by the compiler 
	m_meshLight = { };

	m_camera = { };

	m_shaderColor = { };
	m_shaderDiffuse = { };
}

void GameController::Initialize() {

	// Create a default window
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_DEPTH_TEST);
	srand(time(0));
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::RunGame() {
	
	//Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	//Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	//Create meshes
	m_meshLight = Mesh();
	m_meshLight.Create(&m_shaderColor);
	m_meshLight.SetPosition({ 1, -0.5f, 0.0f });
	m_meshLight.SetScale({ 0.1f, 0.1f, 0.1f });
	
	for (int count = 0; count < 10; count++) {
		
		Mesh box = Mesh();
		box.Create(&m_shaderDiffuse);
		box.SetLightColor({ 1.0f, 1.0f, 1.0f });
		box.SetLightPosition(m_meshLight.GetPosition());
		box.SetCameraPosition(m_camera.GetPosition());
		box.SetScale({ 0.3f, 0.3f ,0.3f });
		box.SetPosition({ glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f) });
		m_meshBoxes.push_back(box);
	}

	do {
		
		//Checkbox states from the tool window 
		/*
		GLint loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
		
		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
		
		loc = glGetUniformLocation(m_shader.GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
		*/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView()); 
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	m_meshLight.Cleanup();
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
		m_meshBoxes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}