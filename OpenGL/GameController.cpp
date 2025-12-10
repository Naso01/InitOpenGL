#include "GameController.h"
#include "WindowController.h"
#include <glm/gtc/random.hpp>
#include "glm/gtx/string_cast.hpp"
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
	glm::vec3 lightPosition = { 0.0f, 0.0f, 5.0f };
	
	Mesh m = CreateMesh(m_shaderColor, "sphere.obj", { 0.01f, 0.01f, 0.01f }, 
		lightPosition);
	m.SetColor({1.0f, 1.0f , 1.0f });
	Mesh::Lights.push_back(m);

	glm::vec3 fighterScale = { 0.004f, 0.004f, 0.004f };
	glm::vec3 fighterPosition = { 0.0f, 0.0f, 0.0f };

	Mesh fighterjet = CreateMesh(m_shaderDiffuse, "fighter.obj", fighterScale,
		fighterPosition);
	fighterjet.SetCameraPosition(m_camera.GetPosition());
	m_meshes.push_back(fighterjet);

	Mesh fish = CreateMesh(m_shaderDiffuse, "fish.obj", { 0.1f, 0.1f, 0.1f },
														{ 0.0f, 0.0f, 0.0f });
	fish.SetCameraPosition(m_camera.GetPosition());
	fish.SetRotation({ 0.0f, 180.0f, 0.0f });
	m_meshes.push_back(fish);

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
	bool waterScene = false;
	do {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen - Clear depth buffer every frame

		mouseMovement = m_inputController.GetMovementVector();

		if (OpenGL::ToolWindow::MoveLight || OpenGL::ToolWindow::TransformEnabled) {

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
			//Reset Light Position
			if (OpenGL::ToolWindow::ResetLightPosition) {
		
				for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
					Mesh::Lights[count].SetPosition(lightPosition);
				}
				OpenGL::ToolWindow::ResetLightPosition = false;
			}
#pragma endregion Light Settings

#pragma region Transform
			if (OpenGL::ToolWindow::TransformEnabled) {

				if (OpenGL::ToolWindow::ResetTransform) {

					m_meshes[0].SetPosition(fighterPosition);
					m_meshes[0].SetRotation(glm::vec3{ 45.0f ,0.0f, 0.0f });
					m_meshes[0].SetScale(fighterScale);

					OpenGL::ToolWindow::ResetTransform = false;
				}
				if (OpenGL::ToolWindow::TranslateEnabled) {
					glm::vec3 currentPosition = m_meshes[0].GetPosition();
					m_meshes[0].SetPosition(currentPosition + mouseMovement);
				
				}
				if (OpenGL::ToolWindow::RotateEnabled) {
					glm::vec3 currentRotation = m_meshes[0].GetRotation();
					// more intuitive rotation {y, x , z}
					m_meshes[0].SetRotation(currentRotation + (glm::vec3{ mouseMovement.y, mouseMovement.x, mouseMovement.z } *10.0f));
				}
				if (OpenGL::ToolWindow::ScaleEnabled) {
					glm::vec3 currentScale = m_meshes[0].GetScale();
					m_meshes[0].SetScale(currentScale + mouseMovement * 0.001f);
				}	
			}
			else { //rotate on the x axis
					glm::vec3 currentRotation = m_meshes[0].GetRotation();
					m_meshes[0].SetRotation(currentRotation + glm::vec3{ 0.01f, 0.0f, 0.0f });
			}
		
#pragma endregion Transform 

			m_postProcessor.Start();
			//fighter jet
			m_meshes[0].Render(m_camera.GetProjection() * m_camera.GetView());

			f.RenderText("Fighter Position:" + glm::to_string(m_meshes[0].GetPosition()), 100, 200, 0.5f, { 1.0f, 1.0f, 0.0f });
			f.RenderText("Fighter Rotation:" + glm::to_string(m_meshes[0].GetRotation()), 100, 225, 0.5f, { 1.0f, 1.0f, 0.0f });
			f.RenderText("Fighter Scale:" + glm::to_string(m_meshes[0].GetScale()), 100, 250, 0.5f, { 1.0f, 1.0f, 0.0f });

		}
		else if (OpenGL::ToolWindow::WaterSceneEnabled) {
#pragma region Water Scene
			m_postProcessor.Start();
			//move light away from camera view
			for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
				Mesh::Lights[count].SetPosition(glm::vec3{0.5f, 1.0f, 11.0f});
			}

			//Fish
			m_meshes[1].Render(m_camera.GetProjection()* m_camera.GetView());
			f.RenderText("Fish Position:" + glm::to_string(m_meshes[1].GetPosition()), 100, 200, 0.5f, { 1.0f, 1.0f, 0.0f });
			f.RenderText("Fish Rotation:" + glm::to_string(m_meshes[1].GetRotation()), 100, 225, 0.5f, { 1.0f, 1.0f, 0.0f });
			f.RenderText("Fish Scale:" + glm::to_string(m_meshes[1].GetScale()), 100, 250, 0.5f, { 1.0f, 1.0f, 0.0f });
#pragma endregion Water Scene
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


		//Font
		System::Drawing::Point mousePos = OpenGL::ToolWindow::MousePosition;
		
		f.RenderText(fpsS, 100, 100, 0.5f, { 1.0f, 1.0f, 0.0f });
		f.RenderText("Mouse Pos: " + to_string(mousePos.X) + "   " + to_string(mousePos.Y), 100, 125, 0.5f, {1.0f, 1.0f, 0.0f});

		string leftMouseButtonState = (glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) ? "Down" : "Up";
		f.RenderText("Left Mouse Button:" + leftMouseButtonState, 100, 150, 0.5f, { 1.0f, 1.0f, 0.0f });
		string middleMouseButtonState = (glfwGetMouseButton(WindowController::GetInstance().GetWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) ? "Down" : "Up";
		f.RenderText("Middle Mouse Button:" + middleMouseButtonState, 100, 175, 0.5f, { 1.0f, 1.0f, 0.0f });
		
		//if(OpenGL::ToolWindow::WireframeEnabled)
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		m_postProcessor.End();
		
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