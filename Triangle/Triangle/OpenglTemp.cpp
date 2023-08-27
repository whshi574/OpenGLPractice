#include "Base.h"
#include "Shader.h"
#include "ffimage.h"

//About the window

int Window_width = 1200;
int Window_height = 600;

//Shader buffer
unsigned int VBO = 0;
unsigned int VAO = 0;
unsigned int EBO = 0;
unsigned int _texture = 0;

//Shader program
Shader _shader;
GLint FragColorLoc;

//Now program time
float NowTime = glfwGetTime();

//Texture image Data
ffImage* _pimage;

//Camera set up
glm::mat4 matrixProj = glm::mat4(1.0f);
glm::vec3 cameraPosition(0.0f, 0.0f, 3.0f);  // 相机位置
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);   // 目标位置
glm::vec3 upVector(0.0f, 1.0f, 0.0f);       // 上向量
glm::mat4 matrixView = glm::lookAt(cameraPosition, cameraTarget, upVector);

//Model matrix
glm::mat4 matrixModel = glm::mat4(1.0f);

//Model Location Vertices
int const LocVectorsSize = 5;
glm::vec3 LocVectors[LocVectorsSize] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		
	}
}

void initMode() 
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




	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(sizeof(float) * 3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	glBindVertexArray(VAO);
	//glBindTexture(GL_TEXTURE_2D, _texture);
	_shader.start();

	matrixProj = glm::perspective(glm::radians(45.0f), static_cast<float>(Window_width / Window_height), 0.1f, 100.0f);

	_shader.SetMatrix("ViewMatrix", matrixView);
	_shader.SetMatrix("ProjMatrix", matrixProj);

	for (int i = 0; i < LocVectorsSize; i++)
	{
		matrixModel = glm::mat4(1.0f);

		//先旋转，在平移，虽然这里是先平移在旋转，但是glm库矩阵操作都是贴给右边，所以最后贴的是最先计算的
		matrixModel = glm::translate(matrixModel, LocVectors[i]);
		matrixModel = glm::rotate(matrixModel, (float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		_shader.SetMatrix("ModelMatrix", matrixModel);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	_shader.end();
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//Get Texture image
	_pimage = ffImage::readFromFile("Res/Grass.jpg");
	float Pic_Ratio = _pimage->GetPicRatio();

	//About the window
	int Window_height = 400;
	int Window_width = Pic_Ratio * Window_height;

	GLFWwindow* window = glfwCreateWindow(Window_width, Window_height, "OpenGL Core", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glViewport(0, 0, Window_width, Window_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	initTexture();
	initMode();
	_shader.initShader("vertexShader.glsl", "fragmentShader.glsl");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		processInput(window);

        /* Render here */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rend();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}