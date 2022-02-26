坐标系统 

z-buffer  深度缓冲

	//开启 z-buffer 深度缓冲
	glEnable(GL_DEPTH_TEST);

	while
		//清除 z-buffer 深度缓冲信息
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);