#define GLEW_STATIC

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//��һ�������Σ����棩����ʱ�������ƣ�
//�ڶ��������Σ����棩��˳ʱ����ƣ�
float vertices[] = {
	-0.5f, -0.5f, 0.0f,// 0
	 0.5f, -0.5f, 0.0f,// 1
	 0.0f,  0.5f, 0.0f,// 2
	 //0.5f, -0.5f, 0.0f,
	 //0.0f,  0.5f, 0.0f,
	 0.5f, 0.0f, 0.5f// 3
};

unsigned int indices[] = {
	0, 1, 2, //��һ��������
	2, 1, 3  //�ڶ���������
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

	//���޳����ܣ���ʱ����Ƶ������α�ʾ���棬˳ʱ���ʾ���棩
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glCullFace(GL_BACK);

	//�߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//���ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/****************OpenGL��һ���޴������״̬������ͬһʱ��ֻ��һ��VBO��VAO��EBO�����ڵ�ǰ�� Context ��****************/
	// VAO �����������Vertex Array Object�� 
	// �� VBO �����ԣ�...����������ͬ�� VAO ������ϳɲ�ͬ�Ķ���
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);//���� VAO
	glBindVertexArray(VAO);// ��VAO

	// VBO ���㻺�����Vertex Buffer Object��
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO ������ʽ����VAO���߼����÷������ظ����� VBOԪ��
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/****************������ɫ����Ƭ����ɫ����GLSL��ɫ�����ԡ�Shader Program****************/
	// ������ɫ��
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
	// Ϊ�˲��ó���ֹͣ��ֱ�����ڱ�����Ϊ���Ա��ر�
	while (!glfwWindowShouldClose(window))
	{
		// ���� window �����¼�
		processInput(window);

		//������ɫ��ִ������
		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//ʹ�� shaderProgram
		glUseProgram(shaderProgram);
		//glDrawArrays(GL_TRIANGLES, 0, 6);//VAO�÷�
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//EBO�÷�

		// ����˫�����ͼ
		// �� back buffer �л��� front buffer 
		glfwSwapBuffers(window);

		// ��ȡ�¼������簴����
		glfwPollEvents();
	}
	return 0;
}

void processInput(GLFWwindow* window) {
	//ESCAPE : ESC
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		printf("���� ESC : \n");
		//���ô��ڿ��Ա��ر�
		glfwSetWindowShouldClose(window, true);
	}
}