// ## 注意事项 ##
// 1. 对filesystem.h的修改：
//    #include "root_directory.h" - 原本的代码
//    const char* logl_root = "C:/LearnOpenGL-master"; // 设定根目录
// 2. 需要关闭工程的 C/C++ SDL检查 特性
// 3. 对工程连接SOIL.lib
// ## 注意事项 ##

//// I 库头 ////
#include <iostream>

// GLEW
// GLEW 能自动识别你的平台所支持的全部OpenGL高级扩展涵数
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
// OpenGL 窗口管理、分辨率切换、键盘、鼠标以及游戏手柄、定时器输入、线程创建等等。
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>

// Other includes
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>

//// II 函数原型 ////
void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mode);

//// III 全局变量 ////
const GLuint WIDTH = 800, HEIGHT = 600;

//// IV 主程序 ////
int main()
{
	std::cout << "进入GLFW环境, OpenGL版本：3.3。" << std::endl;
	// 1.0 初始化GLFW
	glfwInit();
	// 1.1 设定GLFW程序基本模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// 2.0 创建窗口对象
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
		"LearnOpenGL", nullptr, nullptr);
	// 2.1 将窗口加入openGL环境
	glfwMakeContextCurrent(window);

	// 使用自定义函数
	glfwSetKeyCallback(window, key_callback);

	// 3.0 初始化GLEW
	glewExperimental = GL_TRUE; // 使用现代化技术
	glewInit();

	// 4.0 设置视口
	glViewport(0, 0, WIDTH, HEIGHT);


	// 5.0 编写并编译着色器程序
	Shader ourShader("texture.vert", "texture.frag");


	// 6.0 设置顶点数据
	GLfloat vertices[] = {
		 // Positions         // Colors           // Texture Coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // 从0开始
		0, 1, 3, // 第一个三角面
		1, 2, 3  // 第二个三角面
	};

	// 6.1 创建数据对象
	GLuint VBO, VAO, EBO;		// 顶点缓存对象，顶点数组对象，索引缓存对象 
	glGenVertexArrays(1, &VAO);	// 生成缓存ID
	glGenBuffers(1, &VBO);		// 生成缓存ID
	glGenBuffers(1, &EBO);		// 生成缓存ID

	// 6.2 绑定数据对象
	// 处理VAO
	glBindVertexArray(VAO);

	// 处理VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 处理EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);

	// 6.3 解释顶点数据（数据的：位置、数位、格式，？，步长，偏移量）
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(
		GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(
		GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// 贴图纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(
		GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// 6.4 解绑 VAO
	glBindVertexArray(0);

	// 6.5 读取并创建贴图（之后会独立成类库）
	GLuint texture1;  // 新建纹理变量
	GLuint texture2;
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1); // 生成纹理的数量，然后将数据存储在GLuint数组中
	glBindTexture(GL_TEXTURE_2D, texture1); // 绑定 
											// 设置贴图参数(参数1：使用2D纹理，参数2：设置的轴，参数3：UV环绕的方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // 重复UV
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 读取，创建纹理并生成贴图
	int width, height;

	unsigned char* image = SOIL_load_image(FileSystem::getPath(
		"resources/textures/container.jpg").c_str(), &width, &height, 0,
		SOIL_LOAD_RGB);

	// 生成纹理
	// 参数1： 指定纹理目标（环境），任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响
	// 参数2： 为我们打算创建的纹理指定多级渐远纹理的层级，如果你希望单独手工设置每个多级渐远纹理的层级的话。这里我们填0基本级。
	// 参数3： 告诉OpenGL，我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们把纹理储存为GL_RGB值。
	// 参数4,5： 设置最终的纹理的宽度和高度。
	// 参数6： 应该一直被设为0(遗留问题)。
	// 参数7,8： 定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存在char(byte)，我们将会传入相应值。
	// 参数9： 真实的图像数据。
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	// 生成多级渐远纹理
	glGenerateMipmap(GL_TEXTURE_2D);

	// 生成了纹理和相应的多级渐远纹理后，解绑纹理对象、释放图像的内存很重要。
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// ===================
	// Texture 2
	// ===================
	// 绑定纹理
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// 设置贴图参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 设置纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 读取图像
	image = SOIL_load_image(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// 生成纹理
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// 释放资源
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);



	// 7.0 游戏循环
	while (!glfwWindowShouldClose(window))
	{
		// 检测输入事件
		glfwPollEvents();

		// 渲染
		// 清空颜色缓冲区
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 使用纹理单元绑定纹理
		glActiveTexture(GL_TEXTURE0);           //在绑定纹理之前，先激活纹理单元
		glBindTexture(GL_TEXTURE_2D, texture1); // 绑定纹理单元
												// 定义哪个uniform采样器对应哪个纹理单元
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// 激活渲染器
		ourShader.Use();

		// 开始绘制
		glBindVertexArray(VAO); // 绑VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);   // 解绑

		// 交换屏幕缓冲区
		glfwSwapBuffers(window);
	}
	// 8.0 释放资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}

//// V 函数实现 ////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}