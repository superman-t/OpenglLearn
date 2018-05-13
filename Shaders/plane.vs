#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
uniform mat4 projectionMatrix, viewMatrix;
uniform int line;

out vec4 outColor;

void main()
{
    
    if (line == 1)
    {
        outColor = vec4(0.0, 0.0, 1.0, 0.5);
    }
    else
    {
        outColor = color;
    }

    if (line == 1)
    {
        gl_Position = projectionMatrix * viewMatrix * vec4(position, 1);
    }
    else
    {
        gl_Position = projectionMatrix * viewMatrix * vec4(position, 1);
    }
}
