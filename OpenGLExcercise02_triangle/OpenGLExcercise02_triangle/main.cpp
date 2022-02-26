#define GLEW_STATIC

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//第一个三角形（正面）（逆时针正绘制）
//第二个三角形（背面）（顺时针绘制）
float vertices[] = {
	-0.5f, -0.5f, 0.0f,// 0
	 0.5f, -0.5f, 0.0f,// 1
	 0.0f,  0.5f, 0.0f,// 2
	 //0.5f, -0.5f, 0.0f,
	 //0.0f,  0.5f, 0.0f,
	 0.5f, 0.0f, 0.5f// 3
};

unsigned int indices[] = {
	0, 1, 2, //第一个三角形
	2, 1, 3  //第二个三角形
};

const char* vertexShaderSource =
								"#version 330 core\n"
								"layout(location = 15) in vec3 aPos;\n"
								"void main() {\n"
								"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";

const char* fragmentShaderSource =
								"#version 330 core\n"
								"out vec4 FragColor;\n"
								"void main() {\n"
								"		FragColor = vec4(1.0f, 0.5f, 1.0f, 1.0f);}\n";

//const char* vertexShaderSource =
//								"#version 330 core\n"
//								"layout(location = 15) in vec3 aPos;\n"
//								"out vec4 vertexColor;\n"
//								"void main() {\n"
//								"		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//								"		vertexColor = vec4(1.0, 0.5, 0.0, 1.0);\n"
//								"}";
//
//const char* fragmentShaderSource =
//								"#version 330 core\n"
//								"in vec4 vertexColor;\n"
//								"out vec4 FragColor;\n"
//								"void main() {\n"
//								"		FragColor = vertexColor;}\n";

void processInput(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//提示：主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//提示：次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//前向相容性


	//创造一个窗口 Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//通过该窗口创建上下文和当前的线程绑定，每个线程同一时刻只能拥有一个上下文
	glfwMakeContextCurrent(window);

	// Init GLEW
	// 有些显卡的驱动程序不能正确给出所支持的扩展信息，导致GLEW不能正确获取某些函数的入口地址，需要 glewExperimental = true; 和 glewInit();
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW failed." << std::endl;
		glfwTerminate();
		return -1;
	}

	// OpenGL 渲染窗口的大小，我们将其设置为等于 GLFW 的窗口大小
	glViewport(0, 0, 800, 600);

	//面剔除功能（逆时针绘制的三角形表示正面，顺时针表示背面）
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glCullFace(GL_BACK);

	//线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//填充模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/****************OpenGL是一个巨大的有限状态机，在同一时刻只有一个VBO、VAO、EBO存在于当前的 Context 中****************/
	// VAO 顶点数组对象（Vertex Array Object） 
	// 是 VBO 的属性（...）索引，不同的 VAO 可以组合成不同的东西
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//创建 VAO
	glBindVertexArray(VAO);// 绑定VAO

	// VBO 顶点缓冲对象（Vertex Buffer Object）
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO 索引形式，比VAO更高级的用法，可重复利用 VBO元素
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/****************顶点着色器、片段着色器、GLSL着色器语言、Shader Program****************/
	// 顶点着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/**************** 解释顶点属性 ****************/
	// 顶点属性编号、几个一组、类型、归一化？、一组的跨度、起始偏移量
	// OpenGL确保至少有16个包含4分量的顶点属性可用（0-15）
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);

	// 有些硬件或许允许更多的顶点属性，你可以查询GL_MAX_VERTEX_ATTRIBS来获取具体的上限：
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	/**************** render loop ****************/
	// 为了不让程序停止，直到窗口被设置为可以被关闭
	while (!glfwWindowShouldClose(window))
	{
		// 处理 window 输入事件
		processInput(window);

		//清屏颜色，执行清屏
		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用 shaderProgram
		glUseProgram(shaderProgram);
		//glDrawArrays(GL_TRIANGLES, 0, 6);//VAO用法
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//EBO用法

		// 基于双缓冲绘图
		// 把 back buffer 切换到 front buffer 
		glfwSwapBuffers(window);

		// 获取事件（比如按键）
		glfwPollEvents();
	}
	return 0;
}

void processInput(GLFWwindow* window) {
	//ESCAPE : ESC
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		printf("按下 ESC : \n");
		//设置窗口可以被关闭
		glfwSetWindowShouldClose(window, true);
	}
}