
#version 330 core
layout (location = 0) in vec3 in_vertexCoordinate;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_texCoord;

uniform mat4 VP;
uniform vec3 chunkPosition;

out vec3 rescolor;
out vec2 TexCoord;

void main() {
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightPos1 = vec3(-3.7f, 2.3f, -2.8f);
	vec3 lightPos2 = vec3(2.0f, 2.0f, 1.7f);
	float ambientStrength = 0.4f;

	vec3 ambientLight = ambientStrength * lightColor;
	
	vec3 norm = normalize(in_Normal);
	vec3 lightDir1 = normalize(lightPos1);
	vec3 lightDir2 = normalize(lightPos2);

	float diff1 = max(dot(norm, lightDir1) - 0.25f, 0.0);
	float diff2 = max(dot(norm, lightDir2) - 0.25f, 0.0);
	vec3 diffuse = (diff1 + diff2) * lightColor;
	vec3 result = (ambientLight + diffuse) * vec3(1,1,1);

	rescolor = result;
	TexCoord = in_texCoord;
	gl_Position = VP * vec4(in_vertexCoordinate + chunkPosition, 1.0f);
}