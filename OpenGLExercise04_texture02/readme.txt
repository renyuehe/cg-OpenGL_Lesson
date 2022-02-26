
	/************************* 贴图 *************************/
	//openGL默认y轴是反的,该语句可以对y轴进行一次颠倒
	stbi_set_flip_vertically_on_load(true);

	
	/************************* 多张贴图 *************************/
	//TexBufferA
	glActiveTexture(GL_TEXTURE0);//激活 texture 位置0
	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);//生成贴图buffer（gpu）
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//绑定贴图buffer（gpu）
	//加载图像数据
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//向当前 gpu上 激活的 texBuffer 灌数据
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
	glActiveTexture(GL_TEXTURE3);//激活 texture 位置3
	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);//生成贴图buffer（gpu）
	glBindTexture(GL_TEXTURE_2D, TexBufferB);//绑定贴图buffer（gpu）
	//加载图像数据
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);//加载图像数据
	if (data2)
	{
		//向当前 gpu上 激活的 texBuffer 灌数据
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//Mipmap（纹理金字塔）
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load TexBufferB" << std::endl;
		return -1;
	}
	stbi_image_free(data2);