#define GLEW_STATIC

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window);

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//��ʾ�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//��ʾ���ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//ǰ��������


	//����һ������ Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//ͨ���ô��ڴ��������ĺ͵�ǰ���̰߳󶨣�ÿ���߳�ͬһʱ��ֻ��ӵ��һ��������
	glfwMakeContextCurrent(window);

	// Init GLEW
	// ��Щ�Կ���������������ȷ������֧�ֵ���չ��Ϣ������GLEW������ȷ��ȡĳЩ��������ڵ�ַ����Ҫ glewExperimental = true; �� glewInit();
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW failed." << std::endl;
		glfwTerminate();
		return -1;
	}
	
	// OpenGL ��Ⱦ���ڵĴ�С�����ǽ�������Ϊ���� GLFW �Ĵ��ڴ�С
	glViewport(0, 0, 800, 600);


	// render loop
	// Ϊ�˲��ó���ֹͣ��ֱ�����ڱ�����Ϊ���Ա��ر�
	while (!glfwWindowShouldClose(window)) 
	{
		//������ɫ��ִ������
		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ����˫�����ͼ
		// �� back buffer �л��� front buffer 
		glfwSwapBuffers(window);

		// ��ȡ�¼������簴����
		glfwPollEvents();

		// ���� window �����¼�
		processInput(window);
	}

	return 0;
}

void processInput(GLFWwindow * window) {
	//ESCAPE : ESC
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{ 
		printf("���� ESC : \n");
		//���ô��ڿ��Ա��ر�
		glfwSetWindowShouldClose(window, true);
	}
}