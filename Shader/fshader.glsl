#version 330 core

in vec4 color;

uniform float grayFactor;	// we can set this variable in opengl code

out vec4 fragColor;

void main() {
	fragColor = vec4(color.r*grayFactor, color.g*grayFactor, color.b*grayFactor, 0.0f);
}
