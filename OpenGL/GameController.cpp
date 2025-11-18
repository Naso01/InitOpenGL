#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"
#include "ToolWindow.h"

GameController::GameController() {
	
	//m_meshBoxes.clear();	- Implemented by default by the compiler 
	//m_meshLights.clear();

	m_camera = { };

	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderLight = { };
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

void GameController::RenderToolWindow() {
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	System::Windows::Forms::Application::Run(window);
}

void GameController::SetLightPosition(glm::vec3 _pos) {
	Mesh::Lights[0].SetPosition(_pos);
}

void GameController::RunGame() {
	
	//Show the C++/CLI tool window
#pragma region ToolWindow
	System::Threading::Thread^ uiThread =
		gcnew System::Threading::Thread(
			gcnew System::Threading::ThreadStart(&GameController::RenderToolWindow)
		);

	uiThread->SetApartmentState(System::Threading::ApartmentState::STA);
	uiThread->IsBackground = true;
	uiThread->Start();
#pragma endregion ToolWindow
	

	//Create and compile our GLSL program from the shaders
#pragma region Shader Create/Compile

	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	m_shaderLight = Shader();
	m_shaderLight.LoadShaders("Light.vertexshader", "Light.fragmentshader");

#pragma endregion Shader Create/Compile


	//Create meshes
#pragma region Mesh Creation
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	m.SetPosition({1.0f, 1.0f, 0.1f});
	m.SetColor({1.0f, 1.0f , 1.0f });
	m.SetScale({ 0.005f, 0.005f, 0.005f });
	Mesh::Lights.push_back(m);
		
	Mesh teapot = Mesh();
	teapot.Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
	teapot.SetCameraPosition(m_camera.GetPosition());
	teapot.SetScale({ 0.02f, 0.02f, 0.02f });
	teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshBoxes.push_back(teapot);
#pragma endregion Mesh Creation

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);

	do {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen

#pragma region ToolWindow
		//Specular Strength
		//GLint loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "material.specularStrength");
		//glUniform1f(loc, OpenGL::ToolWindow::SpecularStrength);

		//Specular Color
		//loc = glGetUniformLocation(m_shaderDiffuse.GetProgramID(), "light[0].specularColor");
		//glUniform3f(
			//loc,
		glm::vec4 specular = {
			OpenGL::ToolWindow::RenderRedChannel,
			OpenGL::ToolWindow::RenderGreenChannel,
			OpenGL::ToolWindow::RenderBlueChannel,
			OpenGL::ToolWindow::SpecularStrength
		};
		

#pragma endregion ToolWindow

		//Box
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView(), specular);
		}
		//Light
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Fomt
		//f.RenderText(to_string(OpenGL::ToolWindow::SpecularStrength), 10, 500, 0.5f, {1.0f, 1.0f, 0.0f});
		f.RenderText("The cake is a lie", 2000, 1000, 0.5f, { 1.0f, 0.0f, 0.0f });
		f.RenderText("This is a teapot", 500, 100, 0.5f, { 1.0f, 1.0f, 1.0f });

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

	System::Windows::Forms::Application::ExitThread();
}