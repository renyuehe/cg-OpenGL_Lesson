#define GLEW_STATIC

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>


float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// 0
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// 1
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// 2
	 0.5f, 0.0f, 0.5f, 0.3f, 0.5f, 0.7f// 3
};

unsigned int indices[] = {
	0, 1, 2,
	2, 1, 3 
};


const char* vertexShaderSource =
								"#version 330 core\n"
								"layout(location = 15) in vec3 aPos;\n"
								"layout(location = 14) in vec3 aColor;\n"
								"out vec4 vertexColor;\n"
								"void main() {\n"
								"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								"		vertexColor = vec4(aColor.xyz, 1.0);\n"
								"}";

const char* fragmentShaderSource =
								"#version 330 core\n"
								"in vec4 vertexColor;\n"
								"out vec4 FragColor;\n"
								"void main() {\n"
								"		FragColor = vertexColor;"
								"}\n";

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


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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

	/**************** 解释顶点属性 ****************/
	// 顶点属性编号、几个一组、类型、归一化？、一组的跨度、起始偏移量
	// OpenGL确保至少有16个包含4分量的顶点属性可用（0-15）
	//位置属性
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);
	//颜色属性
	glVertexAttribPointer(14, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(14);


	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram);

		//glDrawArrays(GL_TRIANGLES, 0, 6);//VAO用法
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//VBO用法

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		printf("按下 ESC : \n");
		glfwSetWindowShouldClose(window, true);
	}
}