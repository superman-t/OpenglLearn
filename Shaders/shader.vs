#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
uniform mat4 projectionMatrix, viewMatrix;
uniform vec3 rotation;

out vec4 outColor;

void main()
{
    
    outColor = color;
    mat4 rotate_x, rotate_y, rotate_z;
    
    rotate_x = mat4(1.0, 0.0, 0.0, 0.0,
                    0.0, cos(rotation.x), sin(rotation.x), 0.0,
                    0.0, -sin(rotation.x), cos(rotation.x), 0.0,
                    0.0, 0.0, 0.0, 1.0);
    
    rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    sin(rotation.y), 0.0, cos(rotation.y), 0.0,
                    0.0, 0.0, 0.0, 1.0);
    
    rotate_z = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
                    sin(rotation.z), cos(rotation.z), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0);
    
    gl_Position = projectionMatrix * viewMatrix *
    rotate_y * rotate_x *rotate_z * vec4(position, 1);
    
}
