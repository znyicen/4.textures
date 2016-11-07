// ## ע������ ##
// 1. ��filesystem.h���޸ģ�
//    #include "root_directory.h" - ԭ���Ĵ���
//    const char* logl_root = "C:/LearnOpenGL-master"; // �趨��Ŀ¼
// 2. ��Ҫ�رչ��̵� C/C++ SDL��� ����
// 3. �Թ�������SOIL.lib
// ## ע������ ##

//// I ��ͷ ////
#include <iostream>

// GLEW
// GLEW ���Զ�ʶ�����ƽ̨��֧�ֵ�ȫ��OpenGL�߼���չ����
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
// OpenGL ���ڹ����ֱ����л������̡�����Լ���Ϸ�ֱ�����ʱ�����롢�̴߳����ȵȡ�
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>

// Other includes
#include <learnopengl/shader.h>
#include <learnopengl/filesystem.h>

//// II ����ԭ�� ////
void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mode);

//// III ȫ�ֱ��� ////
const GLuint WIDTH = 800, HEIGHT = 600;

//// IV ������ ////
int main()
{
	std::cout << "����GLFW����, OpenGL�汾��3.3��" << std::endl;
	// 1.0 ��ʼ��GLFW
	glfwInit();
	// 1.1 �趨GLFW�������ģʽ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// 2.0 �������ڶ���
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
		"LearnOpenGL", nullptr, nullptr);
	// 2.1 �����ڼ���openGL����
	glfwMakeContextCurrent(window);

	// ʹ���Զ��庯��
	glfwSetKeyCallback(window, key_callback);

	// 3.0 ��ʼ��GLEW
	glewExperimental = GL_TRUE; // ʹ���ִ�������
	glewInit();

	// 4.0 �����ӿ�
	glViewport(0, 0, WIDTH, HEIGHT);


	// 5.0 ��д��������ɫ������
	Shader ourShader("texture.vert", "texture.frag");


	// 6.0 ���ö�������
	GLfloat vertices[] = {
		 // Positions         // Colors           // Texture Coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // ��0��ʼ
		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};

	// 6.1 �������ݶ���
	GLuint VBO, VAO, EBO;		// ���㻺����󣬶��������������������� 
	glGenVertexArrays(1, &VAO);	// ���ɻ���ID
	glGenBuffers(1, &VBO);		// ���ɻ���ID
	glGenBuffers(1, &EBO);		// ���ɻ���ID

	// 6.2 �����ݶ���
	// ����VAO
	glBindVertexArray(VAO);

	// ����VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);

	// 6.3 ���Ͷ������ݣ����ݵģ�λ�á���λ����ʽ������������ƫ������
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(
		GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(
		GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// ��ͼ��������
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(
		GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// 6.4 ��� VAO
	glBindVertexArray(0);

	// 6.5 ��ȡ��������ͼ��֮����������⣩
	GLuint texture1;  // �½��������
	GLuint texture2;
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1); // ���������������Ȼ�����ݴ洢��GLuint������
	glBindTexture(GL_TEXTURE_2D, texture1); // �� 
											// ������ͼ����(����1��ʹ��2D��������2�����õ��ᣬ����3��UV���Ƶķ�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // �ظ�UV
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// �����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // ���Թ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ��ȡ����������������ͼ
	int width, height;

	unsigned char* image = SOIL_load_image(FileSystem::getPath(
		"resources/textures/container.jpg").c_str(), &width, &height, 0,
		SOIL_LOAD_RGB);

	// ��������
	// ����1�� ָ������Ŀ�꣨���������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ��
	// ����2�� Ϊ���Ǵ��㴴��������ָ���༶��Զ����Ĳ㼶�������ϣ�������ֹ�����ÿ���༶��Զ����Ĳ㼶�Ļ�������������0��������
	// ����3�� ����OpenGL������ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ��������ǰ�������ΪGL_RGBֵ��
	// ����4,5�� �������յ�����Ŀ�Ⱥ͸߶ȡ�
	// ����6�� Ӧ��һֱ����Ϊ0(��������)��
	// ����7,8�� ������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ�����char(byte)�����ǽ��ᴫ����Ӧֵ��
	// ����9�� ��ʵ��ͼ�����ݡ�
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	// ���ɶ༶��Զ����
	glGenerateMipmap(GL_TEXTURE_2D);

	// �������������Ӧ�Ķ༶��Զ����󣬽����������ͷ�ͼ����ڴ����Ҫ��
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// ===================
	// Texture 2
	// ===================
	// ������
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// ������ͼ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// �����������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ��ȡͼ��
	image = SOIL_load_image(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// ��������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	// �ͷ���Դ
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);



	// 7.0 ��Ϸѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ��������¼�
		glfwPollEvents();

		// ��Ⱦ
		// �����ɫ������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ʹ������Ԫ������
		glActiveTexture(GL_TEXTURE0);           //�ڰ�����֮ǰ���ȼ�������Ԫ
		glBindTexture(GL_TEXTURE_2D, texture1); // ������Ԫ
												// �����ĸ�uniform��������Ӧ�ĸ�����Ԫ
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// ������Ⱦ��
		ourShader.Use();

		// ��ʼ����
		glBindVertexArray(VAO); // ��VAO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);   // ���

		// ������Ļ������
		glfwSwapBuffers(window);
	}
	// 8.0 �ͷ���Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}

//// V ����ʵ�� ////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}