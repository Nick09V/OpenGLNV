#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform vec4 chposicion = (  );

void main()
{
    gl_Position = vec4(aPos.x+chposicion.x, aPos.y+chposicion.y, aPos.z+chposicion.z, 1.0);
    ourColor = aColor;
}