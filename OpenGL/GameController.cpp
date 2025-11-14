#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"

GameController::GameController() {
	
	//m_meshes.clear();	- Implemented by default by the compiler 
	//m_meshLight = { };

	m_camera = { };

	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
}

void GameController::Initialize() {

	// Create a default window
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Grey background
	glEnable(GL_DEPTH_TEST);	//Configure global OpenGl state
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand((unsigned int)time(0));

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

//Custom Method
Mesh GameController::CreateMesh(Shader _shader, string _obj, glm::vec3 _scale, glm::vec3 _position) {

	Mesh m = Mesh();
	m.Create(&_shader, "../Assets/Models/"+ _obj);
	m.SetScale(_scale);
	m.SetPosition(_position);

	return m;
}

void GameController::RunGame() {
	
	//Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	//Create and compile our GLSL program from the shaders
#pragma region SetupShaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
#pragma endregion SetupShaders

	//Create meshes
#pragma region CreateMeshes
	Mesh m = CreateMesh(m_shaderColor, "teapot.obj", { 0.01f, 0.01f, 0.01f }, 
												 { 1.0f,  0.0f,  0.0f });
	m.SetColor({1.0f, 1.0f , 1.0f });
	Mesh::Lights.push_back(m);
		
	Mesh teapot = CreateMesh(m_shaderDiffuse, "teapot.obj", { 0.02f, 0.02f, 0.02f },
		{ 0.0f, 0.0f, 0.0f });
	teapot.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(teapot);

	Mesh box = CreateMesh(m_shaderDiffuse, "Cube.obj", { 0.5f, 0.5f, 0.5f },
		{ -1.0f, -1.0f, -1.0f });
	box.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(box);

	Mesh plane = CreateMesh(m_shaderDiffuse, "Plane.obj", { 0.3f, 0.3f, 0.3f },
												  { 0.0f, 0.0f, 0.0f });
	plane.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(plane);
#pragma endregion CreateMeshes

	do {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen - Clear depth buffer every frame

		//Box
		for (unsigned int count = 0; count < m_meshes.size(); count++) {
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Light
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Font

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < m_meshes.size(); count++) {
		m_meshes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
}