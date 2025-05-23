#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;


out vec3 ourColor;
//out vec2 TexCoord;

uniform float xOffset, yOffset;
uniform float time;
void main()
{
	//float offset = sin(time) * 0.5;
	float offset = 0;
	gl_Position = vec4((aPos.x),(aPos.y + yOffset),aPos.z, 1.0);
	//gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	ourColor = aColor;
	//TexCoord = vec2(((aPos.x*0.5) + 0.5), ((aPos.y*0.5) + 0.5));
}