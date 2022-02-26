着色器 

	/**************** 解释顶点属性 ****************/
	// 顶点属性编号、几个一组、类型、归一化？、一组的跨度、起始偏移量
	// OpenGL确保至少有16个包含4分量的顶点属性可用（0-15）
	//位置属性
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);
	//颜色属性
	glVertexAttribPointer(14, 3, GL_FLOAT, 