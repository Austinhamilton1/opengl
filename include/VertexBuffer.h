#pragma once

#include "Types.h"
#include "Texture.h"
#include "IndexBuffer.h"

#include <glad/glad.h>
#include <vector>
#include <cstdarg>
#include <unordered_map>
#include <memory>

namespace gl {
    struct VertexAttribute {
        unsigned int index;
        unsigned int elementSize;
        int type;
        int isNormalized;
        size_t stride;
        size_t offset;
    };

    class VertexBuffer {
    private:
        unsigned int id;
        BufferDrawType drawType;
        unsigned int elementSize;
        std::vector<float> data;
        std::unordered_map<int, std::shared_ptr<Texture>> textures;
        std::shared_ptr<IndexBuffer> indexes;
        std::vector<VertexAttribute> attributes;

    public:
        VertexBuffer(BufferDrawType);
        ~VertexBuffer();

        void addData(int elementSize, int count, ...);
        void staticAllocate();
        void setLayout(unsigned int location, unsigned int size, size_t stride, size_t offset);
        void select();
        void deselect();
        void enableAttributes();

        std::shared_ptr<Texture> getTexture(int key);
        void setTexture(int key, std::shared_ptr<Texture> texture);
        std::unordered_map<int, std::shared_ptr<Texture>> getTextures() { return textures; };
        unsigned int getElementSize() { return elementSize; };
        unsigned int getElementCount() { return data.size() / elementSize; };
        void setIndexBuffer(std::shared_ptr<IndexBuffer> indexes) { this->indexes = indexes; };
        std::shared_ptr<IndexBuffer> getIndexeBuffer() { return indexes; };
    };
}