#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#ifndef SFMLOPENGL_VBO_HPP
#define SFMLOPENGL_VBO_HPP

template<class T>
class VBO {
    private:
        GLenum bufferType;
        GLenum drawType;
        size_t currentSize = 0;
        uint32_t id = 0;
    public:
        VBO() = default;
        VBO(GLenum bufferType, GLenum drawType, size_t size, size_t reserve = 0) {
            create(bufferType, drawType, size, reserve);
        }
        
        ~VBO() {
            glDeleteBuffers(1, &id);
        }
        
        void create(GLenum bufferType, GLenum drawType, size_t size, size_t reserve = 0) {
            this->bufferType = bufferType;
            this->drawType = drawType;
            glGenBuffers(1, &id);
            glBindBuffer(bufferType, id);
            glBufferData(bufferType, sizeof(T) * (size + reserve), nullptr, drawType);
            glBindBuffer(bufferType, 0);
            currentSize = size;
        }
        
        void bind() {
            glBindBuffer(bufferType, id);
        }
        
        void fill(size_t offset, size_t amount, const T* data) {
            glBindBuffer(bufferType, id);
            glBufferSubData(bufferType, sizeof(T) * offset, sizeof(T) * amount, data);
        }
        
        void fill(size_t offset, const std::vector<T>& data) {
            glBindBuffer(bufferType, id);
            glBufferSubData(bufferType, sizeof(T) * offset, sizeof(T) * data.size(), data.data());
        }
        
        void setData(size_t index, const T& data) {
            glBindBuffer(bufferType, id);
            glBufferSubData(bufferType, sizeof(T) * index, sizeof(T), &data);
        }
};


#endif //SFMLOPENGL_VBO_HPP

#pragma clang diagnostic pop