#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"

GameController::GameController() {
	
	//m_meshBoxes.clear();	- Implemented by default by the compiler 
	//m_meshLight = { };

	m_camera = { };

	m_shaderColor = { };
	m_shaderDiffuse = { };
}

void GameController::Initialize() {

	// Create a default window
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Grey background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

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

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	//Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Teapot.obj");
	m.SetPosition({1.0f, 0.0f, 0.0f});
	m.SetColor({1.0f, 1.0f , 1.0f });
	m.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(m);
		
	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/Teapot.obj");
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale({ 0.02f, 0.02f, 0.02f });
	teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshBoxes.push_back(teapot);

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

	do {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen

		//Box
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Light
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Fomt
		f.RenderText("it has a flower texture", 10, 500, 0.5f, { 1.0f, 1.5f, 1.0f });
		f.RenderText("The cake is a lie", 1000, 500, 0.5f, { 1.0f, 0.0f, 0.0f });
		f.RenderText("This is a teapot", 500, 10, 0.5f, { 1.0f, 1.0f, 1.0f });

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
		m_meshBoxes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}