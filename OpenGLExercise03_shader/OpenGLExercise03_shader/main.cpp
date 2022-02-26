#define GLEW_STATIC

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>


float vertices[] = {
	-0.5f, -0.5f, 0.0f,// 0
	 0.5f, -0.5f, 0.0f,// 1
	 0.0f,  0.5f, 0.0f,// 2
	 //0.5f, -0.5f, 0.0f,
	 //0.0f,  0.5f, 0.0f,
	 0.5f, 0.0f, 0.5f// 3
};

unsigned int indices[] = {
	0, 1, 2,
	2, 1, 3 
};



/*********** uniform ���÷� ***********/
const char* vertexShaderSource =
								"#version 330 core\n"
								"layout(location = 15) in vec3 aPos;\n"
								"void main() {\n"
								"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								"}";

const char* fragmentShaderSource =
								"#version 330 core\n"
								"uniform vec4 ourColor;\n"
								"out vec4 FragColor;\n"
								"void main() {\n"
								"		FragColor = ourColor;}\n";

void processInput(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);



	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW failed." << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);


	/****************VBO��VAO��EBO****************/
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO ������ʽ����VAO���߼����÷������ظ����� VBOԪ��
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/****************Shader Program****************/
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/**************** ���Ͷ������� ****************/
	// �������Ա�š�����һ�顢���͡���һ������һ��Ŀ�ȡ���ʼƫ����
	// OpenGLȷ��������16������4�����Ķ������Կ��ã�0-15��
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);

	// ��ЩӲ�������������Ķ������ԣ�����Բ�ѯGL_MAX_VERTEX_ATTRIBS����ȡ��������ޣ�
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	/**************** render loop ****************/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//ͨ��cpuʱ�� ������ gpu�ϵ�fragmentColor
		
		glUseProgram(shaderProgram);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");//�ҵ� gpu shader Program �� Uniform ourColor λ��
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);//���� gpu shader Program �� Uniform ourColor ֵ

		//glDrawArrays(GL_TRIANGLES, 0, 6);//VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//EBO

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		printf("���� ESC : \n");
		glfwSetWindowShouldClose(window, true);
	}
}