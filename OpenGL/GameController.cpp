#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"

GameController::GameController() {
	
	//m_meshes.clear();
	m_skybox = { };
	m_camera = { };
	//Shader
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderSkybox = { };
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

	//Face Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
#pragma endregion SetupShaders

	//Create meshes
#pragma region CreateMeshes
	Mesh m = CreateMesh(m_shaderColor, "teapot.obj", { 0.01f, 0.01f, 0.01f }, 
												 { 0.0f,  0.8f,  1.0f });
	m.SetColor({1.0f, 1.0f , 1.0f });
	Mesh::Lights.push_back(m);

	Mesh fighter = CreateMesh(m_shaderDiffuse, "fighter.obj",	{0.002f, 0.002f, 0.002f }, 
														{0.0f, 0.0f, 0.0f});
	fighter.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(fighter);

	/*
	Skybox m_skybox = Skybox();
	m_skybox.Create(&m_shaderSkybox, "../Assets/Models/Skybox.obj",
		{ "../Assets/Textures/Skybox/right.jpg",
		  "../Assets/Textures/Skybox/left.jpg",
		  "../Assets/Textures/Skybox/top.jpg",
		  "../Assets/Textures/Skybox/bottom.jpg",
		  "../Assets/Textures/Skybox/front.jpg",
		  "../Assets/Textures/Skybox/back.jpg" });
	*/
#pragma endregion CreateMeshes

#pragma region CreateFonts

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 40);

#pragma endregion CreateFonts
#pragma region Render
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
		f.RenderText("Testing text", 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(WindowController::GetInstance().GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC key was pressed
		glfwWindowShouldClose(WindowController::GetInstance().GetWindow()) == 0); // Check if the window was closed
#pragma endregion Render

#pragma region Cleanup
	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Cleanup();
	}
	for (unsigned int count = 0; count < m_meshes.size(); count++) {
		m_meshes[count].Cleanup();
	}
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();
	m_skybox.Cleanup();
	m_shaderSkybox.Cleanup();

#pragma endregion Cleanup
}