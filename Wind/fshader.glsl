#version 330 core

in vec2 texCoord;

uniform sampler2D texture1;
uniform float time;

out vec4 fragColor;

void main() {
	float x = texCoord.x;
	float y = texCoord.y;
	float dtY = 0.05*texCoord.x*sin(2*time - 8*texCoord.x);
	float dtX = 0.008*texCoord.x*sin(2*time);
	y = y + dtY;
	x = x + dtX;
	if (y > 1.0 || y < 0.0) {
		discard;
		return;
	}
	if (x > 1.0) {
		discard;
		return;
	}
	vec4 texColor = texture(texture1, vec2(x, y));
	fragColor = texColor;
}
