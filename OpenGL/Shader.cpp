#include "Shader.h"

Shader::Shader() :
	m_programID(0),
	m_attrVertices(0),
	m_attrColors(0),
	m_attrNormals(0),
	m_attrTexCoords(0),
	
	m_sampler1(0),
	m_sampler2(0),

	m_attrWVP(0),

	m_result(GL_FALSE),
	m_infoLogLength(0)
{ }


void Shader:: Cleanup() {
	glDeleteProgram(m_programID);
}

void Shader::SetVec3(const char* _name, glm::vec3 _value) {
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) {
		glUniform3fv(loc, 1, &_value[0]);
	}
}

void Shader::LoadAttributes() {
	m_attrVertices = glGetAttribLocation(m_programID, "vertices"); // Get a handle for the vertex buffer
	m_attrColors = glGetAttribLocation(m_programID, "colors"); //Get a handle for the colors buffer
	m_attrNormals = glGetAttribLocation(m_programID, "normals"); // Get a handle for the normals buffer
	m_attrTexCoords = glGetAttribLocation(m_programID, "texCoords"); // Get a handle for the texCoords buffer
	m_sampler1 = glGetUniformLocation(m_programID, "sampler1"); // Get a handle for texture sampler 1
	m_sampler2 = glGetUniformLocation(m_programID, "sampler2"); // Get a handle for texture sampler 1

	m_attrWVP = glGetUniformLocation(m_programID, "WVP"); // Get a handle for the WorldViewProjection matrix
}

void Shader::EvaluateShader(int _infoLength, GLuint _id) {
	
	if (_infoLength > 0) {
		// Only fetch and report the info log if there is something to report
		std::vector<char> errorMessage(_infoLength + 1);
		glGetProgramInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type) {

	GLuint shaderID = glCreateShader(_type); // Create the shader ID

	// Read the shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in);
	M_ASSERT(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory ? Dont forget to read the FAQ !\n", _filePath));
	std::string Line = "";
	while (getline(shaderStream, Line))
		shaderCode += "\n" + Line;
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