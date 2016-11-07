// ������ɫ�� Vertex Shader

#version 330 core

// ��������
layout (location = 0) in vec3 position; // ����λ0 λ��
layout (location = 1) in vec3 color;    // ����λ1 ��ɫ
layout (location = 2) in vec2 texCoord; // ����λ2 ��������

// �������
out vec3 ourColor;                      // ��ɫ
out vec2 TexCoord;                      // ��������

void main()
{
    gl_Position = vec4(position, 1.0f); // ����Ϣ����,����4��vec.w����͸�ӻ���
    ourColor = color;                   // ����ɫ���ݳ�ȥ
	// ����y�ᣬ��Ϊ�����ͼ�θ�opengl�����෴
	// TexCoord = texCoord; - ԭ����д��
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
