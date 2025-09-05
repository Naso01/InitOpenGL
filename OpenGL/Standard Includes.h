#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

//std::vector
#include <vector>

//Windows Specific
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
		if(!(_cond)) {OutputDebugStringA(_msg); std::abort(); glfwTerminate();}
#endif //!_WIN32

//OpenGL/Helper Headers
#include <GL/glew.h>	// Include GLEW
#include <GLFW/glfw3.h>	// Include GLFW
#include <glm/glm.hpp>	// Include GLM

#include "Singleton.h"

using namespace std;

#endif // !STANDARD_INCLUDES_H
