// 片段着色器 Fragment Shader

#version 330 core

// 输入数据
in vec3 ourColor;                  
in vec2 TexCoord;

// 输出数据
out vec4 color;

// 全局变量 - 纹理采样
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	// 我们使用GLSL的内建texture函数来采样纹理的颜色，
	// 它第一个参数是纹理采样，第二个参数是相应的纹理坐标。
	// color = texture(ourTexture, TexCoord) - 原本的写法

	// 混合纹理采样
	// GLSL的内建mix函数 混合两种颜色
	// 参数1，参数2位要混合的颜色1和颜色2
	// 参数3位混合权重, 0.0-1.0
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}
