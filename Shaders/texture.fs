#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 outTexCoord;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, outTexCoord);
}