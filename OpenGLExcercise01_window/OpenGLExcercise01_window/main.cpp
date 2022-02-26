#define GLEW_STATIC

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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


	// render loop
	// 为了不让程序停止，直到窗口被设置为可以被关闭
	while (!glfwWindowShouldClose(window)) 
	{
		//清屏颜色，执行清屏
		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 基于双缓冲绘图
		// 把 back buffer 切换到 front buffer 
		glfwSwapBuffers(window);

		// 获取事件（比如按键）
		glfwPollEvents();

		// 处理 window 输入事件
		processInput(window);
	}

	return 0;
}

void processInput(GLFWwindow * window) {
	//ESCAPE : ESC
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{ 
		printf("按下 ESC : \n");
		//设置窗口可以被关闭
		glfwSetWindowShouldClose(window, true);
	}
}