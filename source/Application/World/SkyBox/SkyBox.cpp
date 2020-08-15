#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"


#include "SkyBox.hpp"

SkyBox::SkyBox(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::vector<std::string>& faces) {
    shader = new sf::Shader();
    shader->loadFromFile(vertexShaderPath, fragmentShaderPath);
    // ***
    glGenVertexArrays(1, &vaoid);
    glBindVertexArray(vaoid);
    glGenBuffers(1, &vboid);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxVertices), skyBoxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // ***
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    sf::Vector2u size;
    for (unsigned int i = 0; i < faces.size(); i++) {
        sf::Image image;
        if (image.loadFromFile(faces[i])) {
            size = image.getSize();
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()
            );
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

SkyBox::~SkyBox() {
    glDeleteTextures(1, &textureId);
    glDeleteBuffers(1, &vboid);
    glDeleteVertexArrays(1, &vaoid);
}

void SkyBox::draw(const glm::mat4& vp) {

    glDepthFunc(GL_LEQUAL);
    shader->setUniform("VP", sf::Glsl::Mat4(&vp[0][0]));
    sf::Shader::bind(shader);
    glBindVertexArray(vaoid);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    sf::Shader::bind(nullptr);
}

SkyBox& SkyBox::operator=(SkyBox&& other) noexcept {
    textureId = other.textureId;
    other.textureId = 0;
    vaoid = other.vaoid;
    other.vaoid = 0;
    vboid = other.vboid;
    other.vboid = 0;
    shader = other.shader;
    other.shader = nullptr;
    return *this;
}


#pragma clang diagnostic pop