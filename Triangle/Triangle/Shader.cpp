#include "Shader.h"

Shader::~Shader()
{

}

void Shader::initShader(const char* _vertexPath, const char* _fragPath)
{
	std::string  _vertexCode("");
	std::string  _fragCode("");

	std::ifstream	_vShaderFile;
	std::ifstream	_fShaderFile;

	//����try catch����չ����
	_vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	_fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		_vShaderFile.open(_vertexPath);
		_fShaderFile.open(_fragPath);

		std::stringstream	_vShaderStream, _fShaderStream;
		_vShaderStream << _vShaderFile.rdbuf();
		_fShaderStream << _fShaderFile.rdbuf();

		_vShaderFile.close();
		_fShaderFile.close();

		_vertexCode = _vShaderStream.str();
		_fragCode = _fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::string  errStr = "ffShader constructor fail to read filePath";
		std::cout << errStr << std::endl;
		return;
	}

	const char* _vShaderStr = _vertexCode.c_str();
	const char* _fShaderStr = _fragCode.c_str();

	unsigned int	_vertexID = 0, _fragID = 0;
	char	_infoLog[512];
	int		_successFlag;

	//��������shader
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexID, 1, &_vShaderStr, NULL);
	glCompileShader(_vertexID);

	glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetShaderInfoLog(_vertexID, 512, NULL, _infoLog);
		std::string errStr(_infoLog);
		std::cout << errStr << std::endl;
	}

	//������ɫshader
	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragID, 1, &_fShaderStr, NULL);
	glCompileShader(_fragID);

	glGetShaderiv(_fragID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetShaderInfoLog(_fragID, 512, NULL, _infoLog);
		std::string errStr(_infoLog);
		std::cout << errStr << std::endl;
	}

	//����shader����
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, _vertexID);
	glAttachShader(m_shaderProgram, _fragID);
	glLinkProgram(m_shaderProgram);

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, _infoLog);
		std::string errStr(_infoLog);
		std::cout << errStr << std::endl;
	}
	glDeleteShader(_vertexID);
	glDeleteShader(_fragID);
}

void Shader::start()
{
	glUseProgram(m_shaderProgram);
}

void Shader::end()
{
	glUseProgram(0);
}

unsigned int Shader::GetId()
{
	return m_shaderProgram;
}

void Shader::SetMatrix(const GLchar* matrixName, glm::mat4 matrixData)
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, matrixName), 1, GL_FALSE, glm::value_ptr(matrixData));
}
