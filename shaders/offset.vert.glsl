#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 ourColor;

uniform float offset;

void main() {
    gl_Position = vec4(aPos.x + offset, aPos.yz, 1.0f);
    ourColor = vec4(aColor.xyz, 1.0f);
}