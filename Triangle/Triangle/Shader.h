#pragma once
#include "Base.h"


class Shader
{
private:
	unsigned int m_shaderProgram;

public:
	Shader() {
		m_shaderProgram = 0;
	}

	~Shader();

	void initShader(const char* _vertexPath, const char* _fragPath);

	void start();

	void end();

	/*Get m_shaderProgram of the shader program*/
	unsigned int GetId();

	void SetMatrix(const GLchar* matrixName, glm::mat4 matrixData);

};