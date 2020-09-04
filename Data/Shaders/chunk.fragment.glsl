#version 330 core
out vec4 color;
in vec3 rescolor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
void main() {
	color = texture(ourTexture, TexCoord) * vec4(rescolor, 1);
}