#include "Camera.h"

Camera::Camera() {
	m_projection = glm::mat4();
	m_view = glm::mat4();
	m_position = { };
	m_lookAt = glm::vec3();
	m_lookAt = glm::vec3();
	m_angle = 0;
}

Camera::Camera(Resolution _screenResolution) {

	m_position = { 10, 10, 10};
	m_lookAt	= { 0, 0, 0 };
	m_rotation	= { 0, 0, 0 };
	m_angle = 0;

	//Projection matrix: 45 degrees Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	m_projection = glm::perspective(glm::radians(45.0f), // Field of View
		(float)_screenResolution.width / (float)_screenResolution.height, // Aspect Ratio
		0.1f,	 // Near clipping plane
		1000.0f); // Far clipping plane

	//Or for an ortho camera
	//m_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

	//Camera matrix
	m_view = glm::lookAt(
		m_position, // Camera is at (0,0,0), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
}

Camera::~Camera() { }

void Camera::Rotate() {
	// https://gamedev.stackexchange.com/questions/9607/moving-an-object-in-a-circular-path
	m_angle += 0.01f;
	m_lookAt.x = cos(glm::radians(m_angle)) * 50;
	m_lookAt.z = sin(glm::radians(m_angle)) * 50;

	//Camera matrix
	m_view = glm::lookAt(
		m_position,			// Camera is at (0,0,0), in World Space
		m_lookAt,		
		glm::vec3(0, 1, 0)	// Head is up (set to 0,-1,0 to look upside-down)
	);
}