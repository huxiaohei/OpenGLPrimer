#version 330 core

in vec2 texCoord;
in float glY;
in float glX;

uniform sampler2D texture1;
uniform int light;

out vec4 fragColor;

bool inLightZone() {
	if (abs(glY) < 0.4) {
		return true;
	}
	return false;
}

void main() {

	vec4 texColor = texture(texture1, texCoord);
	if (light == 1 && inLightZone()) {
		texColor = texColor * (2.0 - 6.0 * abs(glY));
	}
	fragColor = texColor;
}
