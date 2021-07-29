#version 330 core

in vec2 texCoord;

uniform sampler2D texture1;

out vec4 fragColor;

void main() {
	
	vec4 texColor = texture(texture1, texCoord);
	fragColor = texColor;
}
