// Ƭ����ɫ�� Fragment Shader

#version 330 core

// ��������
in vec3 ourColor;                  
in vec2 TexCoord;

// �������
out vec4 color;

// ȫ�ֱ��� - �������
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	// ����ʹ��GLSL���ڽ�texture�����������������ɫ��
	// ����һ������������������ڶ�����������Ӧ���������ꡣ
	// color = texture(ourTexture, TexCoord) - ԭ����д��

	// ����������
	// GLSL���ڽ�mix���� ���������ɫ
	// ����1������2λҪ��ϵ���ɫ1����ɫ2
	// ����3λ���Ȩ��, 0.0-1.0
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}
