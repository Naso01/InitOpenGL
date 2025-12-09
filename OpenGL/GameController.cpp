#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "Fonts.h"
#include "ToolWindow.h"

GameController::GameController() {
	
	//m_meshes.clear();
	m_skybox = { };
	m_camera = { };
	m_postProcessor = { };

	//Shader
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_shaderFont = { };
	m_shaderPost = { };
	//m_shaderSkybox = { };
}

void GameController::Initialize() {

	// Create a default window
	GLFWwindow* glfwWindow = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 1); // Black background
	glEnable(GL_DEPTH_TEST);
	//Face Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);	//Configure global OpenGl state

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	srand((unsigned int)time(0));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a default perspective camera
	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.width, r.height);
	m_camera = Camera(r);
}

//Create Mesh Wrapper Method
Mesh GameController::CreateMesh(Shader _shader, string _obj,  glm::vec3 _scale, glm::vec3 _position, int _instanceCount) {

	Mesh m = Mesh();
	m.Create(&_shader, "../Assets/Models/" + _obj, _instanceCount);
	m.SetScale(_scale);
	m.SetPosition(_position);

	return m;
}

void GameController::RenderToolWindow() {
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	System::Windows::Forms::Application::Run(window);
}

void GameController::RunGame() {
	
	//Create and compile our GLSL program from the shaders
#pragma region SetupShaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	m_shaderPost = Shader();
	m_shaderPost.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");

	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
#pragma endregion SetupShaders

	//Create meshes
#pragma region CreateMeshes
	Mesh m = CreateMesh(m_shaderColor, "sphere.obj", { 0.01f, 0.01f, 0.01f }, 
												 { 0.0f,  0.0f,  5.0f });
	m.SetColor({1.0f, 1.0f , 1.0f });
	Mesh::Lights.push_back(m);

	Mesh fighterjet = CreateMesh(m_shaderDiffuse, "fighter.obj",	{0.005f, 0.005f, 0.005f },
														{0.0f, 0.0f, 0.0f});
	fighterjet.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(fighterjet);

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

	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPost);

#pragma region ToolWindow
		System::Threading::Thread^ uiThread =
		gcnew System::Threading::Thread(
			gcnew System::Threading::ThreadStart(&GameController::RenderToolWindow)
		);

	uiThread->SetApartmentState(System::Threading::ApartmentState::STA);
	uiThread->IsBackground = true;
	uiThread->Start();
#pragma endregion ToolWindow

#pragma region Render

	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";

	unsigned short specularStrength = 0;
	float redValue = 1.0f;
	float greenValue = 1.0f;
	float blueValue = 1.0f;
	glm::vec3 specularColor = {
		OpenGL::ToolWindow::RenderRedChannel,
		OpenGL::ToolWindow::RenderGreenChannel,
		OpenGL::ToolWindow::RenderBlueChannel
	};

	glm::vec3 newSpecularColor;
	glm::vec3 mouseMovement;

	do {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen - Clear depth buffer every frame

		mouseMovement = m_inputController.GetMovementVector();

#pragma region Light Settings
		if(OpenGL::ToolWindow::MoveLight){
			newSpecularColor = {
				OpenGL::ToolWindow::RenderRedChannel,
				OpenGL::ToolWindow::RenderGreenChannel,
				OpenGL::ToolWindow::RenderBlueChannel
			};
			//if render color channels changed
			if (specularColor != newSpecularColor)
			{
				for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
					Mesh::Lights[count].SetSpecularColor(newSpecularColor);
				}
				specularColor = newSpecularColor;
			}

			for (unsigned int count = 0; count < m_meshes.size(); count++) {
				m_meshes[count].SetSpecularStrength(OpenGL::ToolWindow::SpecularStrength);
			}

			if(mouseMovement != glm::vec3(0.0f))
			{
				for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
					glm::vec3 currentPosition = Mesh::Lights[count].GetPosition();
					Mesh::Lights[count].SetPosition(currentPosition + mouseMovement);
				}
			}
		}
#pragma endregion Light Settings


		m_postProcessor.Start();

		//Meshes
		for (unsigned int count = 0; count < m_meshes.size(); count++) {
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//Light
		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		//Timer / FPS
		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0) {
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime += 1.0f;
		}
		m_postProcessor.End();

		System::Drawing::Point mousePos = OpenGL::ToolWindow::MousePosition;

		string strMousePosition = "Mouse Pos: " + to_string(mousePos.X) + "   " + to_string(mousePos.Y);

		//Font
		f.RenderText(fpsS, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
		f.RenderText(strMousePosition, 100, 150, 0.5f, {1.0f, 1.0f, 0.0f});
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
	
	f.Cleanup();
	m_shaderFont.Cleanup();
	
	m_postProcessor.Cleanup();
	m_shaderPost.Cleanup();
	 
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup();

#pragma endregion Cleanup
}