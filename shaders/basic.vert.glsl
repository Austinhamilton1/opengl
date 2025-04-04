#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 ourColor;

void main() {
    gl_Position = vec4(aPos.xyz, 1.0f);
    ourColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
}