#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 VP;

out vec3 TexCoords;

void main() {
	TexCoords = aPos;
	vec4 pos = VP * vec4(aPos, 1.0f);
	gl_Position = pos.xyww;
}