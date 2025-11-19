#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"
#include "ToolWindow.h"

bool GameController::m_leftMouseHeld = false;
GameController* GameController::Active = nullptr;

GameController::GameController() {
	
	//m_meshBoxes.clear();	- Implemented by default by the compiler 
	//m_meshLights.clear();

	m_camera = { };

	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderLight = { };
	Active = this;
}

void GameController::Initialize() {

	// Create a default window
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glfwSetMouseButtonCallback(glfwWindow, MouseClickCallback);
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

void MouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
			GameController::m_leftMouseHeld = true;

		if (action == GLFW_RELEASE)
			GameController::m_leftMouseHeld = false;
	}
}

void GameController::MoveLight(GLFWwindow* _window)
{
	if (!m_leftMouseHeld || Mesh::Lights.empty() || m_meshBoxes.empty())
		return;

	double mouseX, mouseY;
	glfwGetCursorPos(_window, &mouseX, &mouseY);

	int width, height;
	glfwGetWindowSize(_window, &width, &height);

	float cx = float(mouseX - width * 0.5f);
	float cy = float(height * 0.5f - mouseY);

	// Safe normalization
	glm::vec2 direction(0.0f);
	if (cx != 0 || cy != 0)
		direction = glm::normalize(glm::vec2(cx, cy));

	float dist = glm::length(glm::vec2(cx, cy));
	float maxDist = glm::length(glm::vec2(width * 0.5f, height * 0.5f));
	float speedFactor = dist / maxDist;

	// If you have deltaTime available use this instead:
	//float speed = 2.0f * speedFactor * deltaTime;
	float speed = 0.001f * speedFactor;

	if (OpenGL::ToolWindow::ColorByPosition) {
		glm::vec3 pos = m_meshBoxes[0].GetPosition();
		pos.x += direction.x * speed;
		pos.y += direction.y * speed;

		m_meshBoxes[0].SetPosition(pos);
	}
	else {
		glm::vec3 pos = Mesh::Lights[0].GetPosition();
		pos.x += direction.x * speed;
		pos.y += direction.y * speed;

		SetMeshPosition(pos);
	}
}

void GameController::RenderToolWindow() {
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	System::Windows::Forms::Application::Run(window);
}

void GameController::SetMeshPosition(glm::vec3 _pos) {
	if (OpenGL::ToolWindow::ColorByPosition) {
		m_meshBoxes[0].SetPosition(_pos);
	}
	else {
		Mesh::Lights[0].SetPosition(_pos);
	}
	
}

void GameController::SetColorByPosition(bool _ColorByPosition) {

	m_meshBoxes[0].SetColorByPosition(_ColorByPosition);
}

void GameController::MoveCubesToSphere(bool _moveCubeToSphere) {
	
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
		m_meshBoxes[count].Cleanup();
	}
	m_meshBoxes.clear();

	if (_moveCubeToSphere) {
		Mesh sphere = Mesh();
		sphere.Create(&m_shaderDiffuse, "../Assets/Models/sphere.obj");
		sphere.SetCameraPosition(m_camera.GetPosition());
		sphere.SetScale({ 0.02f, 0.02f, 0.02f });
		sphere.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_meshBoxes.push_back(sphere);
	}
	else {
		Mesh teapot = Mesh();
		teapot.Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
		teapot.SetCameraPosition(m_camera.GetPosition());
		teapot.SetScale({ 0.02f, 0.02f, 0.02f });
		teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_meshBoxes.push_back(teapot);
	}
}

void GameController::CreateCube() {
	float distance = 0.5f;

	glm::vec3 spawnPos = ()

	// Add cube
	m_meshBoxes.emplace_back();
	auto& cube = m_meshBoxes.back();

	cube.Create(&m_shaderDiffuse, "../Assets/Models/cube.obj");
	cube.SetCameraPosition(m_camera.GetPosition());
	cube.SetScale({ 0.02f, 0.02f, 0.02f });
	cube.SetPosition(spawnPos);
}

void GameController::RunGame() {
	
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow();

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
	m.SetPosition({0.0f, 0.0f, 0.1f});
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

	bool colorbyPosition = false;

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


		if (OpenGL::ToolWindow::ColorByPosition != colorbyPosition) {
			m_meshBoxes[0].SetColorByPosition(OpenGL::ToolWindow::ColorByPosition);
			colorbyPosition = OpenGL::ToolWindow::ColorByPosition;
		}
		
		if (OpenGL::ToolWindow::MoveCubesToSphereMode)
		{
			if (m_windowController->IsLeftMouseDown())
			{
				CreateCubeAtClickPosition();
			}
		}

		//Box
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView(), specular);
		}
		//Light
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Font
		//f.RenderText("Light Pos: " + to_string(lightPos.x) + ", " + to_string(lightPos.y), 20, 20, 0.5f, { 1,1,0 });

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();
		
		MoveLight(glfwWindow);

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