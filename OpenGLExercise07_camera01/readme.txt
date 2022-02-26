

mvp中的 view
摄像机主要参数：pos、direct、up
		/******************** LookAt 矩阵 *********************/
		glm::mat4 viewMat;
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		//摄像机位置、摄像机target、up向量
		viewMat = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));