#include "Base.h"
#include "Shader.h"
#include "ffimage.h"
#include "Camera.h"

//About the window

int Window_width = 1200;
int Window_height = 600;

//Shader buffer
unsigned int VAO_Cube = 0;
unsigned int VAO_Sun = 0;

unsigned int _texture = 0;

//Shader program
Shader _shaderCube;
Shader _shaderSun;
GLint FragColorLoc;

//Now program time
float NowTime = glfwGetTime();

//Texture image Data
ffImage* _pimage;

//Camera set up
Camera _camera;
glm::mat4 matrixProj = glm::mat4(1.0f);
glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);  // 相机位置
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);   // 目标位置
glm::vec3 cameraUp(0.0f, 0.1f, 0.0f); //相机的向上向量


//Model matrix
glm::mat4 matrixModel = glm::mat4(1.0f);

//Model Location Vertices
int const LocVectorsSize = 5;
glm::vec3 LocVectors[LocVectorsSize] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(-1.8f, -2.0f, -1.3f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

//Light config
glm::vec3 LightPos = glm::vec3(2.5f, 1.4f, 2.2f);
glm::vec4 LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		_camera.Move(MOVEFORWARD);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		_camera.Move(MOVEBACK);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		_camera.Move(MOVELEFT);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		_camera.Move(MOVERIGHT);
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	_camera.onMouseMove(xpos, ypos);
}

unsigned int initMode()
{
	//Model Vertices
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int _VAO = 0;
	unsigned int _VBO = 0;

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return _VAO;
}

void initTexture() 
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pimage->getWidth(), _pimage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pimage->getData());

}

void rend() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBindTexture(GL_TEXTURE_2D, _texture);
	_shaderCube.start();

	glBindVertexArray(VAO_Cube);

	matrixProj = glm::perspective(glm::radians(45.0f), static_cast<float>(Window_width / Window_height), 0.1f, 100.0f);

	_shaderCube.SetMatrix("ViewMatrix", _camera.GetViewMatrix());
	_shaderCube.SetMatrix("ProjMatrix", matrixProj);

	_shaderCube.SetVecFour("LightColor", LightColor);

	matrixModel = glm::mat4(1.0f);
	matrixModel = glm::translate(matrixModel, LocVectors[0]);

	_shaderCube.SetMatrix("ModelMatrix", matrixModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	_shaderCube.end();

	
	_shaderSun.start();

	glBindVertexArray(VAO_Sun);

	matrixModel = glm::mat4(1.0f);
	matrixModel = glm::translate(matrixModel, LightPos);
	matrixModel = glm::rotate

	matrixProj = glm::perspective(glm::radians(45.0f), static_cast<float>(Window_width / Window_height), 0.1f, 100.0f);

	_shaderSun.SetMatrix("ViewMatrix", _camera.GetViewMatrix());
	_shaderSun.SetMatrix("ProjMatrix", matrixProj);

	_shaderSun.SetVecFour("LightColor", LightColor);

	_shaderSun.SetMatrix("ModelMatrix", matrixModel);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	_shaderSun.end();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Get Texture image
	_pimage = ffImage::readFromFile("../Triangle/Res/Grass.jpg");
	float Pic_Ratio = _pimage->GetPicRatio();

	//About the window
	int Window_height = 400;
	int Window_width = Pic_Ratio * Window_height;

	GLFWwindow* window = glfwCreateWindow(Window_width, Window_height, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create GLFW window, Create window again" << std::endl;
		return -1;
	}
	

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "" << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	glViewport(0, 0, Window_width, Window_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	_camera.LookAt(cameraPosition, cameraTarget - cameraPosition, cameraUp);

	initTexture();
	VAO_Cube = initMode();
	VAO_Sun = initMode();

	_shaderCube.initShader("vertexShader.glsl", "fragmentShader.glsl");
	_shaderSun.initShader("VertexSunShader.glsl", "FragSunShader.glsl");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		processInput(window);

        /* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		rend();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}