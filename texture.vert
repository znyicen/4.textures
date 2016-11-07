// 顶点着色器 Vertex Shader

#version 330 core

// 顶点数据
layout (location = 0) in vec3 position; // 数据位0 位置
layout (location = 1) in vec3 color;    // 数据位1 颜色
layout (location = 2) in vec2 texCoord; // 数据位2 纹理坐标

// 输出数据
out vec3 ourColor;                      // 颜色
out vec2 TexCoord;                      // 纹理坐标

void main()
{
    gl_Position = vec4(position, 1.0f); // 将信息填入,参数4：vec.w用于透视划分
    ourColor = color;                   // 将颜色传递出去
	// 倒置y轴，因为大多数图形跟opengl坐标相反
	// TexCoord = texCoord; - 原本的写法
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
