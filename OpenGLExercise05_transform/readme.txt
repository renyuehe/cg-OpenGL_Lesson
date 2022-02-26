		/*************** 变换 ***************/
		float valuesin = sin((float)glfwGetTime());
		float valuecos = cos((float)glfwGetTime());
		glm::mat4 trans;//变换矩阵
		trans = glm::translate(trans, glm::vec3(valuesin, valuecos, 0));//位移
		trans = glm::scale(trans, glm::vec3(1.0 + valuesin, 1.0 + valuesin, 1.0 + valuesin));//缩放
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//旋转
		//变换矩阵丢给GPU的vertexShader做运算
		glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));