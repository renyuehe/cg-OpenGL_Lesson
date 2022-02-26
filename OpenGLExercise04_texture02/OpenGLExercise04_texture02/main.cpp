#include <iostream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertices[] = {
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};

unsigned int indices[] = {
	0, 1, 2,
	0, 2, 3
};

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

	/* VAO�� VBO�� EBO�� TexBufferA */
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

	/************************* ��ͼ *************************/
	//openGLĬ��y���Ƿ���,�������Զ�y�����һ�εߵ�
	stbi_set_flip_vertically_on_load(true);
	
	int width, height, nrChannels;
	
	//TexBufferA
	glActiveTexture(GL_TEXTURE0);//���� texture λ��0
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);//������ͼbuffer��gpu��
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//����ͼbuffer��gpu��
	//����ͼ������
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//��ǰ gpu�� ����� texBuffer ������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load TexBufferA" << std::endl;
		return -1;
	}
	stbi_image_free(data);

	//TexBufferB
	glActiveTexture(GL_TEXTURE3);//���� texture λ��3
	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);//������ͼbuffer��gpu��
	glBindTexture(GL_TEXTURE_2D, TexBufferB);//����ͼbuffer��gpu��
	//����ͼ������
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);//����ͼ������
	if (data2)
	{
		//��ǰ gpu�� ����� texBuffer ������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//Mipmap�������������
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load TexBufferB" << std::endl;
		return -1;
	}
	stbi_image_free(data2);



	/************** ���Ͷ������� **************/
	//λ������
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);
	//��ɫ����
	glVertexAttribPointer(14, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(14);
	//uv����
	glVertexAttribPointer(13, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(13);

	/*************** ��ɫ���� ****************/
	Shader* testShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.6f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		testShader->use();// use program
		
		glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 3);

		//glDrawArrays(GL_TRIANGLES, 0, 6);//VAO�÷�
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//VBO�÷�

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