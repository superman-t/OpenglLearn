#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
uniform mat4 projectionMatrix, viewMatrix, modelMatrix;

out vec2 outTexCoord;
void main()
{

    outTexCoord = texCoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
    
}