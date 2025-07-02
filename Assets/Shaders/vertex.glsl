#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 MVP;

void main()
{
    gl_Position = projection * view * model * vec4(position.xyz, 1.0);//MVP * vec4(position, 1.0);

    //gl_Position = vec4(position.x, position.y, position.z, 1.0);
}