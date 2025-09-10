#include "Shader.h"

Shader::Shader() :
	m_programID(0),
	m_attrVertices(0),
	m_result(GL_FALSE),
	m_infoLogLength(0)
{
}

void Shader:: Cleanup() {
	glDeleteProgram(m_programID);
}

void Shader::LoadAttributes() {
	m_attrVertices = glGetAttribLocation(m_programID, "vertices"); // Get a handle for the vertex buffer
}

void Shader::EvaluateShader(int _infoLength, GLuint _id) {
	
	if (_infoLength > 0) {
		// Only fetch and report the info log if there is something to report
		std::vector<char> errorMessage(_infoLength + 1);
		glGetProgramInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(false, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type) {

	// Create the shader ID
	GLuint shaderID = glCreateShader(_type);

	// Read the shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in);
	M_ASSERT(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory ? Dont forget to read the FAQ !\n", _filePath));
	std::string line = "";
	while (getline(shaderStream, line))
		shaderCode += "\n" + line;
	shaderStream.close();

	//Compile the shader
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	// Check the shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, shaderID);

	//Attach the shader to the program
	glAttachShader(m_programID, shaderID);

	return shaderID;
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath) {

	// Create the shader program
	m_programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER); // Load and compile the vertex shader
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER); // Load and compile the fragment shader
	glLinkProgram(m_programID); // Link the program

	// Check the program
	glGetProgramiv(m_programID, GL_LINK_STATUS, &m_result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, m_programID);

	// Free resources
	glDetachShader(m_programID, vertexShaderID);
	glDetachShader(m_programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath) {
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}