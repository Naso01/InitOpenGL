#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"
#include "ToolWindow.h"

bool GameController::m_leftMouseHeld = false;
GameController* GameController::Active = nullptr;

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

void MouseClickCallback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT) {

		if (action == GLFW_PRESS)
			GameController::m_leftMouseHeld = true;

		if (action == GLFW_RELEASE)
			GameController::m_leftMouseHeld = false;
	}
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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());
}



//Create Mesh Wrapper Method
Mesh GameController::CreateMesh(Shader* _shader, string _obj,  glm::vec3 _scale, glm::vec3 _position, int _instanceCount) {

	Mesh m = Mesh();
	m.Create(_shader, "../Assets/Models/" + _obj, _instanceCount);
	m.SetScale(_scale);
	m.SetPosition(_position);

	return m;
}

void GameController::MoveMesh(GLFWwindow* _window)
{
	if (!m_leftMouseHeld || Mesh::Lights.empty() || m_meshes.empty())
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
		glm::vec3 pos = m_meshes[0].GetPosition();
		pos.x += direction.x * speed;
		pos.y += direction.y * speed;

		SetMeshPosition(pos);
	}
	else {
		glm::vec3 pos = Mesh::Lights[0].GetPosition();
		pos.x += direction.x * speed;
		pos.y += direction.y * speed;

		SetLightPosition(pos);
	}
}

void GameController::RenderToolWindow() {
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	System::Windows::Forms::Application::Run(window);
}

void GameController::SetLightPosition(glm::vec3 _pos) {

	Mesh::Lights[0].SetPosition(_pos);
}

void GameController::SetMeshPosition(glm::vec3 _pos) {

	m_meshes[0].SetPosition(_pos);
}

void GameController::SetColorByPosition(bool _ColorByPosition) {

	m_meshes[0].SetColorByPosition(_ColorByPosition);
}

void GameController::MoveCubesToSphere(bool _moveCubeToSphere) {

	for (unsigned int count = 0; count < m_meshes.size(); count++) {
		m_meshes[count].Cleanup();
	}
	m_meshes.clear();

	if (_moveCubeToSphere) {
		Mesh sphere = Mesh();
		sphere.Create(&m_shaderDiffuse, "../Assets/Models/sphere.obj");
		sphere.SetCameraPosition(m_camera.GetPosition());
		sphere.SetScale({ 0.02f, 0.02f, 0.02f });
		sphere.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_meshes.push_back(sphere);
	}
	else {
		Mesh teapot = Mesh();
		teapot.Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
		teapot.SetCameraPosition(m_camera.GetPosition());
		teapot.SetScale({ 0.02f, 0.02f, 0.02f });
		teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_meshes.push_back(teapot);
	}
}

void GameController::CreateCube() {
	glm::vec3 spawnPos = { glm::linearRand(0.0f, 2.0f),
		glm::linearRand(0.0f, 2.0f),
		glm::linearRand(0.0f, 2.0f) };

	// Add cube
	m_meshes.emplace_back();
	auto& cube = m_meshes.back();

	cube.Create(&m_shaderDiffuse, "../Assets/Models/cube.obj");
	cube.SetCameraPosition(m_camera.GetPosition());
	cube.SetScale({ 0.02f, 0.02f, 0.02f });
	cube.SetPosition(spawnPos);
}

void GameController::UpdateCubeMovement(float _deltaTime)
{
	glm::vec3 spherePos = m_meshes[0].GetPosition();

	for (auto& cube : m_meshes)
	{
		glm::vec3 cubePos = cube.GetPosition();

		glm::vec3 direction = glm::normalize(spherePos - cubePos);

		float speed = 0.025f;

		cubePos += direction * speed * _deltaTime;
		cube.SetPosition(cubePos);
	}
}

void GameController::RunGame() {
	
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow();

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
	Mesh m = CreateMesh(&m_shaderColor, "sphere.obj", { 0.005f, 0.005f, 0.005f },
												 { 0.0f,  0.0f,  0.1f });
	m.SetColor({1.0f, 1.0f , 1.0f });
	Mesh::Lights.push_back(m);

	Mesh teapot = CreateMesh(&m_shaderDiffuse, "teapot.obj",	{ 0.02f, 0.02f, 0.02f },
														{0.0f, 0.0f, 0.0f});
	teapot.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(teapot);

#pragma endregion CreateMeshes

#pragma region CreateFonts

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 40);

#pragma endregion CreateFonts

	bool colorbyPosition = false;

#pragma region Render

	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";
	do {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen - Clear depth buffer every frame

		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0) {
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1.0f;
		}
		f.RenderText(fpsS, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });


#pragma region ToolWindow
		glm::vec4 specularData = {
			OpenGL::ToolWindow::RenderRedChannel,
			OpenGL::ToolWindow::RenderGreenChannel,
			OpenGL::ToolWindow::RenderBlueChannel,
			OpenGL::ToolWindow::SpecularStrength
		};
#pragma endregion ToolWindow

		if (OpenGL::ToolWindow::ColorByPosition != colorbyPosition) {
			m_meshes[0].SetColorByPosition(OpenGL::ToolWindow::ColorByPosition);
			colorbyPosition = OpenGL::ToolWindow::ColorByPosition;
		}

		//Box
		for (unsigned int count = 0; count < m_meshes.size(); count++) {
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView(), specularData);
		}
		//Light
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Font
		

		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); // Swap the front and back buffers
		glfwPollEvents();

		MoveMesh(glfwWindow);

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
	m_shaderSkybox.Cleanup();

	System::Windows::Forms::Application::ExitThread();

#pragma endregion Cleanup
}