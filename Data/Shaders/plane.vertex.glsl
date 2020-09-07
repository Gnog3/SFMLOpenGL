#version 330 core
layout (location = 0) in vec2 in_positionOffsetStage;
layout (location = 1) in vec2 in_textureOffsetStage;

layout (location = 2) in vec3 in_planePosition;
layout (location = 3) in vec2 in_planeTexturePosition;
layout (location = 4) in ivec3 in_planeDirection;
layout (location = 5) in uint in_normalIndex;

uniform mat4 VP;
uniform vec3 chunkPosition;

out vec3 resColor;
out vec2 texCoord;

vec3 getLight(vec3 normal) {
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightPos1 = vec3(-3.7f, 2.3f, -2.8f);
    vec3 lightPos2 = vec3(2.0f, 2.0f, 1.7f);
    float ambientStrength = 0.4f;

    vec3 ambientLight = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir1 = normalize(lightPos1);
    vec3 lightDir2 = normalize(lightPos2);

    float diff1 = max(dot(norm, lightDir1) - 0.25f, 0.0);
    float diff2 = max(dot(norm, lightDir2) - 0.25f, 0.0);
    vec3 diffuse = (diff1 + diff2) * lightColor;
    vec3 result = (ambientLight + diffuse) * vec3(1, 1, 1);

    return result;
}

void main() {
    vec3 resultPosition = in_planePosition;
    if (in_positionOffsetStage.x == 1.0f) {
        if (in_planeDirection.x != 0) {
            resultPosition.x += in_planeDirection.x;
        } else {
            resultPosition.y += in_planeDirection.y;
        }
    }
    if (in_positionOffsetStage.y == 1.0f) {
        if (in_planeDirection.z != 0) {
            resultPosition.z += in_planeDirection.z;
        } else {
            resultPosition.y += in_planeDirection.y;
        }
    }
    vec2 resultTexturePosition = in_planeTexturePosition + in_textureOffsetStage;
    vec3[6] normals;
    normals[0] = vec3(0, 1, 0);
    normals[1] = vec3(0, -1, 0);
    normals[2] = vec3(-1, 0, 0);
    normals[3] = vec3(1, 0, 0);
    normals[4] = vec3(0, 0, 1);
    normals[5] = vec3(0, 0, -1);
    vec3 light = getLight(normals[in_normalIndex]);

    gl_Position = VP * vec4(resultPosition + chunkPosition, 1.0f);
    resColor = light;
    texCoord = resultTexturePosition;
}