#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform float time;
uniform float scale;
uniform int dir;

out vec2 texCoord;
out float glX;
out float glY;

void main() {
	float r = sqrt(pow(aPos.x, 2) + pow(aPos.y, 2));
	float _time = time * dir;
	float x = r * cos(_time / 2.0 + atan(aPos.x, aPos.y));
	float y = r * sin(_time / 2.0 + atan(aPos.x, aPos.y));
	x = x * scale;
	y = y * scale;
	glX = x;
	glY = y;
	y = y * cos(3.14159 / 3.0);
	gl_Position = vec4(x, y, 0.0f, 1.0f);
	texCoord = aTexCoord;
}