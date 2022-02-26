https://learnopengl-cn.github.io/

环境配置 ############################################################
1、下载GLFW（32位）：https://www.glfw.org/ 
2、GLEW（帮你依照当下的硬件接上底层的驱动）（32位）：http://glew.sourceforge.net/

3、vs包含 opengl32.lib、glfw3.lib、glew32s.lib


窗口 ############################################################

三角形 ############################################################

着色器 shader（GLSL） ############################################################

#version version_number
in type in_variable_name;
in type in_variable_name;
out type out_variable_name;
uniform type uniform_name;
int main()
{
  // 处理输入并进行一些图形操作
  ...
  // 输出处理过的结果到输出变量
  out_variable_name = weird_stuff_we_processed;
}

#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

纹理

变换

坐标系统

摄像机